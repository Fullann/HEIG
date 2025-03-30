# Author : 

.global parity_word
.global check_parity

# int parity_word(int value)
# input value in eax
# output in eax
parity_word:
        pushl %ebp                      # Save old stack frame
        movl  %esp, %ebp                # Set new stack base
        movl 8(%ebp), %eax              # copy the argument in eax
        pushl %ebx

        ########## A completer ##########
        mov %eax, %ebx
        shr $16, %ebx   

        xor %bh, %bl
        xor %ah, %bl
        mov %bl, %al    
        popl %ebx
        leave                           # Restore stack frame
        ret                             # Return to caller

# int check_word(int value)
# input value in eax
# output in eax
check_parity:
        pushl %ebp                      # Save old stack frame
        movl  %esp, %ebp                # Set new stack base
        movl 8(%ebp), %eax              # copy the argument in eax
        pushl %ebx

        ########## A completer ##########
        mov %eax, %ebx
        shr $16, %ebx           

        xor %bh, %bl            
        xor %ah, %bl            
        xor %bl, %al            
        movzbl %al, %eax  
        
        popl %ebx
        leave                           # Restore stack frame
        ret                             # Return to caller
