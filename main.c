#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a structure for storing user information
struct User {
    char username[50];
    char password[50];
};

// Function to register a user
void registerUser() {
    struct User newUser;
    FILE *file;

    // Open the file in append mode to add new users
    file = fopen("users.dat", "a");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Get user details
    printf("Enter a username: ");
    scanf("%s", newUser.username);
    printf("Enter a password: ");
    scanf("%s", newUser.password);

    // Write user data to the file
    fwrite(&newUser, sizeof(struct User), 1, file);

    fclose(file);
    printf("Registration successful!\n");
}

// Function to login a user
int loginUser() {
    struct User user;
    char username[50], password[50];
    FILE *file;

    // Open the file in read mode to check login credentials
    file = fopen("users.dat", "r");

    if (file == NULL) {
        printf("No users registered yet. Please register first!\n");
        return 0;
    }

    // Get login details from the user
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    // Read the file and check if the username and password match
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
            fclose(file);
            printf("Login successful!\n");
            return 1;
        }
    }

    fclose(file);
    printf("Invalid username or password!\n");
    return 0;
}

// Function to display the main menu
void displayMenu() {
    printf("\n=========== Student Management System ===========\n");
    printf("1. Register\n");
    printf("2. Login\n\n");
    printf("Choose an option: ");
}

int main() {
    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    printf("Welcome to the Student Management System!\n");
                }
                break;
            default:
                printf("Invalid choice!.\n");
        }

    } while (choice != 2);  // Exit loop after successful login

    return 0;
}
