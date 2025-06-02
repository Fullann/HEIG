.global asm_matrix_distance_simd
.type asm_matrix_distance_simd, @function

.text
    

# Functions parameters : image_container* img, image_container* kernel, int x, int y
asm_matrix_distance_simd:
#   @@@@@@@@@@@ A completer @@@@@@@@@@
    push    %ebp                        # Sauvegarder la base de pile courante
    mov     %esp, %ebp                  # Initialiser la nouvelle base de pile
    
    push    %ebx                        # Sauvegarder ebx
    push    %esi                        # Sauvegarder esi
    push    %edi                        # Sauvegarder edi

    # Stocker les paramètres dans les variables globales
    movl    8(%ebp), %eax               # Charger l'adresse de img dans eax
    movl    (%eax), %ecx                # Charger img->width dans ecx
    movl    %ecx, (image_width)         # Stocker la largeur de l'image
    movl    4(%eax), %ecx               # Charger img->height dans ecx
    movl    %ecx, (image_height)        # Stocker la hauteur de l'image
    movl    12(%eax), %esi              # Charger img->data dans esi

    movl    12(%ebp), %eax              # Charger l'adresse de kernel dans eax
    movl    (%eax), %ecx                # Charger kernel->width dans ecx
    movl    %ecx, (kernel_width)        # Stocker la largeur du kernel   
    movl    4(%eax), %ecx               # Charger kernel->height dans ecx
    movl    %ecx, (kernel_height)       # Stocker la hauteur du kernel
    movl    12(%eax), %edi              # Charger kernel->data dans edi

    movl    16(%ebp), %eax              # Charger x dans eax
    movl    %eax, (x)                   # Stocker x
    movl    20(%ebp), %eax              # Charger y dans eax
    movl    %eax, (y)                   # Stocker y

    # Initialiser les compteurs et la somme
    movl    $0, (ky)                    # Initialiser ky à 0
    pxor    %xmm7, %xmm7                # xmm7 contiendra la somme accumulée

loop_y:
    movl    $0, (kx)                    # Initialiser kx à 0
    
loop_x:
    # Calculer l'adresse dans l'image : (y + ky) * image_width + x + kx
    movl    (ky), %eax                  # Charger ky
    addl    (y), %eax                   # eax = ky + y
    imull   (image_width), %eax         # eax = (ky + y) * image_width
    addl    (x), %eax                   # eax = (ky + y) * image_width + x
    addl    (kx), %eax                  # eax = (ky + y) * image_width + x + kx

    # Charger 4 pixels de l'image (extension zéro vers 32 bits)
    pmovzxbd (%esi, %eax), %xmm0        # 4 pixels image -> xmm0

    # Calculer l'adresse dans le kernel : ky * kernel_width + kx  
    movl    (ky), %eax                  # Charger ky
    imull   (kernel_width), %eax        # eax = ky * kernel_width
    addl    (kx), %eax                  # eax = ky * kernel_width + kx

    # Charger 4 pixels du kernel (extension zéro vers 32 bits)
    pmovzxbd (%edi, %eax), %xmm1        # 4 pixels kernel -> xmm1

    # Calculer la différence et le carré
    psubd   %xmm1, %xmm0                # xmm0 = img - kernel
    pmulld  %xmm0, %xmm0                # xmm0 = (img - kernel)²

    # Accumuler dans xmm7
    paddd   %xmm0, %xmm7                # xmm7 += xmm0

    # Incrémenter kx par 4 (on traite 4 pixels à la fois)
    addl    $4, (kx)
    movl    (kx), %eax
    cmpl    (kernel_width), %eax        # Comparer kx avec kernel_width
    jl      loop_x

    # Incrémenter ky
    incl    (ky)
    movl    (ky), %eax
    cmpl    (kernel_height), %eax       # Comparer ky avec kernel_height  
    jl      loop_y

    # Sommer les 4 valeurs dans xmm7 pour obtenir le résultat final
    # xmm7 contient [a, b, c, d]
    phaddd  %xmm7, %xmm7                # xmm7 = [a+b, c+d, a+b, c+d]
    phaddd  %xmm7, %xmm7                # xmm7 = [a+b+c+d, a+b+c+d, a+b+c+d, a+b+c+d]
    
    movd    %xmm7, %eax                 # Résultat final dans eax

    pop     %edi                        # Restaurer les registres
    pop     %esi
    pop     %ebx
    leave
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
