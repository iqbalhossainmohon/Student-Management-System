#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structures for User and Student
struct User {
    char username[50];
    char password[50];
};

struct Student {
    int rollNo;
    char name[100];
    int age;
    float grade;
};

// File paths for storing data
#define USER_FILE "users.dat"
#define STUDENT_FILE "students.dat"

// Utility functions to handle file I/O for users
void saveUser(struct User user) {
    FILE *file = fopen(USER_FILE, "ab");
    if (file != NULL) {
        fwrite(&user, sizeof(struct User), 1, file);
        fclose(file);
    }
}

int loginUser(char *username, char *password) {
    FILE *file = fopen(USER_FILE, "rb");
    struct User user;

    if (file == NULL) {
        printf("No users registered yet.\n");
        return 0;
    }

    while (fread(&user, sizeof(struct User), 1, file)) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            fclose(file);
            return 1;  // Successful login
        }
    }
    fclose(file);
    return 0;  // Invalid credentials
}

// Functions for login/registration
void registerUser() {
    struct User newUser;
    printf("Enter a username: ");
    scanf("%c", newUser.username);
    printf("Enter a password: ");
    scanf("%s", newUser.password);

    saveUser(newUser);
    printf("Registration successful.\n");
}

void login() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (loginUser(username, password)) {
        printf("Login successful! Welcome, %s.\n", username);
    } else {
        printf("Invalid username or password.\n");
    }
}

// Functions to manage student records
void addStudent() {
    struct Student newStudent;
    FILE *file = fopen(STUDENT_FILE, "ab");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter roll number: ");
    scanf("%d", &newStudent.rollNo);
    getchar();  // Clear buffer
    printf("Enter student name: ");
    fgets(newStudent.name, 100, stdin);  // Accepts string input with spaces
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;  // Remove newline character
    printf("Enter age: ");
    scanf("%d", &newStudent.age);
    printf("Enter grade: ");
    scanf("%f", &newStudent.grade);

    fwrite(&newStudent, sizeof(struct Student), 1, file);
    fclose(file);
    printf("Student added successfully.\n");
}

void viewStudents() {
    struct Student student;
    FILE *file = fopen(STUDENT_FILE, "rb");

    if (file == NULL) {
        printf("No students found.\n");
        return;
    }

    printf("Student Records:\n");
    printf("Roll No \t Name \t\t\t Age \t Grade \t\n");
    while (fread(&student, sizeof(struct Student), 1, file)) {

       /* printf("Roll No: %d, Name: %s, Age: %d, Grade: %.2f\n",
        student.rollNo, student.name, student.age, student.grade);
        */

        printf("%d \t\t %s \t\t %d \t  %.2f\n", student.rollNo, student.name, student.age, student.grade);
    }
    fclose(file);
}

void updateStudent() {
    int rollNo, found = 0;
    struct Student student;
    FILE *file = fopen(STUDENT_FILE, "rb+");

    if (file == NULL) {
        printf("No students found.\n");
        return;
    }

    printf("Enter roll number of the student to update: ");
    scanf("%d", &rollNo);

    while (fread(&student, sizeof(struct Student), 1, file)) {
        if (student.rollNo == rollNo) {
            printf("Enter new name: ");
            getchar();  // Clear buffer
            fgets(student.name, 100, stdin);
            student.name[strcspn(student.name, "\n")] = 0;  // Remove newline character
            printf("Enter new age: ");
            scanf("%d", &student.age);
            printf("Enter new grade: ");
            scanf("%f", &student.grade);

            fseek(file, -sizeof(struct Student), SEEK_CUR);
            fwrite(&student, sizeof(struct Student), 1, file);
            found = 1;
            break;
        }
    }
    fclose(file);

    if (found) {
        printf("Student record updated.\n");
    } else {
        printf("Student not found.\n");
    }
}

void deleteStudent() {
    int rollNo, found = 0;
    struct Student student;
    FILE *file = fopen(STUDENT_FILE, "rb");
    FILE *tempFile = fopen("temp.dat", "wb");

    if (file == NULL) {
        printf("No students found.\n");
        return;
    }

    printf("Enter roll number of the student to delete: ");
    scanf("%d", &rollNo);

    while (fread(&student, sizeof(struct Student), 1, file)) {
        if (student.rollNo != rollNo) {
            fwrite(&student, sizeof(struct Student), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(STUDENT_FILE);
    rename("temp.dat", STUDENT_FILE);

    if (found) {
        printf("Student record deleted.\n");
    } else {
        printf("Student not found.\n");
    }
}

void searchStudent() {
    int rollNo, found = 0;
    struct Student student;
    FILE *file = fopen(STUDENT_FILE, "rb");

    if (file == NULL) {
        printf("No students found.\n");
        return;
    }

    printf("Enter roll number to search: ");
    scanf("%d", &rollNo);

    while (fread(&student, sizeof(struct Student), 1, file)) {
        if (student.rollNo == rollNo) {

            /*printf("Record found: Roll No: %d, Name: %s, Age: %d, Grade: %.2f\n",
                   student.rollNo, student.name, student.age, student.grade);
            */
            printf("Roll No \tName \t\t\tAge \t Grade \t\n");
            printf(" %d \t\t %s \t\t %d \t  %.2f\n", student.rollNo,
                student.name, student.age, student.grade);

            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Student not found.\n");
    }
}

// Main menu and program flow
int main() {
    int choice;

    while (1) {
        printf("\n=============== Student Management System ===============\n");
        printf("\n1. Register\n2. Login\n3. Add Student\n4. View Students\n5. Update Student\n6. Delete Student\n7. Search Student\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                login();
                break;
            case 3:
                addStudent();
                break;
            case 4:
                viewStudents();
                break;
            case 5:
                updateStudent();
                break;
            case 6:
                deleteStudent();
                break;
            case 7:
                searchStudent();
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
