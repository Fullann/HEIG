@ ASM
@ Author :

@@ @brief uint32_t manhattan_distance_asm(const uint32_t a, const uint32_t b)
@@ Computes the Manhattan distance between a and b
@@ @param a (r0)
@@ @param b (r1)
@@ @return distance in r0
.global manhattan_distance_asm
manhattan_distance_asm:
	mov   r12, sp
        stmfd sp!, {r4-r12, lr}

        @@@@@@@@@@@ A completer @@@@@@@@@@

        unpack  r0, r2, r3              @ r2 = X_A, r3 = Y_A
        unpack  r1, r4, r5              @ r4 = X_B, r5 = Y_B

        absdiff r2, r2, r4              @ r2 = |X_A - X_B|
        absdiff r3, r3, r5              @ r3 = |Y_A - Y_B|
        
        mov     r0, #0
        add     r0, r2, r3             @ r0 = |X_A - X_B| + |Y_A - Y_B|

	@@@@@@@@@@@ ----------- @@@@@@@@@@

        ldmfd sp!, {r4-r12, lr}
        mov   sp, r12
        mov   pc, lr

@@ @brief uint32_t ssd_semi_distance_asm(const uint32_t a, const uint32_t b)
@@ Computes the Sum of Squared Differences semi distance between a and b
@@ @param a (r0)
@@ @param b (r1)
@@ @return distance in r0
.global ssd_semi_distance_asm
ssd_semi_distance_asm:
	mov   r12, sp
        stmfd sp!, {r4-r12, lr}

        @@@@@@@@@@@ A completer @@@@@@@@@@

        unpack  r0, r2, r3              @ r2 = X_A, r3 = Y_A
        unpack  r1, r4, r5              @ r4 = X_B, r5 = Y_B
        absdiff r2, r2, r4              @ r2 = |X_A - X_B|
        absdiff r3, r3, r5              @ r3 = |Y_A - Y_B|
        mul     r2, r2, r2              @ r2 = |X_A - X_B|^2
        mul     r3, r3, r3              @ r3 = |Y_A - Y_B|^2
        add     r0, r2, r3              @ r0 = |X_A - X_B|^2 + |Y_A - Y_B|^2

	@@@@@@@@@@@ ----------- @@@@@@@@@@

        ldmfd sp!, {r4-r12, lr}
        mov   sp, r12
        mov   pc, lr

