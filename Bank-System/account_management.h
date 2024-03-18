#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char iban[25];
    char account_id[6];
    char password[20];
    float balance;
} Personal_Data;

typedef struct{
    Personal_Data *link;
    char name[20];
    char surname[20];
    char telephone_number[20];
} User_Credentials;

void clear_screen();
void loggingInto();
void createAccount();
