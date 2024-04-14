#include "account_management.h"
int initial_start = 0;

int main()
{
    if(initial_start == 0){
        clear_screen();
        initial_start++;
    }
    printf("-----------------------------------\n");
    printf("Welcome to the UVT Bank System!");
    printf("\n-----------------------------------\n");
    printf("\n\t===TERMINAL===\n\n");

    char choice;

    printf("Choose one of the options:\n  1. Log in\n  2. Create account\n  3. Exit");
    printf("\n-----------------------------------\n");
    scanf(" %c", &choice);

    switch(choice)
    {
        case '1':
            char *bufferTelephone = malloc(sizeof(char)*21);
            char *bufferPassword = malloc(sizeof(char)*21);
            clear_screen();
            loggingInto(bufferTelephone, bufferPassword);
            free(bufferTelephone);
            free(bufferPassword);
            break;
        case '2':
            createAccount();
            break;
        case '3':
            printf("\nExiting.....");
            exit(0);
            break;
        default:
            clear_screen();
            main();
            break;
    }

    return 0;
}

   