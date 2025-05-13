        # Authors :
        # File    : asm_filter.S
        # Date    :
        # AT&T Syntax

#include "image_processing.h"

.globl asm_filter
.type asm_filter, @function

.text
        # Function arguments :
        # ebp + 8  : address of source image data (pointer to unsigned 8 bits)
        # ebp + 12 : address of destination image data (already allocated)
        # ebp + 16 : width of the image (signed 32 bits)
        # ebp + 20 : height of the image (signed 32 bits)
        # ebp + 24 : x position of pixel (signed 32 bits)
        # ebp + 28 : y position of pixel (signed 32 bits)

asm_filter:
        pushl %ebp                      # Save old stack frame
        movl  %esp, %ebp                # Set new stack base
        pushl %esi                      # Save registers
        pushl %edi                      # Save registers
        pushl %ebx                      # Save registers

        # Copy of the arguments for easier access
        movl 8(%ebp),   %esi            # esi is for source
        movl 12(%ebp),  %edi            # edi is for destination

        movl 16(%ebp),  %eax
        movl %eax,      (width)         # width holds the width parameter
        movl 20(%ebp),  %eax
        movl %eax,      (height)        # height holds the height parameter
        movl 24(%ebp),  %eax
        movl %eax,      (x)             # x holds the x position
        movl 28(%ebp),  %eax
        movl %eax,      (y)             # y holds the y position

check_if_on_border:

        # TODO : Check if the current pixel is on the border of the image
        # when on border jump to copy_pixel else continue

           movl    (x), %eax               # eax contient la position x
        movl    (width), %ebx           # ebx contient la largeur de l'image
        decl    %ebx

        cmpl    %eax, %ebx              # comparer x avec la largeur
        je      copy_pixel              # ignorer ce pixel s'il est en bordure droite
        
        cmpl    $0, %eax                # comparer x avec 0
        je      copy_pixel              # ignorer ce pixel s'il est en bordure gauche

        # même chose pour y
        movl    (y), %eax
        movl    (height), %ebx            
        decl    %ebx

        cmpl    %eax, %ebx              # comparer y avec la hauteur
        je      copy_pixel              # ignorer ce pixel s'il est en bordure inférieure

        cmpl    $0, %eax                # comparer y avec 0
        je      copy_pixel              # ignorer ce pixel s'il est en bordure supérieure



emboss_filter:

        # TODO : Implement the emboss 3D filter
        # Copier le pixel de esi vers eax
        get_pixel x, y, width, %esi, %eax, %ebx
        
        subl    (width), %eax
        decl    %eax                    # eax contient le pixel en haut à gauche de l'image source

        movl    $edge_detection_3x3, %edx
        addl    $8, %edx                # edx pointe vers la fin du tableau du noyau (kernel)

        movl    $0, (it)                # itérateur
        movl    $0, (res)               # accumulateur

        xorl    %ebx, %ebx              # réinitialise ebx
        xorl    %ecx, %ecx              # réinitialise ecx

        loop:
                movzbl  (%eax), %ebx    # ebx contient le pixel courant (uint8_t)
                movsbl  (%edx), %ecx    # ecx contient la cellule actuelle du noyau (int8_t)
                imull   %ecx, %ebx      # calcule pixel_courant * cellule_noyau
                addl    %ebx, (res)     # ajoute le résultat à l'accumulateur res 

                cmpl    $2, (it)        
                jne     1f
                subl    $3, %eax        # revenir au début de la ligne
                addl    (width), %eax   # aller à la ligne suivante
                
                1:
                cmpl    $5, (it)
                jne     2f
                subl    $3, %eax         # revenir au début de la ligne
                addl    (width), %eax    # aller à la ligne suivante
                
                2:
                decl    %edx            # cellule suivante du noyau
                incl    %eax            # pixel suivant
                incl    (it)            # incrémenter l'itérateur

                cmpl    $9, (it)
                jne     loop

        # - si acc < 0 : acc = -acc


        cmpl    $0, (res)
        jge     1f
        negl    (res)
        
        # - if acc > 255 : acc = 255

        1:
        cmpl    $PIXEL_MAX, (res)
        jle     2f
        movl    $PIXEL_MAX, (res)

        2:
        # Copy pixel from edi to eax
        get_pixel x, y, width, %edi, %eax, %ebx

        movl  (res), %ebx               # copy result to a scratch register
        movl  %ebx, (%eax)              # copy the result to the destination

exit:
        popl %ebx                       # Restore registers
        popl %edi       	        # Restore registers
	popl %esi                       # Restore registers
	leave                           # Restore stack frame
	ret                             # Return to caller

copy_pixel:

        # TODO : Copy pixel from source to destination image

             # Copier le pixel de esi vers eax
        get_pixel x, y, width, %esi, %eax, %ebx
        
        xorl     %ebx, %ebx              # réinitialiser le registre ebx

        # Copier le pixel de edi vers ebx
        get_pixel x, y, width, %edi, %ebx, %ecx

        xorl     %ecx, %ecx              # réinitialiser le registre ecx

        movl    (%eax), %ecx            # Copier le pixel de la source dans un registre temporaire
        movl    %ecx, (%ebx)            # Copier depuis le registre temporaire vers la mémoire

        jmp exit                        # exit


.bss
        # Block Started by Symbol Section
        # space is 4 bytes because the values are 32 bit

width:                                  # image width
        .space 4
height:                                 # image height
        .space 4
x:                                      # x position of pixel
        .space 4
y:                                      # y position of pixel
        .space 4
res:                                    # result of convolution
        .space 4
