#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

static const char *DICTIONNARY[] = {
    "programming",
    "computer",
    "algorithm",
    "game",
    "hangman",
    "code",
    "software",
    "developer",
    "language"};

#define NUM_WORDS (sizeof(DICTIONNARY) / sizeof(const char *))
#define MAX_TRIES 10

// Fonction pour choisir un mot aléatoirement
const char *choose_word()
{
    srand(time(NULL));
    return DICTIONNARY[rand() % NUM_WORDS];
}

// Fonction pour afficher l'état actuel du mot
void display_word(const char *word, const char *guessed_letters)
{
    int i;
    for (i = 0; i < strlen(word); i++)
    {
        if (strchr(guessed_letters, word[i]) != NULL)
        {
            printf("%c", word[i]);
        }
        else
        {
            printf("-");
        }
    }
    printf("\n");
}

// Vérifier si toutes les lettres du mot ont été devinées
int all_letters_guessed(const char *word, const char *guessed_letters)
{
    int i;
    for (i = 0; i < strlen(word); i++)
    {
        if (strchr(guessed_letters, word[i]) == NULL)
            return 0;
    }
    return 1;
}

int main(int argc, char **argv)
{
    int lifes = 10;

    // Vérifier si l'argument --lifes a été fourni
    if (argc == 3 && strcmp(argv[1], "--lifes") == 0)
    {
        lifes = atoi(argv[2]);
    }
    else if (argc > 1)
    {
        printf("Usage: %s [--lifes <n>]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *word = choose_word();
    char guessed_letters[26] = {0};
    int tries = 0;

    printf("Lifes: %d\n", lifes);
    printf("Tried letters:\n-------------\n");
    display_word(word, guessed_letters);

    while (tries < MAX_TRIES)
    {
        char guess[50];
        printf("\nGuess a letter or a word: ");
        scanf("%s", guess);
        // Vérifier si l'entrée est une lettre
        if (strlen(guess) == 1 && isalpha(guess[0]))
        {
            char letter = tolower(guess[0]);
            if (strchr(guessed_letters, letter) != NULL)
            {
                printf("%c has already been tried.\n", letter);
            }
            else if (strchr(word, letter) != NULL)
            {
                guessed_letters[strlen(guessed_letters)] = letter;
                printf("Correct guess!\n");
                display_word(word, guessed_letters);
                if (all_letters_guessed(word, guessed_letters))
                {
                    printf("\nGG !! You win \\o/\n");
                    return EXIT_SUCCESS;
                }
            }
            else
            {
                guessed_letters[strlen(guessed_letters)] = letter;
                tries++;
                printf("Wrong guess!\n");
                printf("Lifes: %d\n", lifes - tries);
                printf("Tried letters: %s\n", guessed_letters);
                display_word(word, guessed_letters);
            }
        }
        // Vérifier si l'entrée est un mot
        else if (strlen(guess) > 1 && isalpha(guess[0]))
        {
            if (strcmp(word, guess) == 0)
            {
                printf("\nGG !! You win \\o/\n");
                return EXIT_SUCCESS;
            }
            else
            {
                tries += 2;
                printf("\n%s isn't the word !\n", guess);
                printf("Lifes: %d\n", lifes - tries);
                printf("Tried letters: %s\n", guessed_letters);
                display_word(word, guessed_letters);
            }
        }
        // Si l'entrée n'est ni une lettre ni un mot
        else
        {
            printf("'%s' is not a valid input.\n", guess);
        }
    }

    printf("\nYou loose... The word was %s.\n", word);
    return EXIT_FAILURE;
}
