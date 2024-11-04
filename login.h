
#ifndef LOGIN_H
#define LOGIN_H

struct User {
    char username[50];
    char password[50];
    char email[30];

    char firstName[50];
    char lastName[50];
    char gender[10];
    char phone[20];
};

void registerUser();
void login();

#endif

