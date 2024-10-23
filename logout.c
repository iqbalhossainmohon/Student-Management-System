#include <stdio.h>
#include "logout.h"

// Global variable to track session state
int loggedIn = 0;

// Function to set login status
void setLoginStatus(int status) {
    loggedIn = status;
}

// Function to check if the user is logged in
int isLoggedIn() {
    return loggedIn;
}

// Function to log out the user
void logout() {
    if (isLoggedIn()) {
        setLoginStatus(0);
        printf("Logout successful. See you soon!\n");
    } else {
        printf("No user is currently logged in.\n");
    }
}
