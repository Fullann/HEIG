@ Q3 PROGRAMME 2
MOV R0,#0x1 
MOV R1,#0x2
MOV R2,#0x6
MOV R3,#0x5
ADD R4,R0,#0x1
STRH R0,[R1,#0x4]
ADD R2,R0,#0x4
SUB R4,R1,R0
LSL R3,R0,#0x1
ADD R0,R3,#0x5
MOV R0,#0x8
NOP
NOP
NOP
NOP
NOP
