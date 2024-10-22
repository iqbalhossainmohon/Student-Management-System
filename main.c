#include <stdio.h>
#include "login.h"
#include "student.h"

int main() {
    int choice;

    while (1) {
        printf("\n=============== Student Management System ===============\n");
        printf("\n1. Register\n2. Login\n3. Add Student\n4. View Students\n"
               "5. Update Student\n6. Delete Student\n7. Search Student\n8. Exit\n");
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
