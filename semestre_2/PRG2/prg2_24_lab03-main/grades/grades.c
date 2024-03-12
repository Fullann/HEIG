/*
===============================================================================
File:                   grades.c
Course:                 PRG2
Year:                   2024
Author:                 Clément Dieperink
Creation Date:          15.01.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This file implements a simple grade management for
                        one course.
===============================================================================
*/

#include <stdio.h>

#define ARRAY_SIZE 10

// Structure pour représenter une note
typedef struct
{
    float value;
} Grade;
// Fonction pour intervertir deux notes
void swap(Grade *a, Grade *b)
{
    Grade temp = *a;
    *a = *b;
    *b = temp;
}
void clearBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}
// Fonction pour ajouter une note
int addGrade(Grade grades[], int *numGrades)
{
    if (*numGrades == ARRAY_SIZE)
    {
        printf("Error: The array is already full.\n");
        return 1;
    }

    float newValue;

    while (1)
    {
        printf("Enter the new grade: ");
        scanf("%f", &newValue);
        // Vérifier que la note est dans la plage spécifiée
        if (newValue < 1.0 || newValue > 6.0)
        {
            printf("Error: Invalid grade. Please enter a grade between 1.0 and 6.0.\n");
            clearBuffer();
        }
        else
        {
            break;
        }
    }

    grades[*numGrades].value = newValue;
    (*numGrades)++;

    return 0;
}

// Fonction pour supprimer une note
int deleteGrade(Grade grades[], int *numGrades)
{
    if (*numGrades == 0)
    {
        printf("Error: The array is already empty.\n");
        return 1;
    }

    int indexToDelete;
    while (1)
    {
        printf("Enter the index of the grade to delete (1 to %d): ", *numGrades);
        scanf("%d", &indexToDelete);

        // Vérifier que l'index est valide
        if (indexToDelete < 1 || indexToDelete > *numGrades)
        {
            printf("Error: Invalid index. Please enter an index between 1 and %d.\n", *numGrades);
            clearBuffer();
        }
        else
        {
            break;
        }
    }
    // Décaler les notes à la suite de l'index à supprimer
    for (int i = indexToDelete - 1; i < *numGrades - 1; i++)
    {
        grades[i] = grades[i + 1];
    }

    (*numGrades)--;

    return 0;
}
// Fonction pour modifier une note
int modifyGrade(Grade grades[], int numGrades)
{
    if (numGrades == 0)
    {
        printf("Error: The array is empty. Cannot modify grades.\n");
        return 1;
    }

    int indexToModify;
    float newValue;
    while (1)
    {
        printf("Enter the index of the grade to modify (1 to %d): ", numGrades);
        scanf("%d", &indexToModify);

        // Vérifier que l'index est valide
        if (indexToModify < 1 || indexToModify > numGrades)
        {
            printf("Error: Invalid index. Please enter an index between 1 and %d.\n", numGrades);
            clearBuffer();
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        printf("Enter the new value for the grade: ");
        scanf("%f", &newValue);

        // Vérifier que la nouvelle note est dans la plage spécifiée
        if (newValue < 1.0 || newValue > 6.0)
        {
            printf("Error: Invalid grade. Please enter a grade between 1.0 and 6.0.\n");
            clearBuffer();
        }
        else
        {
            break;
        }
    }

    grades[indexToModify - 1].value = newValue;

    return 0;
}

// Fonction pour intervertir deux notes
int swapGrades(Grade grades[], int numGrades)
{
    if (numGrades < 2)
    {
        printf("Error: Not enough grades to swap.\n");
        return 1;
    }

    int index1, index2;

    printf("Enter the indexes of the two grades to swap (1 to %d), separated by a space: ", numGrades);
    scanf("%d %d", &index1, &index2);

    // Vérifier que les index sont valides
    if (index1 < 1 || index1 > numGrades || index2 < 1 || index2 > numGrades)
    {
        printf("Error: Invalid indexes. Please enter indexes between 1 and %d.\n", numGrades);
        return 1;
    }

    // Appeler la fonction de swap
    swap(&grades[index1 - 1], &grades[index2 - 1]);

    return 0;
}

// Fonction pour calculer la moyenne des notes
float computeAverage(Grade grades[], int numGrades)
{
    if (numGrades == 0)
    {
        printf("Error: The array is empty. Cannot compute average.\n");
        return -1.0;
    }

    float sum = 0.0;

    for (int i = 0; i < numGrades; i++)
    {
        sum += grades[i].value;
    }

    return sum / numGrades;
}

// Fonction pour afficher le menu principal
void displayMenu()
{
    printf("\n1: Add a grade\n");
    printf("2: Delete a grade\n");
    printf("3: Modify a grade\n");
    printf("4: Swap two grades\n");
    printf("5: Compute average\n");
    printf("6: Quit\n");
}

int main()
{
    Grade grades[ARRAY_SIZE];
    int numGrades = 0;
    displayMenu();

    while (1)
    {
        printf("\nGrades: ");
        if (numGrades == 0)
        {
            printf("There are no grades yet.\n");
        }
        else
        {
            for (int i = 0; i < numGrades; i++)
            {
                printf("%.1f ", grades[i].value);
            }
            printf("\n");
        }

        int choice;
        printf("Enter your choice (1 to 6): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addGrade(grades, &numGrades);
            break;
        case 2:
            deleteGrade(grades, &numGrades);
            break;
        case 3:
            modifyGrade(grades, numGrades);
            break;
        case 4:
            swapGrades(grades, numGrades);
            break;
        case 5:
        {
            float average = computeAverage(grades, numGrades);
            if (average != -1.0)
            {
                printf("Average: %.1f\n", average);
            }
        }
        break;
        case 6:
            printf("Quitting the program.\n");
            return 0;
        default:
            printf("Error: Invalid choice. Please enter a number between 1 and 6.\n");
            break;
        }
        printf("\n\n...\n\n");
        clearBuffer();
    }

    return 0;
}
