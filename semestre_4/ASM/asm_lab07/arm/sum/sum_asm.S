@     ___   _____ __  ______   ____ ___  ___ 
@    /   | / ___//  |/  /__ \ / __ \__ \|__ \
@   / /| | \__ \/ /|_/ /__/ // / / /_/ /__/ /
@  / ___ |___/ / /  / // __// /_/ / __// __/ 
@ /_/  |_/____/_/  /_//____/\____/____/____/ 
@
@ Author :

@@ @brief uint32_t sum_asm(uint32_t n, ...)
@@ Computes the sum of ... (uint32_t), 0 if empty
@@ @param n (r0) the number of elements in ...
@@ @param ... variable number of uint32_t elements
@@ @return sum of ... or 0 if empty
.global sum_asm
sum_asm:
        @@@@@@@@@@@ A completer @@@@@@@@@@
        @ L'espace vide vous donne une idée de la taille de la solution
        stmfd   sp!, {r1-r3}            @ Sauvegarde les registres r1 à r3 sur la pile
        stmfd   sp!, {fp, lr}           @ Sauvegarde le frame pointer et le link register
        add     fp, sp, #4              @ Met à jour le frame pointer

        add     sp, sp, #8              @ Saute les deux premiers arguments (r1 et r2) sur la pile
        eor     r1, r1, r1              @ Initialise r1 à 0 (somme)
        eor     r2, r2, r2              @ Initialise r2 à 0 (valeur temporaire)
        
        while:
        cmp     r0, #0                  @ Compare le compteur à 0
        beq     end                     @ Si compteur == 0, saute à la fin
        ldmfd   sp!, {r2}               @ Charge l'argument suivant dans r2
        add     r1, r1, r2              @ Ajoute r2 à la somme (r1)
        sub     r0, r0, #1              @ Décrémente le compteur
        b       while                   @ Retourne au début de la boucle
        
        end:
        mov     r0, r1                  @ Place la somme dans r0 (valeur de retour)
        
        @ épilogue
        sub     sp, fp, #4              @ Restaure la pile
        ldmfd   sp!, {fp, pc}           @ Restaure fp et retourne à l'appelant
        @@@@@@@@@@@ ----------- @@@@@@@@@@
