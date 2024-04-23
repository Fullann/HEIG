@ Stack Pointer SP = r5
@ Link Register LR = r6
@ Program Counter PC = r7

@ Ajouter le code d’initialisation de la pile

MOV r1, #0x26
BL FONCTION_A
ADD r4, r2, #3

.org 0x20
FONCTION_A:
@@@@@ Ajouter le code pour le PUSH
BL FONCTION_B
MOV r2, #0xFF
AND r2, r1
@@@@@ Ajouter le code pour le POP
MOV r7, r6

.org 0x40
FONCTION_B:
@@@@@ Ajouter le code pour le PUSH
LSL r2, r1, #4
ORR r2, r1
@@@@@ Ajouter le code pour le POP
MOV r7, r6
