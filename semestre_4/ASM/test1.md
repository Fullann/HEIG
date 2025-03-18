### **Page 1/4 : Architecture des Processeurs**
#### **1. RISC vs CISC**
- **RISC (ARM)** : 
  - Instructions de taille fixe (32/16 bits en Thumb).
  - Nombreux registres généraux (r0-r12, sp, lr, pc).
  - Pipeline simple, accès mémoire via `ldr/str`.
  - Exemples : Microcontrôleurs, systèmes embarqués.
- **CISC (x86)** : 
  - Instructions de taille variable (1-17 octets).
  - Registres spécialisés (eax, ebx, esp, ebp, eflags).
  - Segmentation et pagination mémoire.
  - Exemples : Processeurs Intel/AMD.

#### **2. Microprocesseur vs Microcontrôleur**
- **Microprocesseur** : Cœur de calcul seul (CPU), connecté à des périphériques externes.
- **Microcontrôleur** : Intègre CPU, mémoire, périphériques (GPIO, UART, etc.) sur une puce. Ex : ARM Cortex.

#### **3. Mémoire et Adressage**
- **Endianness** :
  - **Little-endian** (x86) : Octet de poids faible en premier (`0x04 0x03 0x02 0x01` pour `0x01020304`).
  - **Big-endian** (ARM en mode réseau) : Octet de poids fort en premier.
- **Accès I/O** :
  - **x86** : Instructions dédiées (`in`, `out`).
  - **ARM** : Mémoire mappée (`ldr/str` sur adresses spécifiques).

#### **4. Registres Clés**
- **x86** :
  - `eax, ebx, ecx, edx` (généraux), `esp` (pile), `ebp` (base), `eip` (pointeur d'instruction), `eflags` (flags).
  - Segments : `cs` (code), `ds` (données), `ss` (pile).
- **ARM** :
  - `r0-r12` (généraux), `r13` (sp), `r14` (lr), `r15` (pc).
  - `cpsr` (Current Program Status Register) : Contient N, Z, C, V, bits d'interruption, mode d'exécution.

---

### **Page 2/4 : Programmation Système en C et Environnements**
#### **1. Programmation Bas Niveau en C**
- **Volatile** : 
  - Utilisé pour les registres matériels/variables modifiées par des interruptions.
  ```c
  volatile unsigned int *uart_reg = (volatile unsigned int*)0x20af630;
  ```
- **Manipulation de Bits** :
  - **SET** : `*reg |= mask;`
  - **CLEAR** : `*reg &= ~mask;`
  - **TOGGLE** : `*reg ^= mask;`

#### **2. Accès aux Registres Matériels**
- Exemple pour un GPIO :
  ```c
  #define GPIO_BASE 0x20af630
  volatile unsigned int *gpio = (volatile unsigned int*)GPIO_BASE;
  *gpio = 0x22; // Écriture
  ```

#### **3. Environnement Hôte-Cible**
- **Hôte** (PC) : Développement avec outils croisés (cross-compiler).
- **Cible** (ARM/x86) : Exécution du code via émulateur (QEMU) ou matériel réel.
- **Bootloader** (U-Boot) : Initialise le matériel et charge le noyau/application.

#### **4. Types de Comportement en C**
- **Défini** : Comportement standardisé (ex : variables statiques initialisées à 0).
- **Implémentation-défini** : Dépend du compilateur (ex : taille de `int`).
- **Non défini** : Comportement imprévisible (ex : déréférencement de pointeur NULL).

---

### **Page 3/4 : Chaîne de Compilation et Makefile**
#### **1. Toolchain Croisée**
- Composants :
  - **Cross-compiler** (ex : `arm-linux-gnueabi-gcc`).
  - **Assembleur** (traduit `.s` en `.o`).
  - **Linker** (lie les `.o` et librairies en exécutable).
- Processus :
  ```
  main.c → préprocesseur → compilateur → assembleur → main.o → linker → exécutable
  ```

#### **2. Makefile**
- **Structure** :
  ```makefile
  CC = gcc
  CFLAGS = -Wall
  OBJS = main.o module.o

  all: program

  program: $(OBJS)
      $(CC) $(OBJS) -o $@

  %.o: %.c
      $(CC) -c $< $(CFLAGS)

  clean:
      rm -f *.o program
  ```
- **Variables Automatiques** :
  - `$@` : Nom de la cible.
  - `$^` : Toutes les dépendances.
  - `$<` : Première dépendance.

#### **3. Directives de Compilation**
- **Sections** :
  - `.text` : Code exécutable.
  - `.data` : Variables initialisées.
  - `.bss` : Variables non initialisées.
- **Alignement** :
  - `.align 4` (ARM) : Aligne l'adresse sur 4 octets.

---

### **Page 4/4 : Assembleur ARM/x86**
#### **1. Structure d'un Fichier Assembleur**
- **Labels** : Définissent des adresses (ex : `main:`).
- **Directives** :
  - `.global main` : Rend le symbole visible.
  - `.word 0x1234` : Déclare un mot de 32 bits.
  - `.asciz "Hello"` : Chaîne de caractères terminée par `\0`.

#### **2. Instructions Clés**
- **ARM** :
  - `mov r0, #5` : Charge 5 dans r0.
  - `ldr r1, [r2]` : Charge la valeur à l'adresse r2 dans r1.
  - `bl function` : Appel de fonction (sauvegarde l'adresse de retour dans lr).
- **x86** :
  - `mov eax, 5` : Charge 5 dans eax.
  - `add ebx, ecx` : ebx = ebx + ecx.
  - `call function` : Appel de fonction.

#### **3. Gestion de la Pile**
- **ARM** :
  ```asm
  push {r0-r3}   ; Empile r0-r3
  pop {r0-r3}    ; Dépile
  ```
- **x86** :
  ```asm
  push eax        ; Empile eax
  pop ebx         ; Dépile dans ebx
  ```

#### **4. Exemple de Code**
- **ARM (Boucle)** :
  ```asm
  mov r0, #0         ; Compteur
  loop:
    add r0, r0, #1
    cmp r0, #10
    bne loop
  ```
- **x86 (Accès Mémoire)** :
  ```asm
  mov eax, [ebx]     ; Charge la valeur à l'adresse ebx dans eax
  mov [ecx], eax     ; Stocke eax à l'adresse ecx
  ```

-