@ programme Q1
mov r1,#4
mov r2,#0x23
mov r3,#0x9
mov r4,#0x18
lsl r0,r2, #4 
orr r0,r3 
STRH r0, [r4, #2]
LDRH r3, [r4, #2]
mov r1,#0x10
sub r3,r3,r1
nop
nop
nop
nop
nop
