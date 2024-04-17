#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUBJECT_NAME_LENGTH 10
#define MAX_GRADES 10

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int addGrade(float *grades[], int numGrades[], char *subjectNames[]) {
    char subjectName[MAX_SUBJECT_NAME_LENGTH + 1];
    printf("Enter the subject name: ");
    scanf("%s", subjectName);
    clearBuffer();

    int subjectIndex = -1;
    for (int i = 0; i < numGrades[0]; i++) {
        if (strcmp(subjectName, subjectNames[i]) == 0) {
            subjectIndex = i;
            break;
        }
    }

    if (subjectIndex == -1) {
        printf("Subject not found.\n");
        return 1;
    }

    if (numGrades[subjectIndex + 1] == MAX_GRADES) {
        printf("Error: The %s subject is already full.\n", subjectNames[subjectIndex]);
        return 1;
    }

    float newValue;
    printf("Enter the grade value: ");
    scanf("%f", &newValue);
    clearBuffer();

    if (newValue < 1.0 || newValue > 6.0) {
        printf("Grade is not valid.\n");
        return 1;
    }

    grades[subjectIndex][numGrades[subjectIndex + 1]] = newValue;
    numGrades[subjectIndex + 1]++;

    return 0;
}

int deleteGrade(float *grades[], int numGrades[], char *subjectNames[]) {
    char subjectName[MAX_SUBJECT_NAME_LENGTH + 1];
    printf("Enter the subject name: ");
    scanf("%s", subjectName);
    clearBuffer();

    int subjectIndex = -1;
    for (int i = 0; i < numGrades[0]; i++) {
        if (strcmp(subjectName, subjectNames[i]) == 0) {
            subjectIndex = i;
            break;
        }
    }

    if (subjectIndex == -1) {
        printf("Subject not found.\n");
        return 1;
    }

    if (numGrades[subjectIndex + 1] == 0) {
        printf("Error: The %s subject is already empty.\n", subjectNames[subjectIndex]);
        return 1;
    }

    int position;
    printf("Enter the grade position: ");
    scanf("%d", &position);
    clearBuffer();

    if (position < 1 || position > numGrades[subjectIndex + 1]) {
        printf("Position is not valid.\n");
        return 1;
    }

    for (int i = position - 1; i < numGrades[subjectIndex + 1] - 1; i++) {
        grades[subjectIndex][i] = grades[subjectIndex][i + 1];
    }

    numGrades[subjectIndex + 1]--;

    return 0;
}

int modifyGrade(float *grades[], int numGrades[], char *subjectNames[]) {
    char subjectName[MAX_SUBJECT_NAME_LENGTH + 1];
    printf("Enter the subject name: ");
    scanf("%s", subjectName);
    clearBuffer();

    int subjectIndex = -1;
    for (int i = 0; i < numGrades[0]; i++) {
        if (strcmp(subjectName, subjectNames[i]) == 0) {
            subjectIndex = i;
            break;
        }
    }

    if (subjectIndex == -1) {
        printf("Subject not found.\n");
        return 1;
    }

    if (numGrades[subjectIndex + 1] == 0) {
        printf("Error: The %s subject is empty. Cannot modify grades.\n", subjectNames[subjectIndex]);
        return 1;
    }

    int position;
    printf("Enter the grade position: ");
    scanf("%d", &position);
    clearBuffer();

    if (position < 1 || position > numGrades[subjectIndex + 1]) {
        printf("Position is not valid.\n");
        return 1;
    }

    float newValue;
    printf("Enter the new value for the grade: ");
    scanf("%f", &newValue);
    clearBuffer();

    if (newValue < 1.0 || newValue > 6.0) {
        printf("Grade is not valid.\n");
        return 1;
    }

    grades[subjectIndex][position - 1] = newValue;

    return 0;
}

int swapGrades(float *grades[], int numGrades[], char *subjectNames[]) {
    char subjectName[MAX_SUBJECT_NAME_LENGTH + 1];
    printf("Enter the subject name: ");
    scanf("%s", subjectName);
    clearBuffer();

    int subjectIndex = -1;
    for (int i = 0; i < numGrades[0]; i++) {
        if (strcmp(subjectName, subjectNames[i]) == 0) {
            subjectIndex = i;
            break;
        }
    }

    if (subjectIndex == -1) {
        printf("Subject not found.\n");
        return 1;
    }

    if (numGrades[subjectIndex + 1] < 2) {
        printf("Error: Not enough grades to swap.\n");
        return 1;
    }

    int index1, index2;
    printf("Enter the two grades positions to swap: ");
    scanf("%d %d", &index1, &index2);
    clearBuffer();

    if (index1 < 1 || index1 > numGrades[subjectIndex + 1] || index2 < 1 || index2 > numGrades[subjectIndex + 1]) {
        printf("Error: Invalid positions.\n");
        return 1;
    }

    float temp = grades[subjectIndex][index1 - 1];
    grades[subjectIndex][index1 - 1] = grades[subjectIndex][index2 - 1];
    grades[subjectIndex][index2 - 1] = temp;

    return 0;
}

float computeAverage(float *grades[], int numGrades[], char *subjectNames[], int subjectIndex) {
    if (numGrades[subjectIndex + 1] == 0) {
        printf("No grades for %s.\n", subjectNames[subjectIndex]);
        return 0.0;
    }

    float sum = 0.0;
    for (int i = 0; i < numGrades[subjectIndex + 1]; i++) {
        sum += grades[subjectIndex][i];
    }

    return sum / numGrades[subjectIndex + 1];
}

void modifySubjectName(char *subjectNames[], int *nbsubject) {
    char oldName[MAX_SUBJECT_NAME_LENGTH + 1];
    printf("Enter the current name of the subject: ");
    scanf("%s", oldName);
    clearBuffer();

    int subjectIndex = -1;
    for (int i = 0; i < *nbsubject; i++) {
        if (strcmp(oldName, subjectNames[i]) == 0) {
            subjectIndex = i;
            break;
        }
    }

    if (subjectIndex == -1) {
        printf("Subject not found.\n");
        return;
    }

    char newName[MAX_SUBJECT_NAME_LENGTH + 1];
    printf("Enter the new name for the subject: ");
    scanf("%10s", newName);
    clearBuffer();

    strcpy(subjectNames[subjectIndex], newName);
}

void addSubject(int *numSubjects, char ***subjectNames) {
    if (*numSubjects == MAX_SUBJECT_NAME_LENGTH) {
        printf("Cannot add more subjects.\n");
        return;
    }

    char newName[MAX_SUBJECT_NAME_LENGTH + 1];
    printf("Enter the name for the new subject: ");
    scanf("%s", newName);
    clearBuffer();

    // Check if the new name is already used
    for (int i = 0; i < *numSubjects; i++) {
        if (strcmp(newName, (*subjectNames)[i]) == 0) {
            printf("Error: The new name is already in use.\n");
            return;
        }
    }

    // Reallocate memory for subjectNames to accommodate the new subject
    char **temp = realloc(*subjectNames, (*numSubjects + 1) * sizeof(char *));
    if (temp == NULL) {
        printf("Memory reallocation failed for subject names.\n");
        return;
    }
    *subjectNames = temp;

    // Allocate memory for the new subject name
    (*subjectNames)[*numSubjects] = malloc((MAX_SUBJECT_NAME_LENGTH + 1) * sizeof(char));
    if ((*subjectNames)[*numSubjects] == NULL) {
        printf("Memory allocation failed for subject name.\n");
        return;
    }

    // Copy the new name into the allocated memory
    strcpy((*subjectNames)[*numSubjects], newName);

    (*numSubjects)++;
}


void displayGrades(float *grades[], int numGrades[], char *subjectNames[]) {
    for (int i = 0; i < numGrades[0]; i++) {
        printf("%s\t: ", subjectNames[i]);
        if (numGrades[i + 1] == 0) {
            printf("No grades\n");
        } else {
            for (int j = 0; j < numGrades[i + 1]; j++) {
                printf("%.1f%s", grades[i][j], j == numGrades[i + 1] - 1 ? "\n" : ", ");
            }
        }
    }
}

void displayMenu() {
    printf("\n1: Add a grade\n");
    printf("2: Delete a grade\n");
    printf("3: Modify a grade\n");
    printf("4: Swap a grade\n");
    printf("5: Compute average\n");
    printf("6: Modify subject name\n");
    printf("7: Add a subject\n");
    printf("8: Quit\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./better_grades <N_SUBJECT> <MAX_GRADES>\n");
        return 1;
    }

    int nSubjects = atoi(argv[1]);
    int maxGrades = atoi(argv[2]);

    if (nSubjects <= 0 || maxGrades <= 0) {
        printf("Error: Invalid arguments. Please provide positive integer values for <N_SUBJECT> and <MAX_GRADES>.\n");
        return 1;
    }

    char **subjectNames = (char **)malloc(nSubjects * sizeof(char *));
    if (subjectNames == NULL) {
        printf("Memory allocation failed for subject names.\n");
        return 1;
    }

    for (int i = 0; i < nSubjects; i++) {
        subjectNames[i] = (char *)malloc((MAX_SUBJECT_NAME_LENGTH + 1) * sizeof(char));
        if (subjectNames[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            return 1;
        }
    }

    float ***grades = (float ***)malloc(nSubjects * sizeof(float **));
    if (grades == NULL) {
        printf("Memory allocation failed for grades.\n");
        return 1;
    }

    int *numGrades = (int *)malloc((nSubjects + 1) * sizeof(int));
    if (numGrades == NULL) {
        printf("Memory allocation failed for numGrades.\n");
        return 1;
    }

    numGrades[0] = nSubjects;

    for (int i = 0; i < nSubjects; i++) {
        grades[i] = (float **)malloc(maxGrades * sizeof(float *));
        if (grades[i] == NULL) {
            printf("Memory allocation failed for grades[%d].\n", i);
            return 1;
        }
        numGrades[i + 1] = 0;
        for (int j = 0; j < maxGrades; j++) {
            grades[i][j] = (float *)malloc(sizeof(float));
            if (grades[i][j] == NULL) {
                printf("Memory allocation failed for grades[%d][%d].\n", i, j);
                return 1;
            }
        }
    }

    for (int i = 0; i < nSubjects; i++) {
        char newName[MAX_SUBJECT_NAME_LENGTH + 1];
        printf("Enter the name for subject %d: ", i + 1);
        scanf("%s", newName);
        clearBuffer();

        // Check if the new name is already used
        for (int j = 0; j < i; j++) {
            if (strcmp(newName, subjectNames[j]) == 0) {
                printf("Error: The new name is already in use.\n");
                i--; // Re-prompt for the same subject index
                break;
            }
        }

        strcpy(subjectNames[i], newName);
    }

    displayMenu();

    int choice;
    do {
        displayGrades(*grades, numGrades, subjectNames);
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        clearBuffer();

        switch (choice) {
        case 1:
            addGrade(*grades, numGrades, subjectNames);
            break;
        case 2:
            deleteGrade(*grades, numGrades, subjectNames);
            break;
        case 3:
            modifyGrade(*grades, numGrades, subjectNames);
            break;
        case 4:
            swapGrades(*grades, numGrades, subjectNames);
            break;
        case 5:
            printf("Computing averages:\n");
            for (int i = 0; i < nSubjects; i++) {
                float average = computeAverage(*grades, numGrades, subjectNames, i);
                if (average != 0.0)
                    printf("%s\t: %.2f\n", subjectNames[i], average);
            }
            break;
        case 6:
            modifySubjectName(subjectNames, &nSubjects);
            break;
        case 7:
            addSubject(&nSubjects, &subjectNames);
            numGrades[0] = nSubjects;
            break;
        case 8:
            printf("Quitting the program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 8.\n");
            break;
        }
    }
    while (choice != 8);

    for (int i = 0; i < nSubjects; i++) {
        for (int j = 0; j < maxGrades; j++) {
            free(grades[i][j]);
        }
        free(grades[i]);
        free(subjectNames[i]);
    }
    free(grades);
    free(subjectNames);
    free(numGrades);

    return 0;
}
