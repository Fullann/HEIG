#     ___   _____ __  ______   ____ ___  ___ 
#    /   | / ___//  |/  /__ \ / __ \__ \|__ \
#   / /| | \__ \/ /|_/ /__/ // / / /_/ /__/ /
#  / ___ |___/ / /  / // __// /_/ / __// __/ 
# /_/  |_/____/_/  /_//____/\____/____/____/ 
#
# Author :

.text

## @brief uint32_t fib_asm(uint32_t n)
## Computes the nth Fibonacci number recursively
## Fib(0) = 0, Fib(1) = 1, Fib(n) = Fib(n-1) + Fib(n-2) for n > 1
## @param n the nth number we want as a result
## @return the nth Fibonacci number 0, 1, 1, 2, 3, 5, 8 etc...
.global silly_fib_asm
.type fib_asm, @function
silly_fib_asm:
#   @@@@@@@@@@@ A completer @@@@@@@@@@
    # prologue
    push    %ebp
    mov     %esp, %ebp

    mov     8(%ebp), %eax    # n
    cmp     $2, %eax        
    
    jl      1f             # if n < 2, return n
    push    %ebx            # save ebx
    dec     %eax            # n-1
    push    %eax            # push n-1
    
    call    silly_fib_asm   # fib(n-1)
    mov     %eax, %ebx      # save fib(n-1) in ebx
    decl    (%esp)          # n-2
    
    call    silly_fib_asm   # fib(n-2)
    add     %ebx, %eax      # fib(n-1) + fib(n-2)
    add     $4, %esp        # pop n-2
    pop     %ebx            # restore ebx
    
    1:
    # epilogue
    leave
    ret
    
#   @@@@@@@@@@@ ----------- @@@@@@@@@@

## @brief uint32_t fib_asm(uint32_t n, uint32_t a = 0, uint32_t b = 1)
## Computes the nth Fibonacci number recursively
## Fib(0) = 0, Fib(1) = 1, Fib(n) = Fib(n-1) + Fib(n-2) for n > 1
## @param n the nth number we want as a result
## @param a,b used for recursion
## @return the nth Fibonacci number 0, 1, 1, 2, 3, 5, 8 etc...
.global fib_asm
.type fib_asm, @function
fib_asm:
#   @@@@@@@@@@@ A completer @@@@@@@@@@

    push    %ebp            # Sauvegarde la base de pile précédente 
    mov     %esp, %ebp      # Crée un nouveau cadre de pile

    sub     $12, %esp       # Réserve de l'espace sur la pile pour a, b et n

    mov     8(%ebp), %eax   # Charge n dans %eax
    mov     12(%ebp), %edx  # Charge a dans %edx
    mov     16(%ebp), %ecx  # Charge b dans %ecx

    cmp     $0, %eax        # Compare n à 0
    je      10f             # Si n == 0, saute à l'étiquette 10 (retourne a)

    cmp     $1, %eax        # Compare n à 1
    je      11f             # Si n == 1, saute à l'étiquette 11 (retourne b)
    
    dec     %eax            # Décrémente n (n-1)
    add     %edx, %ecx      # Calcule b + a et stocke le résultat dans %ecx
    mov     16(%ebp), %edx  # Met à jour a avec la valeur de b

    push    %ecx            # Empile b+a (nouveau b)
    push    %edx            # Empile b (nouveau a)
    push    %eax            # Empile n-1
    
    call    fib_asm         # Appelle récursivement fib_asm(n-1, b, b+a)
    add     $12, %esp       # Libère l'espace réservé sur la pile (n-1, b, b+a)

    1:
    leave                   # Restaure le cadre de pile précédent
    ret                     # Retourne au programme appelant

    10:
    mov     %edx, %eax      # Place la valeur de a dans %eax (cas n == 0)
    jmp     1b              # Saute à l'étiquette 1 pour terminer

    11:
    mov     %ecx, %eax      # Place la valeur de b dans %eax (cas n == 1)
    jmp     1b              # Saute à l'étiquette 1 pour terminer
    

#   @@@@@@@@@@@ ----------- @@@@@@@@@@

## @brief uint32_t fib_asm(uint32_t n, uint32_t a = 0, uint32_t b = 1)
## Computes the nth Fibonacci number recursively
## Fib(0) = 0, Fib(1) = 1, Fib(n) = Fib(n-1) + Fib(n-2) for n > 1
## @param n the nth number we want as a result
## @param a,b used for recursion
## @return the nth Fibonacci number 0, 1, 1, 2, 3, 5, 8 etc...
.global fib_asm_tail
.type fib_asm_tail, @function
fib_asm_tail:
#   @@@@@@@@@@@ A completer @@@@@@@@@@
    push    %ebp
    mov     %esp, %ebp

    sub     $12, %esp       # reserve space for a, b and n

    push    %ebx            # save ebx

    mov    8(%ebp), %eax    # n
    mov    12(%ebp), %edx   # a
    mov    16(%ebp), %ecx   # b

    cmp     $0, %eax        
    je      1f              # if n == 0, return 0

    while:
    dec     %eax            # n-1

    cmp     $0, %eax        
    je      10f             # if n == 0, return b

    mov     %ecx, %ebx      # save b
    add     %edx, %ecx      # b = b + a
    mov     %ebx, %edx      # a = b
    jmp     while    

    1:
    add     $12, %esp       # pop n-1, b, b+a
    pop     %ebx            # restore ebx
    leave 
    ret

    10:
    mov     %ecx, %eax
    jmp     1b




#   @@@@@@@@@@@ ----------- @@@@@@@@@@
