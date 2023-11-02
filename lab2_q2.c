#include <stdio.h>
#include <string.h>
#include <strings.h>

#define numOfSubjects 3
#define numOfStudents 3

typedef struct {
    char FirstName[10];
    char LastName[10];
    int StudentID;
    float SubjectMarks[numOfSubjects];
    int AggregateMarks;
    char Grade[10];
} students;

void setAggregate(students student[],int index, int numSubjects);
void setGrade(students student[], int index);
int checkID(students list[], int size, int ID);

void enrol(students list[], int size, int numSubjects);
void searchUpdate(students list[], int size, int numSubjects);
void topStudents(students list[], int size);

int main(void) {

    // Defines the array of structures
    students s[numOfStudents];

    // Initializing the struct
    for (int i = 0; i < numOfStudents; i++) {
        strcpy(s[i].FirstName,"");
        strcpy(s[i].LastName,"");
        s[i].StudentID = 0;
        for (int j = 0; j < numOfSubjects; j++) {
            s[i].SubjectMarks[j] = -1;
        }
        setAggregate(s, i, numOfSubjects);
        setGrade(s, i);
    }

    //
    while (1) {
        printf("\n1. Enrol\n2. Search & Update\n3. Show Top Students\n4. Display Details\n0. Exit\n");
        int choice;
        printf("\nEnter Choice (1/2/3/4/0): ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf("\nExiting Program...\n");
            break;
        }
        else if (choice == 1) {
            enrol(s, numOfStudents, numOfSubjects);
        }

        else if (choice == 2) {
            searchUpdate(s, numOfStudents, numOfSubjects);
        }

        else if (choice == 3) {
            topStudents(s, numOfStudents);
        }

        else if (choice == 4) {
            printf("\nFormat:\nFirst Name | Last Name | Student ID | {Subject Marks} | Aggregate Mark | Grade\n");
            for (int i = 0; i < numOfStudents; i++) {
                printf("%s | %s | %d | {" , s[i].FirstName, s[i].LastName, s[i].StudentID);
                for (int j = 0; j < numOfSubjects; j++) {
                    printf(" %.2f, ", s[i].SubjectMarks[j]);
                }
                printf("} | %d | %s\n", s[i].AggregateMarks, s[i].Grade);
            }
        }

        else {
            printf("Invalid Choice.\n");
        }
    }
    return 0;
}

int checkID(students list[], int size, int ID) {
    for (int i = 0; i < size; i++) {
        if (ID == list[i].StudentID) {
            return i;
        }
    }
    return -1;
}

void setAggregate(students student[], int index, int numSubjects) {
    int totalMarks = 0;
    int validMarkCount = 0;

    for (int i = 0; i < numSubjects; i++) {
        int mark = student[index].SubjectMarks[i];
        if (mark != -1) {
            totalMarks += student[index].SubjectMarks[i];
            validMarkCount++;
        }
    }

    if (validMarkCount == 0) {
        student[index].AggregateMarks = -1;
    }
    else {
        student[index].AggregateMarks = (totalMarks/validMarkCount);
    }
    return;
}

void setGrade(students student[], int index) {
    int marks = student[index].AggregateMarks;
    if (marks <= 100 && marks >= 85) {
        strcpy(student[index].Grade, "HD");
    }
    else if (marks <= 84 && marks >= 75) {
        strcpy(student[index].Grade, "D");
    }
    else if (marks <= 74 && marks >= 65) {
        strcpy(student[index].Grade, "C");
    }
    else if (marks <= 64 && marks >= 50) {
        strcpy(student[index].Grade, "P");
    }
    else if (marks <= 49 && marks >= 0) {
        strcpy(student[index].Grade, "F");
    }
    else {
        strcpy(student[index].Grade, "undefined");
    }
}

void enrol (students list[], int size, int numSubjects) {
    for (int stIndex = 0; stIndex < size; stIndex++) {

        char enrolChoice[5];
        printf("\nWould you like to enrol a new student (Yes/No) ? ");
        scanf("%s", enrolChoice);

        if (strcasecmp(enrolChoice, "No") == 0) {
            continue;
        }

        printf("\nEnter First Name: ");
        scanf("%s", list[stIndex].FirstName);
        printf("Enter Last Name: ");
        scanf("%s", list[stIndex].LastName);
        printf("\nEnter Student ID: ");
        scanf("%d", &list[stIndex].StudentID);

        /*
        int index = checkID(list, size, ID);
        if (index == -1) {
            printf("Invalid ID\n");
            return;
        }
        */

        char userPrompt[4];
        printf("\nWould you like to input marks for student %d? ", list[stIndex].StudentID);
        scanf("%s", userPrompt);

        if (strcasecmp(userPrompt, "No") == 0) {
            for (int i = 0; i < numSubjects; i++) {
                list[stIndex].SubjectMarks[i] = -1;
            }
        }
        else {
            for (int i = 0; i < numSubjects; i++) {
                printf("Enter marks for Subject %d: (-1 to skip) ", i);
                scanf("%f", &list[stIndex].SubjectMarks[i]);
            }
            setAggregate(list, stIndex, numSubjects);
            setGrade(list, stIndex);
        }

    }

    return;
}

void searchUpdate (students list[], int size, int numSubjects) {
    int searchChoice;
    printf("\nSearch by: \n1. Last Name\n2. Student ID\nEnter your choice: ");
    scanf("%d", &searchChoice);

    int index = -1;

    if (searchChoice == 1) {
        char sInput[10];
        printf("\nEnter Last Name: ");
        scanf("%s", sInput);

        for (int i = 0; i < size; i++) {
            if (strcasecmp(sInput, list[i].LastName)  == 0) {
                index = i;
            }
        }
    }
    else if (searchChoice == 2) {
        int IDinput;
        printf("\nEnter Student ID: ");
        scanf("%d", &IDinput);

        index = checkID(list, size, IDinput);
    }
    else {
        printf("\nInvalid Choice\n");
        return;
    }

    if (index == -1) {
        printf("\nInvalid Input\n");
        return;
    }

    printf("\nStudent Selected:\n");
    printf("\nFormat:\nFirst Name | Last Name | Student ID | {Subject Marks} | Aggregate Mark | Grade\n");
    printf("%s | %s | %d | {" , list[index].FirstName, list[index].LastName, list[index].StudentID);
    for (int i = 0; i < numOfSubjects; i++) {
        printf(" %.2f, ", list[index].SubjectMarks[i]);
    }
    printf("} | %d | %s\n", list[index].AggregateMarks, list[index].Grade);

    int changeChoice;
    printf("\n1. First Name\n2. Last Name\n3. Student ID\n4. Subject Marks\n");
    printf("\nEnter Number of Element you would like to change (1/2/3/4): ");
    scanf("%d", &changeChoice);

    if (changeChoice == 1) {
        printf("\nEnter New First Name: ");
        scanf("%s", list[index].FirstName);
    }
    else if (changeChoice == 2) {
        printf("\nEnter New Last Name: ");
        scanf("%s", list[index].LastName);
    }
    else if (changeChoice == 3) {
        printf("\nEnter New Student ID: ");
        scanf("%d", &list[index].StudentID);
    }
    else if (changeChoice == 4) {
        for (int i = 0; i < numSubjects; i++) {
            printf("Enter New Marks for Subject %d: (-1 to skip) ", i);
            scanf("%f", &list[index].SubjectMarks[i]);
        }
        setAggregate(list, index, numSubjects);
        setGrade(list, index);
    }
    else {
        printf("\nInvalid Input\n");
        return;
    }
    return;
}

void topStudents(students list[], int size) {
    int highestMark;

    for (int i = 0; i < size; i++) {
        if (highestMark < list[i].AggregateMarks) {
            highestMark = list[i].AggregateMarks;
        }
    }

    printf("Top Students:\n");
    for (int i = 0; i < size; i++) {
        if (highestMark == list[i].AggregateMarks) {
            printf("%s %s\n", list[i].FirstName, list[i].LastName);
        }
    }
}
