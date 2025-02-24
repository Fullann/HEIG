# Labo 01
Nathan Füllemann
## Questions
### Etape 3
*Depuis la fonction « main() », appeler cette fonction en lui fournissant en paramètre une chaîne de caractère préalablement déclarée sur la pile (stack). Affichez ensuite le contenu de cette nouvelle chaîne de caractères.*
- L'exercice doit être réalisé sans utiliser la fonction memcpy() ou strcpy(). 
```c
char *allocate_string(const char *string, int length) {
    char *new_string = (char *)malloc((length + 1) * sizeof(char));

    if (new_string == NULL) {
        fprintf(stderr, "Err");
        return NULL;
    }

    for (int i = 0; i < length; i++) {
        new_string[i] = string[i];
    }

    new_string[length] = '\0';

    return new_string;
}

int main(int argc, char **argv) {
    printf("Welcome to ASM\n");
    char original[] = "Hello, ASM!";

    int length = strlen(original);

    char *copied_string = allocate_string(original, length);

	if (copied_string != NULL) {
		printf("Chaîne copiée : %s\n", copied_string);
		free(copied_string);
    }
    return 0;
}
```
  *Quelle différence y a-t-il entre sizeof et strlen ? Quelle différence entre l’utilisation de char * ou de char[] ?* 

### Différence entre sizeof et strlen
| Fonction | Description | Exemple avec "Hello" |
|----------|------------|----------------------|
| sizeof | Renvoie la taille en octets d'un objet ou d'un type (tableau, structure, etc.). | sizeof("Hello") retourne 6 (car Hello + \0) |
| strlen | Renvoie la longueur d'une chaîne de caractères (sans compter le \0). | strlen("Hello") retourne 5 |

#### Exemple :
```c
char str1[] = "Hello";
char *str2 = "Hello";

printf("%lu\n", sizeof(str1)); // 6 (caractères + '\0')
printf("%lu\n", sizeof(str2)); // 8 (taille d'un pointeur sur 64 bits)
printf("%lu\n", strlen(str1)); // 5
printf("%lu\n", strlen(str2)); // 5
```

*Remarque* : sizeof sur un tableau renvoie sa taille totale, tandis que sur un pointeur, il renvoie la taille du pointeur (4 ou 8 octets selon l'architecture).

---

### Différence entre char * et char[]
| Type | Description | Allocation | Modifiable ? |
|------|------------|------------|-------------|
| char *ptr | Pointeur vers une chaîne constante en lecture seule | Stocké en **mémoire constante** (section .rodata) | Non |
| char arr[] | Tableau de caractères stocké localement | Stocké sur la *pile (stack)* | Oui |

#### Exemple :
```c
char *str1 = "Hello"; // Stocké en mémoire constante, interdit de modifier
char str2[] = "Hello"; // Stocké sur la pile, modifiable

str2[0] = 'h'; // OK
str1[0] = 'h'; // Segmentation fault (erreur d'accès mémoire)
```
*Quelles données se trouvent sur la pile (stack) et sur le tas(heap) ? Regarder leur adresse.*

*Comment pourriez-vous tester le code afin de vous assurer que le caractère NULL soit bien copié ?*

### Etape 5
```c
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <libleds.h>


int main(int argc, char **argv) {
    init_reg_leds();

    uint32_t leds = get_reg_leds();

    leds ^= 0xFFFFFF;

    set_reg_leds(leds);

    return 0;
}
```
### Etape 6
```c
#include <stdio.h>

int check_endianness() {
    union {
    	unsigned int i;
        char c[4];
    } test_union = {0x01020304};

    return test_union.c[0] == 1 ? 0 : 1;
}

int main(int argc, char **argv) {
    if (check_endianness())
        printf("This machine is little-endian.\n");
    else
        printf("This machine is big-endian.\n");
    
    return 0;
}

```
