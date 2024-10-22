#include <stdio.h>
#include <string.h>
#include "login.h"

// File path for user data
#define USER_FILE "users.csv"

// Utility function to save a user
void saveUser(struct User user) {
    FILE *file = fopen(USER_FILE, "a");
    if (file != NULL) {
        fprintf(file, "%s, %s, %s\n",user.email, user.username, user.password);
        fclose(file);
    }
}

// Function to validate login
int loginUser(char *email, char *password) {
    FILE *file = fopen(USER_FILE, "r");
    struct User user;

    if (file == NULL) {
        printf("No users registered yet.\n");
        return 0;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,], %[^,],%s", user.email,user.username, user.password);
        if (strcmp(user.email, email) == 0 && strcmp(user.password, password) == 0) {
            fclose(file);
            return 1;  // Successful login
        }
    }
    fclose(file);
    return 0;  // Invalid credentials
}

// Function to register a new user
void registerUser() {
    struct User newUser;
    printf("Enter email address: ");
    scanf("%s",newUser.email);
    printf("Enter a username: ");
    scanf("%s", newUser.username);
    printf("Enter a password: ");
    scanf("%s", newUser.password);


    saveUser(newUser);
    printf("Registration successful.\n");
}

// Function to handle user login
void login() {
    char  email[20], password[50];
    printf("Enter email: ");
    scanf("%s", email);
    printf("Enter password: ");
    scanf("%s", password);

    if (loginUser(email, password)) {
        printf("Login successful! Welcome, %s.\n", email);
    } else {
        printf("Invalid username or password.\n");
    }
}
