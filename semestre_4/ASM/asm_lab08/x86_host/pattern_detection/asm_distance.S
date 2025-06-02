.global asm_matrix_distance_simd
.type asm_matrix_distance_simd, @function

.text
    

# Functions parameters : image_container* img, image_container* kernel, int x, int y
asm_matrix_distance_simd:
#   @@@@@@@@@@@ A completer @@@@@@@@@@
    push    %ebp                           # Sauvegarder la base de pile courante
    mov     %esp, %ebp                     # Définir la nouvelle base de pile
    subl    $4, %esp                       # Réserver de l'espace pour une variable locale
    
    push    %ebx                           # Sauvegarder ebx
    push    %esi                           # Sauvegarder esi
    push    %edi                           # Sauvegarder edi
    
    #IMG
    movl    8(%ebp), %eax                  # Charger l'adresse 
    movl    8(%eax), %ecx                  # Charger la largeur
    movl    %ecx, (image_width)            # Stocker la largeur 
    movl    4(%eax), %ecx                  # Charger l'hauteur
    movl    %ecx, (image_height)           # Stocker la hauteur
    movl    12(%eax), %esi                 # Charger les donnée  dans esi
    
    #KERNEL
    movl    12(%ebp), %eax                 # Charger l'adresse
    movl    8(%eax), %ecx                  # Charger la largeur 
    movl    %ecx, (kernel_width)           # Stocker la largeur
    movl    4(%eax), %ecx                  # Charger la hauteur
    movl    %ecx, (kernel_height)          # Stocker la hauteur
    movl    12(%eax), %edi                 # Charger les donnée dans edi

    movl    16(%ebp), %eax                 # Charger x
    movl    %eax, (x)                      # Stocker x
    movl    20(%ebp), %eax                 # Charger y
    movl    %eax, (y)                      # Stocker y

    movl    $0, (ky)                       # Initialiser ky à 0
    movl    $0, -4(%ebp)                   # Initialiser la somme à 0
    pxor    %xmm7, %xmm7                   # Réinitialiser l'accumulateur SIMD à 0
        
loop_y:
    movl    $0, (kx)                       # Initialiser kx à 0
    
loop_x:
    # addr_img = (y + ky) * image_width + (x + kx)
    movl    (ky), %ebx                     # ebx = ky
    addl    (y), %ebx                      # ebx = ky + y   
    imull   (image_width), %ebx            # ebx = (ky + y) * image_width
    movl    (kx), %eax                     # eax = kx
    addl    (x), %eax                      # eax = kx + x
    addl    %eax, %ebx                     # ebx = (ky + y) * image_width + (kx + x)

    pmovzxbd (%esi, %ebx), %xmm0           # Charger et étendre 4 pixels de l'image en entiers 32 bits

    # addr_kernel = ky * kernel_width + kx
    movl    (ky), %eax                     # eax = ky
    imull   (kernel_width), %eax           # eax = ky * kernel_width
    addl    (kx), %eax                     # eax = ky * kernel_width + kx

    pmovzxbd (%edi, %eax), %xmm1           # Charger et étendre 4 pixels du kernel en entiers 32 bits

    psubd   %xmm1, %xmm0                   # Calculer la différence vectorielle entre les pixels
    pmulld  %xmm0, %xmm0                   # Calculer le carré des différences

    paddd   %xmm0, %xmm7                   # Accumuler les 4 différences au carré

    addl    $4, (kx)                       # Incrémenter kx de 4
    movl    (kx), %eax                     # Charger kx
    cmpl    (kernel_width), %eax           # Comparer kx à la largeur du kernel
    jl      loop_x                         # Boucler si kx < kernel_width

    incl    (ky)                           # Incrémenter ky
    movl    (ky), %eax                     # Charger ky
    cmpl    (kernel_height), %eax          # Comparer ky à la hauteur du kernel
    jl      loop_y                         # Boucler si ky < kernel_height

    phaddd  %xmm7, %xmm7                   # Additionner horizontalement les paires : [a+b, c+d, a+b, c+d]
    phaddd  %xmm7, %xmm7                   # Additionner horizontalement : [a+b+c+d, a+b+c+d, a+b+c+d, a+b+c+d]
    
    movd    %xmm7, %eax                    # Déplacer la somme finale dans eax

    pop     %edi                           # Restaurer edi
    pop     %esi                           # Restaurer esi
    pop     %ebx                           # Restaurer ebx
    leave                                  # Restaurer la pile
    ret                                    # Retour de la fonction
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
