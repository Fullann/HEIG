@ Programme pour la question 1

MOV r0, #255
MOV r2, #7
MOV r3, #6
LSL r0, r2
MOV r4, r0
NEG r0, r0
SUB r1, r0, r4
BVS SAUT_1
MOV r3, #4
B SAUT_2

.org 0x80
SAUT_1:
STRH r1, [r3, #4]

.org 0x82
SAUT_2:
LDRH r4, [r3, #4]
NOP

