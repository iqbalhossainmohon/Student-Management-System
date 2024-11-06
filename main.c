#include <stdio.h>
#include "login.h"
#include "student.h"
#include "logout.h"
#include "grading.h"

int main() {
    int choice;

    while (1) {
        printf("\n=============== Student Management System ===============\n");

        if (isLoggedIn()) {
            // Menu options when the user is logged in
            printf("3. Add Student\n4. View Students\n5. Update Student\n"
                   "6. Delete Student\n7. Search Student\n8. view Student Grades\n9. Logout\n10. Exit\n");
        } else {
            // Menu options when the user is not logged in
            printf("1. Register\n2. Login\n");
        }

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (!isLoggedIn()) {
            // User is not logged in, only allow registration or login
            switch (choice) {
                case 1:
                    registerUser();
                break;
                case 2:
                    login();
                break;
                default:
                    printf("Invalid choice. Please log in first.\n");
            }
        } else {
            // User is logged in, show all other options
            switch (choice) {
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
                    viewStudentGrades();
                break;
                case 9:
                    logout();
                break;
                case 10:
                    exit(0);
                default:
                    printf("Invalid choice.\n");
            }
        }
    }

    return 0;
}