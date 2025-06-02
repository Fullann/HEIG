.global asm_matrix_distance_simd
.type asm_matrix_distance_simd, @function

.text
    

# Functions parameters : image_container* img, image_container* kernel, int x, int y
asm_matrix_distance_simd:
#   @@@@@@@@@@@ A completer @@@@@@@@@@
    push    %ebp                        # Sauvegarder la base de pile courante
    mov     %esp, %ebp                  # Initialiser la nouvelle base de pile
    subl    $4, %esp                    # Réserver 4 octets pour la variable locale sum
    
    push    %ebx                        # Sauvegarder ebx
    push    %esi                        # Sauvegarder esi
    push    %edi                        # Sauvegarder edi

    
    movl    8(%ebp), %eax               # Charger l'adresse de img dans eax
    movl    (%eax), %ecx                # Charger img->width dans ecx
    movl    %ecx, (image_width)         # Stocker la largeur de l'image
    movl    4(%eax), %ecx               # Charger img->height dans ecx
    movl    %ecx, (image_height)        # Stocker la hauteur de l'image

    movl    12(%ebp), %eax              # Charger l'adresse de kernel dans eax
    movl    (%eax), %ecx                # Charger kernel->width dans ecx
    movl    %ecx, (kernel_width)        # Stocker la largeur du kernel   
    movl    4(%eax), %ecx               # Charger kernel->height dans ecx
    movl    %ecx, (kernel_height)       # Stocker la hauteur du kernel

    movl    16(%ebp), %eax              # Charger x dans eax
    movl    %eax, (x)                   # Stocker x

    movl    20(%ebp), %eax              # Charger y dans eax
    movl    %eax, (y)                   # Stocker y

    movl    $0, (ky)                    # Initialiser ky à 0
    movl    $0, -4(%ebp)                # Initialiser sum à 0

    pxor    %xmm0, %xmm0                # Réinitialiser xmm0 à 0
    pxor    %xmm1, %xmm1                # Réinitialiser xmm1 à 0

    movl    8(%ebp), %eax               # Charger l'adresse de img dans eax
    movl    12(%eax), %esi              # Charger img->data dans esi

    movl    12(%ebp), %eax              # Charger l'adresse de kernel dans eax
    movl    12(%eax), %edi              # Charger kernel->data dans edi
        
    loop_y:
        movl        $0, (kx)            # Initialiser kx à 0
    loop_x:

        movl        (ky), %ebx          # Charger ky dans ebx
        addl        (y), %ebx           # ebx = ky + y   
        imull       (image_width), %ebx # ebx = (ky + y) * image_width
        addl        (kx), %ebx          # ebx = (ky + y) * image_width + kx
        addl        (x), %ebx           # ebx = (ky + y) * image_width + kx + x

        pmovzxbd    (%esi, %ebx), %xmm0 # Charger 4 pixels de l'image (zéro-extension 32 bits)

        # ebx = ky * kernel->width + kx

        movl        (ky), %ebx          # Charger ky dans ebx
        imull       (kernel_width), %ebx# ebx = ky * kernel_width
        addl        (kx), %ebx          # ebx = ky * kernel_width + kx

        pmovzxbd    (%edi, %ebx), %xmm1 # Charger 4 pixels du kernel (zéro-extension 32 bits)

        psubd       %xmm1, %xmm0        # Calculer la différence vectorielle entre pixels
        pmulld      %xmm0, %xmm0        # Calculer le carré des différences (vectorisé)

        phaddd      %xmm0, %xmm0        # Addition horizontale des composantes
        phaddd      %xmm0, %xmm0        # Accumuler les composantes

        movd        %xmm0, %eax         # Déplacer le résultat dans eax
        addl        %eax, -4(%ebp)      # Ajouter à sum

        addl        $4, (kx)            # Incrémenter kx de 4 (pixels traités)
        movl        (kx), %eax          # Charger kx dans eax
        cmpl        (kernel_width), %eax# Comparer kx à kernel_width
        jl loop_x                       # Boucler si kx < kernel_width

    incl        (ky)                    # Incrémenter ky
    movl        (ky), %eax              # Charger ky dans eax
    cmpl        (kernel_height), %eax   # Comparer ky à kernel_height
    jl loop_y                           # Boucler si ky < kernel_height

    movl    -4(%ebp), %eax              # Charger sum dans eax (valeur de retour)
    pop     %ebx                        # Restaurer ebx
    pop     %esi                        # Restaurer esi
    pop     %edi                        # Restaurer edi
    leave                               # Restaurer la pile
    ret                                 # Retour de la fonction
    
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
