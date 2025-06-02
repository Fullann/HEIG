.global asm_matrix_distance_simd
.type asm_matrix_distance_simd, @function

.text
    

# Functions parameters : image_container* img, image_container* kernel, int x, int y
asm_matrix_distance_simd:
#   @@@@@@@@@@@ A completer @@@@@@@@@@

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
    
    # Sauvegarder les paramètres dans les variables globales
    movl %edx, x(%rip)
    movl %ecx, y(%rip)
    
    # Récupérer et sauvegarder les informations de l'image
    movl 4(%rdi), %eax      # img->height
    movl %eax, image_height(%rip)
    movl 8(%rdi), %eax      # img->width
    movl %eax, image_width(%rip)
    movq 12(%rdi), %r10     # img->data
    
    # Récupérer et sauvegarder les informations du kernel
    movl 4(%rsi), %eax      # kernel->height
    movl %eax, kernel_height(%rip)
    movl 8(%rsi), %eax      # kernel->width
    movl %eax, kernel_width(%rip)
    movq 12(%rsi), %r13     # kernel->data
    
    # Initialiser l'accumulateur SIMD à zéro
    pxor %xmm0, %xmm0       # Accumulateur principal
    
    # Initialiser ky = 0 (ligne courante du kernel)
    movl $0, ky(%rip)
    
outer_loop:
    # Vérifier si ky < kernel_height
    movl ky(%rip), %eax
    cmpl kernel_height(%rip), %eax
    jge end_outer_loop
    
    # Initialiser kx = 0 (colonne courante)
    movl $0, kx(%rip)
    
inner_loop:
    # Vérifier si kx < kernel_width
    movl kx(%rip), %eax
    cmpl kernel_width(%rip), %eax
    jge end_inner_loop
    
    # Calculer l'adresse dans l'image source
    # addr_img = img->data + (y + ky) * img->width + (x + kx)
    movl y(%rip), %eax      # y
    addl ky(%rip), %eax     # y + ky
    imull image_width(%rip), %eax  # (y + ky) * img->width
    addl x(%rip), %eax      # (y + ky) * img->width + x
    addl kx(%rip), %eax     # (y + ky) * img->width + x + kx
    addq %r10, %rax         # Ajouter img->data
    
    # Calculer l'adresse dans le kernel
    # addr_kernel = kernel->data + ky * kernel->width + kx
    movl ky(%rip), %ebx     # ky
    imull kernel_width(%rip), %ebx  # ky * kernel->width
    addl kx(%rip), %ebx     # ky * kernel->width + kx
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
    
    # Incrémenter kx de 4 (traiter 4 pixels à la fois)
    addl $4, kx(%rip)
    jmp inner_loop
    
end_inner_loop:
    # Incrémenter ky
    addl $1, ky(%rip)
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

#   @@@@@@@@@@@ ----------- @@@@@@@@@@




.data

kernel_width:
    .space 4

kernel_height:
    .space 4

image_width:
    .space 4

image_height:
    .space 4
kx:
    .space 4
ky:
    .space 4
x: 
    .space 4
y: 
    .space 4