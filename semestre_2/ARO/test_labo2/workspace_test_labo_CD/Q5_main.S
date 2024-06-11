@ programme Q5
MOV r0, #32
MOV r1, #7
MOV r2, #4
MOV r3, #12
MOV r4, #8
STRH r0, [r2, #4]
LDRH r3, [r2, #4]
SUB r3, #4
LDRH r1, [r2, #4]
LSL r2, r4
ADD r0, r3, r1
STRH r1, [r4, #4]
LDRH r0, [r4, #4]
NOP
NOP
NOP
NOP
NOP
