.global asm_matrix_distance_simd
.type asm_matrix_distance_simd, @function

.text
    

# Functions parameters : image_container* img, image_container* kernel, int x, int y
asm_matrix_distance_simd:
#   @@@@@@@@@@@ A completer @@@@@@@@@@
push    %ebp
    mov     %esp, %ebp
    subl    $4, %esp                # localvar: sum
    
    push    %ebx
    push    %esi
    push    %edi

    # Récupération des données de l'image
    movl    8(%ebp), %eax           # img address
    movl    8(%eax), %ecx            # img->width
    movl    %ecx, (image_width)
    movl    4(%eax), %ecx           # img->height
    movl    %ecx, (image_height)
    movl    12(%eax), %esi          # esi = img->data

    # Récupération des données du kernel
    movl    12(%ebp), %eax          # kernel address
    movl    8(%eax), %ecx            # kernel->width
    movl    %ecx, (kernel_width)    
    movl    4(%eax), %ecx           # kernel->height
    movl    %ecx, (kernel_height)
    movl    12(%eax), %edi          # edi = kernel->data

    # Récupération des coordonnées
    movl    16(%ebp), %eax          # x
    movl    %eax, (x)
    movl    20(%ebp), %eax          # y
    movl    %eax, (y)

    # Initialisation des variables
    movl    $0, (ky)
    movl    $0, -4(%ebp)            # initialize sum to 0
    pxor    %xmm7, %xmm7            # accumulator for sum (reset to 0)
        
loop_y:
    movl    $0, (kx)                # init kx to 0
    
loop_x:
    # Calcul de l'adresse dans l'image source
    # addr_img = (y + ky) * image_width + (x + kx)
    movl    (ky), %ebx              # ebx = ky
    addl    (y), %ebx               # ebx = ky + y   
    imull   (image_width), %ebx     # ebx = (ky + y) * image_width
    movl    (kx), %eax              # eax = kx
    addl    (x), %eax               # eax = kx + x
    addl    %eax, %ebx              # ebx = (ky + y) * image_width + (kx + x)

    # Chargement et extension des pixels de l'image (4 pixels à la fois)
    pmovzxbd (%esi, %ebx), %xmm0    # extend to 32-bit integers 4 pixels from image

    # Calcul de l'adresse dans le kernel
    # addr_kernel = ky * kernel_width + kx
    movl    (ky), %eax              
    imull   (kernel_width), %eax
    addl    (kx), %eax

    # Chargement et extension des pixels du kernel (4 pixels à la fois)
    pmovzxbd (%edi, %eax), %xmm1    # extend to 32-bit integers 4 pixels from kernel

    # Calcul de la différence au carré
    psubd   %xmm1, %xmm0            # compute vectorized difference between pixels
    pmulld  %xmm0, %xmm0            # compute vectorized square of differences

    # Accumulation dans le registre xmm7
    paddd   %xmm0, %xmm7            # accumulate the 4 squared differences

    # Incrément de kx par 4 (traitement de 4 pixels à la fois)
    addl    $4, (kx)
    movl    (kx), %eax
    cmpl    (kernel_width), %eax
    jl      loop_x

    # Incrément de ky
    incl    (ky)
    movl    (ky), %eax
    cmpl    (kernel_height), %eax
    jl      loop_y

    # Réduction finale : somme horizontale des 4 composantes de xmm7
    phaddd  %xmm7, %xmm7            # horizontally add pairs: [a+b, c+d, a+b, c+d]
    phaddd  %xmm7, %xmm7            # horizontally add pairs: [a+b+c+d, a+b+c+d, a+b+c+d, a+b+c+d]
    
    # Extraction du résultat final
    movd    %xmm7, %eax             # move the final sum to eax

    pop     %edi
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
