#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

void addStudent() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "ab");

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("\nStudent Added Successfully!\n");
}

void displayStudents() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nRoll: %d", s.roll);
        printf("\nName: %s", s.name);
        printf("\nMarks: %.2f\n", s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("\nStudent Found!\n");
            printf("Roll: %d\n", s.roll);
            printf("Name: %s\n", s.name);
            printf("Marks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nStudent Not Found!\n");
    }

    fclose(fp);
}

void deleteStudent() {
    FILE *fp, *temp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll != roll) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("\nStudent Deleted Successfully!\n");
    else
        printf("\nStudent Not Found!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: exit(0);
            default: printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}
