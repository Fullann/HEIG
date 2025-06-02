.global asm_matrix_distance_simd
.type asm_matrix_distance_simd, @function

.text
    

# Functions parameters : image_container* img, image_container* kernel, int x, int y
asm_matrix_distance_simd:
#   @@@@@@@@@@@ A completer @@@@@@@@@@
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
    pxor %xmm0, %xmm0       # sum = 0 (4 valeurs 32-bit)
    
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
    mull image_width        # (y + ky) * img_width
    movl x, %ebx
    addl kx, %ebx           # x + kx
    addl %ebx, %eax         # (y + ky) * img_width + (x + kx)
    addl %esi, %eax         # img_data + offset
    
    # Calcul de l'adresse dans le kernel
    # kernel_addr = kernel_data + ky * kernel_width + kx
    movl ky, %ebx
    mull kernel_width       # ky * kernel_width
    movl kx, %ecx
    addl %ecx, %ebx         # ky * kernel_width + kx
    addl %edi, %ebx         # kernel_data + offset
    
    # Chargement et extension des 4 pixels de l'image (8-bit -> 32-bit)
    pmovzxbd (%eax), %xmm1
    
    # Chargement et extension des 4 pixels du kernel (8-bit -> 32-bit)
    pmovzxbd (%ebx), %xmm2
    
    # Calcul de la différence
    psubd %xmm2, %xmm1      # img_pixels - kernel_pixels
    
    # Mise au carré des différences
    pmulld %xmm1, %xmm1     # (img_pixels - kernel_pixels)²
    
    # Accumulation des carrés
    paddd %xmm1, %xmm0      # sum += squared_differences
    
    # Incrémentation de kx par 4 (traitement de 4 pixels à la fois)
    addl $4, kx
    jmp inner_loop

end_inner_loop:
    # Incrémentation de ky
    incl ky
    jmp outer_loop

end_outer_loop:
    # Réduction horizontale pour obtenir la somme finale
    # %xmm0 contient [a, b, c, d], on veut a+b+c+d
    phaddd %xmm0, %xmm0     # %xmm0 = [a+b, c+d, a+b, c+d]
    phaddd %xmm0, %xmm0     # %xmm0 = [a+b+c+d, a+b+c+d, a+b+c+d, a+b+c+d]
    
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
