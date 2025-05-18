@ ASM
@ Author :

@@ @brief void show_backtrace() prints the backtrace up to main()
.global show_backtrace
.equiv STACK_TOP, -1 
show_backtrace:
        stmfd sp!, {fp, lr}
        add fp, sp, #4

        @@@@@@@@@@@ A completer @@@@@@@@@@

        ldr r0, =backtrace_string
        bl printf

         mov     r2, fp                          @ sauvegarder le frame pointer dans r2

        while:
                ldr     r1, [r2]                @ lire l'adresse du frame pointer (registre de liaison)

                cmp     r1, #STACK_TOP          @ comparer le registre de liaison avec le sommet de la pile
                beq     end                     @ si égal, terminer la boucle

                stmfd   sp!, {r2}               @ sauvegarder r2 sur la pile
                ldr     r0, =format_string      @ charger l'adresse de la chaîne de format
                bl      printf                  @ appeler la fonction printf
                ldmfd   sp!, {r2}               @ restaurer la valeur de r2 depuis la pile
                
                ldr     r2, [r2, #-4]           @ obtenir le registre de liaison précédent
                cmp     r2, #STACK_TOP          @ comparer avec le sommet de la pile

                bne     while                   @ si différent, continuer la boucle
        
        end:

	@@@@@@@@@@@ ----------- @@@@@@@@@@
        sub sp, fp, #4
        ldmfd sp!, {fp, pc}

.data

backtrace_string:
        .string "\nBacktrace :\n----\n"

format_string:
        .string "Previous link register : 0x%p\n"