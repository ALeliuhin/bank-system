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
    Card_Data *iban1;
    Card_Data *iban2;
    Card_Data *iban3;
    char password[20];
    char name[20];
    char surname[20];
    char telephone_number[20];
    int number_of_cards;
} User_Credentials;

void mainTerminal();
void clear_screen();
void mainMenu(User_Credentials user);
void loggingIntoArgv(char *bufferTelephone, char *bufferPassword);
void loggingInto(char *bufferTelephone, char *bufferPassword);
void createAccount();
