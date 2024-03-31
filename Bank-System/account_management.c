#include "account_management.h"
#include "data_generator.h"
#include "data_parser.h"

// FUNCTION PROTOTYPES
void clear_screen();
void loggingInto();
void createAccount();
int main();
//

void loggingInto(){
    clear_screen();
    printf("\n-----------------------------------\n");
    printf("You've succesfully logged!");
}

void createAccount(){

    createCSV(); // Creates when the CSV is not found
    clear_screen();

    User_Credentials user;

    // Choosing the Coin
    int bool = 1;
    char currency[4];
    char option1;

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

    char *buffer = (char*)malloc(sizeof(char)*21);
    int length;

    do{
        printf("\n======================================================"); 
        printf("\nEnter your first name:\n\n");

        scanf("%s", buffer);
        length = strlen(buffer);
        if(length < 3){
            clear_screen();
            printf("Your name is too short.\n");
            continue;
        }
        else if(length > 20){
            clear_screen();
            printf("Your name is too long.\n");
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
    buffer = (char*)malloc(sizeof(char)*21);

    bool = 1;

    do{
        printf("\n======================================================"); 
        printf("\nEnter your last name:\n\n");

        scanf("%s", buffer);
        length = strlen(buffer);
        if(length < 3){
            clear_screen();
            printf("Your last name is too short.\n");
            continue;
        }
        else if(length > 20){
            clear_screen();
            printf("Your last name is too long.\n");
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
    buffer = malloc(sizeof(char)*21);
    
    bool = 1;

    do{
        printf("\n======================================================"); 
        printf("\nEnter your telephone number:\n\n");
        scanf("%s", buffer);

        length = strlen(buffer);
        if(length < 7){
            clear_screen();
            printf("Telepehone number should contain no less than 7 digits.\n");
            continue;
        }
        else if(length > 20){
            clear_screen();
            printf("Your telephone number is too long.\n");
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

    // Password Field
    buffer = (char*)malloc(sizeof(char)*21);

    user.link = (Card_Data*)malloc(sizeof(Card_Data));

    bool = 1;
    
    do{
        printf("\n======================================================"); 
        printf("\nEnter your password:\n\n");
        scanf("%s", buffer);
        length = strlen(buffer);
        if(length < 5){
            clear_screen();
            printf("Your password is too short.\n ");
            continue;
        }
        else if(length > 20){
            clear_screen();
            printf("Your password is too long.\n");
            continue;
        }
        bool = 0;
    }while(bool);   

    buffer[length] = '\0';
    strcpy(user.password, buffer);
    free(buffer);
    clear_screen();


    // Generate ID
    strcpy(user.account_id, "10000");


    // Card Data Field
    strcpy(user.link->currency, currency);

    char *iban = (char*)malloc((IBAN_LENGTH+1)*sizeof(char));
    generate_random_iban(iban);
    strcpy(user.link->iban, iban);
    free(iban);

    user.link->balance = 0;

    write_data(user);

    printf("\n======================================================"); 
    printf("\n\t+ Your account with ID: %s\n\thas been succesfully created!\n\n", user.account_id);

    printf("\t+ Your current balance: %.2f%s\n", user.link->balance, user.link->currency);
    
    printf("\n\t+ Your IBAN is: %s\n", user.link->iban);
    printf("\n\t+ Your password is: %s\n", user.password);
    printf("======================================================"); 
    //

    char option2;

    printf("    \nDo you want to Log in? [y/N]\n");
    scanf("\n");
    scanf("%c", &option2);
    switch(option2)
    {
        case 'y':
            loggingInto();
            break;
        default:
            clear_screen();
            main();
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

