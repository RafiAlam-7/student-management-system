#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char rollno[10];
    char name[50];
    float gpa;
};

void addStudent() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.txt", "a");
    if(fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter roll number: ");
    scanf("%s", s.rollno);
    printf("Enter full name: ");
    getchar(); // Clear input buffer
    scanf("%[^\n]s", s.name);
    printf("Enter GPA (0.00 - 4.00): ");
    scanf("%f", &s.gpa);

    fprintf(fp, "%s %s %.2f\n", s.rollno, s.name, s.gpa);
    fclose(fp);
    printf("\nStudent added successfully!\n");
}

void displayStudents() {
    FILE *fp;
    struct Student s;
    char line[100];

    fp = fopen("students.txt", "r");
    if(fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("|\tRoll No\t|\tName\t\t\t|\tGPA\t|\n");
    printf("----------------------------------------------------------------\n");

    while(fgets(line, sizeof(line), fp)) {
        if(sscanf(line, "%s %[^0-9] %f", s.rollno, s.name, &s.gpa) == 3) {  // Verify successful read
            printf("|\t%s\t|\t%-20s\t|\t%.2f\t|\n", s.rollno, s.name, s.gpa);
            printf("----------------------------------------------------------------\n");
        }
    }

    fclose(fp);
}

void deleteStudent() {
    FILE *fp, *temp;
    struct Student s;
    char searchRoll[10];
    char line[100];
    int found = 0;

    printf("\nEnter Roll Number to delete : ");
    scanf("%s", searchRoll);

    fp = fopen("students.txt", "r");
    temp = fopen("temp.txt", "w");

    if(fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while(fgets(line, sizeof(line), fp)) {
        sscanf(line, "%s %[^0-9] %f", s.rollno, s.name, &s.gpa);
        if(strcmp(s.rollno, searchRoll) != 0) {
            fprintf(temp, "%s %s %.2f\n", s.rollno, s.name, s.gpa);
        } else {
           found = 1;
       }
    }

    fclose(fp);
    fclose(temp);
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(found)
        printf("\nStudent deleted successfully!\n");
    else
        printf("\nStudent not found!\n");
}

void searchStudent() {
    FILE *fp;
    struct Student s;
    char searchRoll[10];
    char line[100];
    int found = 0;

    printf("\nEnter Roll Number to search ");
    scanf("%s", searchRoll);

    fp = fopen("students.txt", "r");
    if(fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while(fgets(line, sizeof(line), fp)) {
        sscanf(line, "%s %[^0-9] %f", s.rollno, s.name, &s.gpa);
        if(strcmp(s.rollno, searchRoll) == 0) {
            printf("\n=== Student Found ===\n");
            printf("Roll Number: %s\n", s.rollno);
            printf("Name: %s\n", s.name);
            printf("GPA: %.2f\n", s.gpa);
           found = 1;
            break;
        }
    }

    if(!found) {
        printf("\nStudent with Roll Number %s not found!\n", searchRoll);
    }

    fclose(fp);
}

int main() {
    int choice;

    while(1) {
        printf("\nStudent Record System\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Delete Student\n");
        printf("4. Search Student\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: deleteStudent(); break;
            case 4: searchStudent(); break;
            case 5:
                printf("Thank you for using the program!\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

