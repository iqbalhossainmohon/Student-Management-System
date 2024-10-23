
#ifndef LOGIN_H
#define LOGIN_H

struct User {
    char username[50];
    char password[50];
    char email[20];

    char fristName[15];
    char lestName[15];
    char gender[10];
    char phone[20];
};

void registerUser();
void login();

#endif

