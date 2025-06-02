
.section .data
    # Espaces pour variables temporaires si nécessaire
    temp_buffer: .space 16

.section .text
.globl asm_matrix_distance_simd
.type asm_matrix_distance_simd, @function

asm_matrix_distance_simd:
    # Prologue
    pushq %rbp
    movq %rsp, %rbp
    
    # Sauvegarder les registres utilisés
    pushq %rbx
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15
    
    # Paramètres de la fonction:
    # %rdi = image_container *img
    # %rsi = image_container *kernel  
    # %rdx = int x
    # %rcx = int y
    
    # Récupérer les informations de l'image
    movl 4(%rdi), %r8d      # img->height
    movl 8(%rdi), %r9d      # img->width
    movq 12(%rdi), %r10     # img->data
    
    # Récupérer les informations du kernel
    movl 4(%rsi), %r11d     # kernel->height
    movl 8(%rsi), %r12d     # kernel->width
    movq 12(%rsi), %r13     # kernel->data
    
    # Initialiser l'accumulateur SIMD à zéro
    pxor %xmm0, %xmm0       # Accumulateur principal
    
    # Boucle externe: pour chaque ligne du motif
    xorl %r14d, %r14d       # i = 0 (ligne courante du kernel)
    
outer_loop:
    cmpl %r11d, %r14d       # Comparer i avec kernel->height
    jge end_outer_loop
    
    # Boucle interne: pour chaque groupe de 4 pixels de la ligne
    xorl %r15d, %r15d       # j = 0 (colonne courante)
    
inner_loop:
    cmpl %r12d, %r15d       # Comparer j avec kernel->width
    jge end_inner_loop
    
    # Calculer l'adresse dans l'image source
    # addr_img = img->data + (y + i) * img->width + (x + j)
    movl %ecx, %eax         # y
    addl %r14d, %eax        # y + i
    imull %r9d, %eax        # (y + i) * img->width
    addl %edx, %eax         # (y + i) * img->width + x
    addl %r15d, %eax        # (y + i) * img->width + x + j
    addq %r10, %rax         # Ajouter img->data
    
    # Calculer l'adresse dans le kernel
    # addr_kernel = kernel->data + i * kernel->width + j
    movl %r14d, %ebx        # i
    imull %r12d, %ebx       # i * kernel->width
    addl %r15d, %ebx        # i * kernel->width + j
    addq %r13, %rbx         # Ajouter kernel->data
    
    # Charger et étendre 4 pixels de l'image (8-bit -> 32-bit)
    pmovzxbd (%rax), %xmm1
    
    # Charger et étendre 4 pixels du kernel (8-bit -> 32-bit)
    pmovzxbd (%rbx), %xmm2
    
    # Soustraire les valeurs (4 à la fois)
    psubd %xmm2, %xmm1      # xmm1 = img_pixels - kernel_pixels
    
    # Mettre au carré (multiplier par soi-même)
    pmulld %xmm1, %xmm1     # xmm1 = (img_pixels - kernel_pixels)²
    
    # Accumuler dans l'accumulateur principal
    paddd %xmm1, %xmm0      # xmm0 += xmm1
    
    # Incrémenter j de 4 (traiter 4 pixels à la fois)
    addl $4, %r15d
    jmp inner_loop
    
end_inner_loop:
    # Incrémenter i
    incl %r14d
    jmp outer_loop
    
end_outer_loop:
    # Finir de sommer les 4 valeurs dans xmm0
    # Utiliser phaddd pour faire des additions horizontales
    phaddd %xmm0, %xmm0     # [a+b, c+d, a+b, c+d]
    phaddd %xmm0, %xmm0     # [a+b+c+d, *, a+b+c+d, *]
    
    # Récupérer le résultat final (premier élément de 32 bits)
    movd %xmm0, %eax        # Retourner la somme finale
    
    # Épilogue
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %rbx
    popq %rbp
    ret