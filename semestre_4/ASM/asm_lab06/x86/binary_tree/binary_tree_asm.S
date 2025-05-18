# Author : Prenom Nom

.global traverse_tree_asm

.extern printf

# Macro that will print what is at the end of string_ptr (char *)
# with an extra space at the end (through the format string used).
.macro PUT_S string_ptr
    pushal
    push \string_ptr
    push $format_string
    call printf
    add  $0x8, %esp
    popal
.endm

## @brief void traverse_tree_asm(Node *root);
## Traverses a binary search tree in natural order and prints data if available
##
## @param Node *root the root of the tree to traverse and prints
traverse_tree_asm:
        # Intro
        pushl %ebp                      # Save old stack frame
        movl  %esp, %ebp                # Set new stack base
        pushal                          # Save all registers
        movl  8(%ebp), %eax             # copy the argument in eax
	####### Student code below
	movl    $0, %ebx

        # while root != null OR size != 0
        while:
                cmpl    $0, %eax               # aller tout à gauche (tant que root ≠ null)
                jne     traverse_left           

                cmpl    $0, %ebx                # la pile est-elle vide ?
                je      end
        traverse_left:
                cmpl    $0, %eax                # s'il n'y a plus de nœud à gauche, tenter de traverser à droite
                je      traverse_right

                pushl   %eax                    # empiler le nœud courant
                incl    %ebx                    # augmenter la taille de la pile

                movl    0x8(%eax), %ecx         # aller vers le fils gauche
                movl    %ecx, %eax
                jmp     traverse_left
        traverse_right:
                popl    %eax                    # revenir d’un niveau et afficher le nœud
                decl    %ebx                    # diminuer la taille de la pile

                movl    0x4(%eax), %ecx         # afficher la valeur du nœud
                PUT_S   %ecx   

                movl    0xc(%eax), %ecx         # aller vers le fils droit
                movl    %ecx, %eax

                jmp     while
        end:
	######## End of student code
        # Outro
        popal                           # Restore all register
        leave                           # Restore stack frame
        ret                             # Return to caller

.data
format_string:
    .string "%s "
example_string:
    .string "Hello from ASM !"
