.global asm_matrix_distance_simd
.type asm_matrix_distance_simd, @function

.text
    

# Functions parameters : image_container* img, image_container* kernel, int x, int y
asm_matrix_distance_simd:
#   @@@@@@@@@@@ A completer @@@@@@@@@@
# Prologue - sauvegarde des registres et setup du stack frame
    # Prologue - sauvegarde des registres et setup du stack frame
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx
    pushl %esi
    pushl %edi
    
    # Récupération des paramètres depuis la pile
    movl 8(%ebp), %eax      # img pointer
    movl 12(%ebp), %ebx     # kernel pointer  
    movl 16(%ebp), %ecx     # x coordinate
    movl 20(%ebp), %edx     # y coordinate
    
    # Sauvegarde des coordonnées dans les variables globales
    movl %ecx, x
    movl %edx, y
    
    # Récupération des dimensions du kernel
    movl 0(%ebx), %ecx      # kernel->width
    movl %ecx, kernel_width
    movl 4(%ebx), %ecx      # kernel->height
    movl %ecx, kernel_height
    
    # Récupération des dimensions de l'image
    movl 0(%eax), %ecx      # img->width
    movl %ecx, image_width
    movl 4(%eax), %ecx      # img->height
    movl %ecx, image_height
    
    # Récupération des pointeurs vers les données
    movl 12(%eax), %esi     # img->data
    movl 12(%ebx), %edi     # kernel->data
    
    # Initialisation de l'accumulateur SIMD
    pxor %xmm0, %xmm0       # sum = 0
    pxor %xmm7, %xmm7       # registre de zéros pour les extensions
    
    # Boucle externe: parcours des lignes du kernel
    movl $0, ky
outer_loop:
    movl ky, %eax
    cmpl kernel_height, %eax
    jge end_outer_loop
    
    # Boucle interne: parcours des colonnes du kernel (par groupes de 4)
    movl $0, kx
inner_loop:
    movl kx, %eax
    cmpl kernel_width, %eax
    jge end_inner_loop
    
    # Calcul de l'adresse dans l'image
    # img_addr = img_data + (y + ky) * img_width + (x + kx)
    movl y, %eax
    addl ky, %eax           # y + ky
    imull image_width, %eax # (y + ky) * img_width
    movl x, %ebx
    addl kx, %ebx           # x + kx
    addl %ebx, %eax         # (y + ky) * img_width + (x + kx)
    addl %esi, %eax         # img_data + offset
    
    # Calcul de l'adresse dans le kernel
    # kernel_addr = kernel_data + ky * kernel_width + kx
    movl ky, %ebx
    imull kernel_width, %ebx # ky * kernel_width
    movl kx, %ecx
    addl %ecx, %ebx         # ky * kernel_width + kx
    addl %edi, %ebx         # kernel_data + offset
    
    # Chargement des 4 pixels de l'image (8-bit)
    movd (%eax), %xmm1      # Charger 4 bytes dans les 32 bits inférieurs
    punpcklbw %xmm7, %xmm1  # Étendre 8->16 bit (avec des zéros)
    punpcklwd %xmm7, %xmm1  # Étendre 16->32 bit (avec des zéros)
    
    # Chargement des 4 pixels du kernel (8-bit)
    movd (%ebx), %xmm2      # Charger 4 bytes dans les 32 bits inférieurs
    punpcklbw %xmm7, %xmm2  # Étendre 8->16 bit (avec des zéros)
    punpcklwd %xmm7, %xmm2  # Étendre 16->32 bit (avec des zéros)
    
    # Calcul de la différence
    psubd %xmm2, %xmm1      # img_pixels - kernel_pixels
    
    # Mise au carré des différences (multiplication 32-bit en SSE2)
    # Utilisation de la formule: (a-b)² = a² - 2ab + b²
    # Mais plus simple: on fait la multiplication directement
    movdqa %xmm1, %xmm3     # Copie de la différence
    
    # Multiplication 32-bit avec SSE2 (plus complexe qu'avec SSE4.1)
    # On utilise pmuludq qui multiplie les éléments 0 et 2 (64-bit result)
    movdqa %xmm1, %xmm4     # Copie pour éléments 0,2
    movdqa %xmm1, %xmm5     # Copie pour éléments 1,3
    
    pmuludq %xmm3, %xmm4    # Multiplie éléments 0 et 2
    psrlq $32, %xmm5        # Décale pour accéder aux éléments 1,3
    psrlq $32, %xmm3        # Décale la copie aussi
    pmuludq %xmm3, %xmm5    # Multiplie éléments 1 et 3
    
    # Recomposer le résultat
    psllq $32, %xmm5        # Remet les éléments 1,3 en place
    por %xmm5, %xmm4        # Combine les résultats
    
    # Accumulation des carrés
    paddd %xmm4, %xmm0      # sum += squared_differences
    
    # Incrémentation de kx par 4 (traitement de 4 pixels à la fois)
    addl $4, kx
    jmp inner_loop

end_inner_loop:
    # Incrémentation de ky
    incl ky
    jmp outer_loop

end_outer_loop:
    # Réduction horizontale pour obtenir la somme finale
    # Additionner les 4 valeurs 32-bit dans xmm0
    movdqa %xmm0, %xmm1     # Copie
    psrldq $8, %xmm1        # Décale de 8 bytes (2 éléments)
    paddd %xmm1, %xmm0      # Additionne les paires
    
    movdqa %xmm0, %xmm1     # Copie
    psrldq $4, %xmm1        # Décale de 4 bytes (1 élément)
    paddd %xmm1, %xmm0      # Additionne le dernier élément
    
    # Extraction du résultat final dans %eax
    movd %xmm0, %eax
    
    # Épilogue - restauration des registres
    popl %edi
    popl %esi
    popl %ebx
    popl %ebp
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
