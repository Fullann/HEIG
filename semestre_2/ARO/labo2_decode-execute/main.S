@ Programme Pour la validation

START:
MOV r0, #15
MOV r1, #26
MOV r3, #5
ADD r0, r0, #17
ADD r2, r0, r3
ADD r2, #1
SUB r3, r1, r2
SUB r4, r1, #2
SUB r1, #29

STEP_1:
MOV r1, #4
STRH r3, [r0, #8]
ORR r1, r0
LDRH r2, [r0, #8]

STEP_2:
STRB r2, [r1, #2]
LDRB r0, [r1, #2]

STEP_3:
STRB r4, [r0, r1]
LDRB r2, [r0, r1]

STEP_4:
STRH r3, [r0, r1]
LDRH r4, [r0, r1] 
AND r0, r2
LSL r0, r0, #2
LSR r0, r0, #3

STEP_5:
ORR r0, r2
NEG r4, r0
EOR r4, r3
MOV r0, #2
ROR r2, r0
MVN r2, r3

STEP_6:
ASR r2, r0
ASR r2, r3, #2

STEP_7:
MOV r0, #0
MOV r1, #0
ADD r2, r0, r1
BEQ STEP_8
MOV r0, #12

STEP_8:
B STEP_10

STEP_9:
MOV r1, #0

.org 0x60
STEP_10: 
MOV r0, #42
MOV r1, #60
NOP
NOP
