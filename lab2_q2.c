#include <stdio.h>
#include <string.h>
#include <strings.h>

//Defined symbolic constants that define the numbers of subjects and number of students
#define numOfSubjects 3
#define numOfStudents 4

//Structure definition
typedef struct {
    char FirstName[10];
    char LastName[10];
    int StudentID;
    float SubjectMarks[numOfSubjects];
    int AggregateMarks;
    char Grade[10];
} students;

//Custom functions to change the aggregate and grade of record
void setAggregate(students student[],int index, int numSubjects);
void setGrade(students student[], int index);

//Function required as per the lab handout
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

    while (1) {
        //Asks the user to input their choice
        printf("\n1. Enrol\n2. Search & Update\n3. Show Top Students\n4. Display Details\n0. Exit\n");
        int choice;
        printf("\nEnter Choice (1/2/3/4/0): ");
        scanf("%d", &choice);

        //Breaks from the infinite loop if the user chooses to
        if (choice == 0) {
            printf("\nExiting Program...\n");
            break;
        }

        //Enrols new students if the user chooses to
        else if (choice == 1) {
            enrol(s, numOfStudents, numOfSubjects);
        }

        //Searches and updates the chosen details
        else if (choice == 2) {
            searchUpdate(s, numOfStudents, numOfSubjects);
        }

        //Displays the full name of students with the highest aggregate marks
        else if (choice == 3) {
            topStudents(s, numOfStudents);
        }

        //Displays the details of all students
        else if (choice == 4) {
            printf("\nFormat: First Name | Last Name | Student ID | {Subject Marks} | Aggregate Mark | Grade\n");
            for (int i = 0; i < numOfStudents; i++) {
                if (strcasecmp(s[i].FirstName,"") != 0 && strcasecmp(s[i].LastName,"") != 0 && s[i].StudentID != 0) {
                    printf("%s | %s | %d | {" , s[i].FirstName, s[i].LastName, s[i].StudentID);
                    for (int j = 0; j < numOfSubjects; j++) {
                        printf(" %.2f, ", s[i].SubjectMarks[j]);
                    }
                    printf("} | %d | %s\n", s[i].AggregateMarks, s[i].Grade);
                }
            }
        }

        //Notifies if the choice entered by user is not valid
        else {
            printf("Invalid Choice.\n");
        }
    }
    return 0;
}

//Sets the aggregate marks of a studdent
void setAggregate(students student[], int index, int numSubjects) {
    int totalMarks = 0;
    int validMarkCount = 0;

    //Calculates the total marks of students if the mark is not -1
    for (int i = 0; i < numSubjects; i++) {
        int mark = student[index].SubjectMarks[i];
        if (mark != -1) {
            totalMarks += student[index].SubjectMarks[i];
            validMarkCount++;
        }
    }

    //Sets the aggregate of student if all of the subject marks are -1
    if (validMarkCount == 0) {
        student[index].AggregateMarks = -1;
    }

    //Sets the aggregate of student by dividing the total marks with the number of subjects whose mark is not -1
    else {
        student[index].AggregateMarks = (totalMarks/validMarkCount);
    }
    return;
}

//Sets the grade of the student
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

//Enrols a new student if the user chooses to
void enrol (students list[], int size, int numSubjects) {
    //Runs the loop by the number of students
    for (int stIndex = 0; stIndex < size; stIndex++) {

        //Asks the user if they choose to enrol a new student
        char enrolChoice[5];
        printf("\nWould you like to enrol a new student (Yes/No) ? ");
        scanf("%s", enrolChoice);

        //Breaks the loop if the user chooses not to enrol a new student
        if (strcasecmp(enrolChoice, "No") == 0) {
            return;
        }

        //Inputs the first name, last name and student ID to the new struct
        printf("\nEnter First Name: ");
        scanf("%s", list[stIndex].FirstName);
        printf("Enter Last Name: ");
        scanf("%s", list[stIndex].LastName);
        printf("\nEnter Student ID: ");
        scanf("%d", &list[stIndex].StudentID);

        //Asks the if they would like to input marks for the new student
        char userPrompt[4];
        printf("\nWould you like to input marks for student %d (Yes/No)? ", list[stIndex].StudentID);
        scanf("%s", userPrompt);

        //Sets mark for all subjects to -1 if the user chooses not to
        if (strcasecmp(userPrompt, "No") == 0) {
            for (int i = 0; i < numSubjects; i++) {
                list[stIndex].SubjectMarks[i] = -1;
            }
        }

        //Asks user to input marks for each subject
        else {
            for (int i = 0; i < numSubjects; i++) {
                printf("Enter marks for Subject %d: (-1 to skip) ", i);
                scanf("%f", &list[stIndex].SubjectMarks[i]);
            }
            //Sets the aggregate mark and grade once all subject marks are inputted
            setAggregate(list, stIndex, numSubjects);
            setGrade(list, stIndex);
        }

    }

    return;
}

void searchUpdate (students list[], int size, int numSubjects) {
    //Asks the user for their preffered search mode
    int searchChoice;
    printf("\nSearch by: \n1. Last Name\n2. Student ID\nEnter your choice: ");
    scanf("%d", &searchChoice);

    //Index is set initially set to -1 if student record is not found
    int index = -1;

    //Search by last name
    if (searchChoice == 1) {

        //Asks the user the last name of student they want to search
        char sInput[10];
        printf("\nEnter Last Name: ");
        scanf("%s", sInput);

        //Stores the index if the student record is found
        for (int i = 0; i < size; i++) {
            if (strcasecmp(sInput, list[i].LastName)  == 0) {
                index = i;
            }
        }
    }

    //Search by student ID
    else if (searchChoice == 2) {

        //Asks the user the student ID of student they want to search
        int IDinput;
        printf("\nEnter Student ID: ");
        scanf("%d", &IDinput);

        //Stores the index if the student record is found
        for (int i = 0; i < size; i++) {
            if (IDinput == list[i].StudentID) {
                index = i;
            }
        }
    }

    //Notifies the user if the search choice is invalid and exits the function
    else {
        printf("\nInvalid Choice\n");
        return;
    }

    //Notifies the user if the student record is not found and exits the function
    if (index == -1) {
        printf("\nStudent Not Found\n");
        return;
    }

    //Prints the record of the student selected
    printf("\nStudent Selected:\n");
    printf("\nFormat:\nFirst Name | Last Name | Student ID | {Subject Marks} | Aggregate Mark | Grade\n");
    printf("%s | %s | %d | {" , list[index].FirstName, list[index].LastName, list[index].StudentID);
    for (int i = 0; i < numOfSubjects; i++) {
        printf(" %.2f, ", list[index].SubjectMarks[i]);
    }
    printf("} | %d | %s\n", list[index].AggregateMarks, list[index].Grade);

    //Asks the user to choose the detail they want to change
    int changeChoice;
    printf("\n1. First Name\n2. Last Name\n3. Student ID\n4. Subject Marks\n");
    printf("\nEnter Number of Element you would like to change (1/2/3/4): ");
    scanf("%d", &changeChoice);

    //Updates the first name of student
    if (changeChoice == 1) {
        printf("\nEnter New First Name: ");
        scanf("%s", list[index].FirstName);
    }

    //Updates the last name of student
    else if (changeChoice == 2) {
        printf("\nEnter New Last Name: ");
        scanf("%s", list[index].LastName);
    }

    //Updates the student ID of student
    else if (changeChoice == 3) {
        printf("\nEnter New Student ID: ");
        scanf("%d", &list[index].StudentID);
    }

    //Updates the subject marks, aggregate mark and grade of student
    else if (changeChoice == 4) {
        for (int i = 0; i < numSubjects; i++) {
            printf("Enter New Marks for Subject %d: (-1 to skip) ", i);
            scanf("%f", &list[index].SubjectMarks[i]);
        }
        setAggregate(list, index, numSubjects);
        setGrade(list, index);
    }

    //Notifies the user if the choice is invalid
    else {
        printf("\nInvalid Input\n");
        return;
    }
    return;
}

//Returns the name of students with the highest mark
void topStudents(students list[], int size) {
    int highestMark;

    //Finds and stores the value of the highest aggregate mark
    for (int i = 0; i < size; i++) {
        if (highestMark < list[i].AggregateMarks) {
            highestMark = list[i].AggregateMarks;
        }
    }

    //Prints the first and last name of student with the highest mark
    printf("\nTop Students:\n");
    for (int i = 0; i < size; i++) {
        if (highestMark == list[i].AggregateMarks) {
            printf("%s %s\n", list[i].FirstName, list[i].LastName);
        }
    }
}