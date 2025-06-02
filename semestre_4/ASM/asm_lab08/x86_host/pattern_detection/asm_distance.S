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

    # Méthode alternative pour charger 4 pixels consécutifs
    # Au lieu de pmovzxbd, utilisons des loads manuels
    movzbl  (%esi, %eax), %ebx          # Charger pixel 0 -> ebx (32-bit)
    movd    %ebx, %xmm0                 # Mettre dans xmm0[31:0]
    
    incl    %eax
    movzbl  (%esi, %eax), %ebx          # Charger pixel 1 -> ebx
    movd    %ebx, %xmm1                 # Mettre dans xmm1[31:0]
    pslldq  $4, %xmm1                   # Décaler à gauche de 4 bytes
    por     %xmm1, %xmm0                # Combiner dans xmm0
    
    incl    %eax
    movzbl  (%esi, %eax), %ebx          # Charger pixel 2 -> ebx
    movd    %ebx, %xmm1                 # Mettre dans xmm1[31:0]
    pslldq  $8, %xmm1                   # Décaler à gauche de 8 bytes
    por     %xmm1, %xmm0                # Combiner dans xmm0
    
    incl    %eax
    movzbl  (%esi, %eax), %ebx          # Charger pixel 3 -> ebx
    movd    %ebx, %xmm1                 # Mettre dans xmm1[31:0]
    pslldq  $12, %xmm1                  # Décaler à gauche de 12 bytes
    por     %xmm1, %xmm0                # Combiner dans xmm0
    # Maintenant xmm0 contient [pixel3, pixel2, pixel1, pixel0] en 32-bit

    # Calculer l'adresse dans le kernel : ky * kernel_width + kx  
    movl    (ky), %eax                  # Charger ky
    imull   (kernel_width), %eax        # eax = ky * kernel_width
    addl    (kx), %eax                  # eax = ky * kernel_width + kx

    # Charger 4 pixels du kernel de la même manière
    movzbl  (%edi, %eax), %ebx          # Charger pixel 0 -> ebx
    movd    %ebx, %xmm2                 # Mettre dans xmm2[31:0]
    
    incl    %eax
    movzbl  (%edi, %eax), %ebx          # Charger pixel 1 -> ebx
    movd    %ebx, %xmm1                 # Mettre dans xmm1[31:0]
    pslldq  $4, %xmm1                   # Décaler à gauche de 4 bytes
    por     %xmm1, %xmm2                # Combiner dans xmm2
    
    incl    %eax
    movzbl  (%edi, %eax), %ebx          # Charger pixel 2 -> ebx
    movd    %ebx, %xmm1                 # Mettre dans xmm1[31:0]
    pslldq  $8, %xmm1                   # Décaler à gauche de 8 bytes
    por     %xmm1, %xmm2                # Combiner dans xmm2
    
    incl    %eax
    movzbl  (%edi, %eax), %ebx          # Charger pixel 3 -> ebx
    movd    %ebx, %xmm1                 # Mettre dans xmm1[31:0]
    pslldq  $12, %xmm1                  # Décaler à gauche de 12 bytes
    por     %xmm1, %xmm2                # Combiner dans xmm2
    # Maintenant xmm2 contient [pixel3, pixel2, pixel1, pixel0] du kernel

    # Calculer la différence et le carré
    psubd   %xmm2, %xmm0                # xmm0 = img - kernel
    
    # Multiplication manuelle pour éviter pmulld (SSE4.1)
    # Décomposer xmm0 en deux parties et utiliser pmullw + pmuludq
    movdqa  %xmm0, %xmm1                # Copier xmm0 dans xmm1
    pmuludq %xmm0, %xmm0                # Multiplier les éléments 0 et 2 (64-bit)
    psrlq   $32, %xmm1                  # Décaler pour récupérer éléments 1 et 3
    pmuludq %xmm1, %xmm1                # Multiplier les éléments 1 et 3 (64-bit)
    
    # Réassembler le résultat
    pshufd  $0x08, %xmm0, %xmm0         # Récupérer les parties basses de 0 et 2
    pshufd  $0x08, %xmm1, %xmm1         # Récupérer les parties basses de 1 et 3
    punpckldq %xmm1, %xmm0              # Entremêler pour reconstituer [3²,1²,2²,0²]
    pshufd  $0xD8, %xmm0, %xmm0         # Réorganiser en [3²,2²,1²,0²]

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
