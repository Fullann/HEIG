.global asm_matrix_distance_simd
.type asm_matrix_distance_simd, @function

.text

# Functions parameters : image_container* img, image_container* kernel, int x, int y
asm_matrix_distance_simd:
#   @@@@@@@@@@@ A completer @@@@@@@@@@
    push    %ebp
    mov     %esp, %ebp
    
    push    %ebx
    push    %esi
    push    %edi

    # Récupérer les paramètres et stocker les dimensions
    movl    8(%ebp), %eax           # img address
    movl    8(%eax), %ecx           # img->width (offset 8, pas 0)
    movl    %ecx, (image_width)
    movl    4(%eax), %ecx           # img->height (offset 4)
    movl    %ecx, (image_height)

    movl    12(%ebp), %eax          # kernel address
    movl    8(%eax), %ecx           # kernel->width (offset 8, pas 0)
    movl    %ecx, (kernel_width)    
    movl    4(%eax), %ecx           # kernel->height (offset 4)
    movl    %ecx, (kernel_height)   

    movl    16(%ebp), %eax          # x
    movl    %eax, (x)

    movl    20(%ebp), %eax          # y
    movl    %eax, (y)

    # Initialisation
    movl    $0, (ky)
    pxor    %xmm7, %xmm7            # Accumulateur global dans xmm7

    movl    8(%ebp), %eax           # img address
    movl    12(%eax), %esi          # esi = img->data

    movl    12(%ebp), %eax          # kernel address
    movl    12(%eax), %edi          # edi = kernel->data
        
    loop_y:
        movl        $0, (kx)            # init kx to 0
    loop_x:

        # Calculer l'adresse dans l'image
        movl        (ky), %ebx          # ebx = ky
        addl        (y), %ebx           # ebx = ky + y   
        imull       (image_width), %ebx # ebx = (ky + y) * image_width
        addl        (kx), %ebx          # ebx = (ky + y) * image_width + kx
        addl        (x), %ebx           # ebx = (ky + y) * image_width + kx + x

        # Charger et étendre 4 pixels de l'image
        pmovzxbd    (%esi, %ebx), %xmm0 # extend to 32-bit integers 4 pixels

        # Calculer l'adresse dans le kernel
        movl        (ky), %ebx          
        imull       (kernel_width), %ebx
        addl        (kx), %ebx        

        # Charger et étendre 4 pixels du kernel
        pmovzxbd    (%edi, %ebx), %xmm1 # extend to 32-bit integers 4 pixels

        # Calculer la différence au carré
        psubd       %xmm1, %xmm0        # compute vectorized difference between pixels
        pmulld      %xmm0, %xmm0        # compute vectorized square between pixels

        # Accumuler dans l'accumulateur global
        paddd       %xmm0, %xmm7        # Ajouter à l'accumulateur global

        # Incrémenter kx de 4 et vérifier la condition
        addl        $4, (kx)
        movl        (kx), %eax
        cmpl        (kernel_width), %eax
        jl loop_x

    # Incrémenter ky et vérifier la condition
    incl        (ky)
    movl        (ky), %eax
    cmpl        (kernel_height), %eax
    jl loop_y

    # Sommer horizontalement les 4 valeurs accumulées
    phaddd      %xmm7, %xmm7        # [a+b, c+d, a+b, c+d]
    phaddd      %xmm7, %xmm7        # [a+b+c+d, *, a+b+c+d, *]

    # Récupérer le résultat final
    movd        %xmm7, %eax         # Retourner la somme finale

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