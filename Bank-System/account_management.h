#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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
} User_Credentials;

int main();
void clear_screen();
void loggingInto(char *bufferTelephone, char *bufferPassword);
void createAccount();
