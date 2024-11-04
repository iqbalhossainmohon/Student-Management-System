
#ifndef LOGIN_H
#define LOGIN_H

struct User {
    char username[50];
    char password[50];
    char email[30];

    char fristName[50];
    char lestName[50];
    char gender[10];
    char phone[20];
};

void registerUser();
void login();

#endif

