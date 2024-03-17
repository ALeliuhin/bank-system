#include "account_management.h"
#include "data_generator.h"

// STRUCTURES
typedef struct{
    float balance;
    char account_id[6];
    char password[20];
    char iban[25];
} Personal_Data;

typedef struct{
    Personal_Data *link;
    char name[20];
    char surname[20];
    char telephone_number[20];
} User_Credentials;

// FUNCTION PROTOTYPES
void clear_screen();
void loggingInto();
void createAccount();
int main();
//

void loggingInto(){
    clear_screen();
    printf("You've succesfully logged!");
}

void createAccount(){

    clear_screen();
    User_Credentials user;

    int bool = 1;
    char option1;
    char currency[4];

    while (bool){
        printf("\n======================================================"); 
        printf("\nChoose the currency for your account:\n\n  1. RON\n  2. USD\n  3. EUR\n\n");
        scanf(" %c", &option1); 

        switch(option1){
            case '1':
                strcpy(currency, "RON");
                clear_screen();
                bool = 0;
                break;
            case '2':
                strcpy(currency, "USD");
                clear_screen();
                bool = 0;
                break;
            case '3':
                strcpy(currency, "EUR");
                clear_screen();
                bool = 0;
                break;
            default:
                clear_screen();
                continue; 
        break; 
        }
    }
    // First Name Field
    bool = 1;
    char *buffer = malloc(sizeof(char)*21);
    int length;
    do{
        printf("\n======================================================"); 
        printf("\nEnter your first name:\n\n");

        scanf("%20s", buffer);
        length = strlen(buffer);
        if(length < 3){
            clear_screen();
            printf("Your name is too short.\n");
            continue;
        }

        int count_non_letters = 0;
        for(int i = 0; i < length; i++){
            if(!isalpha(buffer[i])){
                count_non_letters++;
            }
        }

        if(count_non_letters == 0){
            bool = 0;
        }
        else{
            clear_screen();
            printf("Name should include only letters.\n");
        }
        
    }while(bool);

    buffer[length] = '\0';
    buffer[0] = toupper(buffer[0]);
    for(int i = 1; i < length; i++){
        buffer[i] = tolower(buffer[i]);
    }

    strcpy(user.name, buffer);
    free(buffer);
    clear_screen();

    // Last Name Field
    printf("%s", user.name);

    buffer = malloc(sizeof(char)*21);

    bool = 1;

    do{
        printf("\n======================================================"); 
        printf("\nEnter your last name:\n\n");

        scanf("%20s", buffer);
        length = strlen(buffer);
        if(length < 3){
            clear_screen();
            printf("Your last name is too short.\n");
            continue;
        }

        int count_non_letters = 0;
        for(int i = 0; i < length; i++){
            if(!isalpha(buffer[i])){
                count_non_letters++;
            }
        }

        if(count_non_letters == 0){
            bool = 0;
        }
        else{
            clear_screen();
            printf("Last name should include only letters.\n");
        }
        
    }while(bool);

    buffer[length] = '\0';
    buffer[0] = toupper(buffer[0]);
    for(int i = 1; i < length; i++){
        buffer[i] = tolower(buffer[i]);
    }

    strcpy(user.surname, buffer);
    free(buffer);
    clear_screen();

    //Telephone Number Field
    printf("%s", user.surname);
    buffer = malloc(sizeof(char)*21);
    
    bool = 1;

    do{
        printf("\n======================================================"); 
        printf("\nEnter your telephone number:\n\n");
        scanf("%20s", buffer);

        length = strlen(buffer);
        if(length < 7){
            clear_screen();
            printf("Telepehone number should contain no less than 7 digits.\n");
            continue;
        }

        int count_non_digits = 0;
        for(int i = 0; i < length; i++){
            if(!isdigit(buffer[i])){
                count_non_digits++;
            }
        }
        if(count_non_digits == 0){
            bool = 0;
        }
        else{
            clear_screen();
            printf("Telephone number should contain only digits.\n");
        }
    }while(bool);

    buffer[length] = '\0';
    strcpy(user.telephone_number, buffer);
    free(buffer);
    clear_screen();

    user.link = malloc(sizeof(Personal_Data));
    printf("%s\n", user.telephone_number);
    printf("\n======================================================"); 
    printf("\nEnter your password:\n\n");
    scanf("%s", &user.link->password);

    user.link->balance = 0;

    clear_screen();
    
    strcpy(user.link->account_id, "10000");

    printf("\n======================================================"); 
    printf("\n\t+ Your account with ID: %s\n\thas been succesfully created!\n\n", user.link->account_id);

    printf("\t+ Your current balance: %.2f%s\n", user.link->balance, currency);
    
    char *iban = generate_random_iban();
    strcpy(user.link->iban, iban);
    printf("\n\t+ Your IBAN is: %s.\n", iban);

    char option2;

    printf("    \nDo you want to Log in? [y/N]\n");

    scanf(" %c", &option2);
    switch(option2)
    {
        case 'y':
            loggingInto();
            break;
        case 'N':
            clear_screen();
            main();
            break;
        case 'n':
            clear_screen();
            main();
            break;
        default:
            {}
            break;
    }

}

void clear_screen() {
    #ifdef _WIN32
        system("cls"); // For Windows
    #else
        system("clear"); // For Linux/Unix
    #endif
}

