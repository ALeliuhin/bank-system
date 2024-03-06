#include <stdio.h>

// function prototypes

void managePersonalData();

void transferMoney();

void createAccount();

void logintoAccount();

void welcomePrompt();

void initialRequest();

// -------------------------

typedef struct {
    char name[12];
    char surname[12];
    int age;
    char email[50];
    char iban[23]; // 22 - symbols code
    
}Bank_Users;

int main()
{
    welcomePrompt();
    initialRequest();

    return 0;
}

void managePersonalData()
{
    // set a new password, check current accounts (ex. RON, EUR, USD)
}

void transferMoney() 
{
    // transfer from personal accounts OR transfer to another person by IBAN
}

void createAccount()
{
    // create account and write personal data to the DB
}


void logintoAccount() 
{
    // compare input data with DB and access the account
}


void welcomePrompt()
{
    printf("\n--------------------------------\n");
    printf("Welcome to the UVT Bank System!\n");
    printf("--------------------------------\n");
}

void initialRequest()
{
    char request[10];
    printf("Choose one of the options:\n(\"Log in\" or \"Sign up\")\n--> :  ");
    fgets(request, 10, stdin);

    // if request == Log in --> call logintoAccount(), else if request == Sign up --> call createAccount()
}
