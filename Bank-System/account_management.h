#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char iban[25];
    char currency[4];
    float balance;
} Card_Data;

typedef struct{
    Card_Data *link;
    char password[20];
    char name[20];
    char surname[20];
    char telephone_number[20];
    char account_id[6];
} User_Credentials;

void clear_screen();
void loggingInto();
void createAccount();
