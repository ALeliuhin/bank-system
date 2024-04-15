#include "account_management.h"
#include "data_generator.h"
#include "data_parser.h"
#include "transactions.h"
#define MAX_LIMIT 100000000

void mainMenu(User_Credentials user){

    printf("--------------------------------------------------\n");
    printf("\t Welcome, %s %s!\n", user.name, user.surname);
    int ext_bool = 1;
    do{
        printf("--------------------------------------------------\n");
        printf("\n\t===MAIN MENU===\n\n");

        int bool1 = 1;
        do{
            char option1;
            printf("Select one of the options:");
            printf("\n  1. Inspect personal data\n  2. Inspect card data\n  3. Withdraw cash\n  4. Top up account\n");
            printf("  5. Make a transaction\n  6. Change password\n  7. Change IBAN\n  8. Delete account\n  9. Log out\n");
            printf("--------------------------------------------------\n");
            scanf(" %c", &option1);
            switch(option1){

                case '1':
                    clear_screen();
                    printf("======================================================\n");
                    printf("\t+ Your name: %s %s\n\n", user.name, user.surname);
                    printf("\t+ Your telephone number: %s", user.telephone_number);
                    printf("\n\n\t+ Your password: %s\n", user.password);
                    printf("======================================================\n");
                    break;

                case '2':
                    clear_screen();
                    printf("======================================================\n");
                    printf("\t+ Your IBAN: %s\n\n", user.link->iban);
                    printf("\t+ Your balance: %0.2f%s\n", user.link->balance, user.link->currency);
                    printf("======================================================\n");
                    break;

                case '3':
                    clear_screen();
                    float amount_to_withdraw;
                    bool bool_withdraw = true;
                    bool bool_withdraw_cancel = true;
                    do{
                        printf("\n======================================================");
                        printf("\nInput the amount to withdraw: [0 - cancel]\n\n");
                        scanf(" %f", &amount_to_withdraw);
                        if(amount_to_withdraw < 5){
                            if(amount_to_withdraw == 0){
                                clear_screen();
                                bool_withdraw = false;
                                bool_withdraw_cancel = false;
                                break;
                            }
                            clear_screen;
                            printf("Minimum 5%s to withdraw.", user.link->currency);
                            continue;
                        }
                        else if(user.link->balance < amount_to_withdraw){
                            clear_screen();
                            printf("Insufficient funds. Please enter a valid amount.");
                            continue;
                        }
                        bool_withdraw = false;
                    }while(bool_withdraw);
                    if(bool_withdraw_cancel == false){
                        clear_screen();
                        break;
                    }
                    clear_screen();
                    withdrawCash(&user, amount_to_withdraw);
                    printf("--------------------------------------------------\n");
                    printf("You have succesfully withdrawn cash!\n");
                    printf("--------------------------------------------------\n");
                    break;

                case '4':
                    clear_screen();
                    float amount_to_top_up;
                    int bool_top_up = 1;
                    do{
                        printf("\n======================================================");
                        printf("\nInput the amount to top up:\n\n");
                        scanf(" %f", &amount_to_top_up);
                        if(amount_to_top_up > user.link->balance + MAX_LIMIT){
                            clear_screen;
                            printf("Maximum limit to top up exceeded.");
                            continue;
                        }
                        bool_top_up = 0;
                    }while(bool_top_up);
                    clear_screen();
                    topUpAccount(&user, amount_to_top_up);
                    printf("-----------------------------------\n");
                    printf("You have succesfully appended account!\n");
                    printf("-----------------------------------\n");
                    break;
                
                case '5':
                    clear_screen();
                    bool bool_transfer = true;
                    char iban_destination[IBAN_LENGTH + 1];
                    float amount_to_transfer;
                    do{
                        printf("\n======================================================");
                        printf("\nInput the destination IBAN:\n");
                        scanf("\n");
                        fgets(iban_destination, IBAN_LENGTH + 1, stdin);
                        if(validationData(iban_destination) == 1){
                            clear_screen();
                            printf("Input amount to transfer: (min: 5%s)\n", user.link->currency);
                            scanf(" %f", &amount_to_transfer);
                            transferMoney(&user, iban_destination, amount_to_transfer);
                            bool_transfer = false;
                        }
                        else{
                            clear_screen();
                            printf("No matching IBAN in the database.");
                            continue;
                        }
                    }while(bool_transfer);
                    clear_screen();
                    printf("-----------------------------------\n");
                    printf("You have succesfully transfered money!\n");
                    printf("-----------------------------------\n");
                    break;

                case '6':
                    clear_screen();
                    char *new_password = malloc(sizeof(char)*21);
                    int bool_password = 1;
    
                    do{
                        printf("\n======================================================"); 
                        printf("\nEnter your new password:\n\n");
                        scanf(" %s", new_password);
                        int length = strlen(new_password);
                        if(length < 5){
                            clear_screen();
                            printf("Your new password is too short.\n ");
                            continue;
                        }
                        else if(length > 20){
                            clear_screen();
                            printf("Your new password is too long.\n");
                            continue;
                        }
                        bool_password = 0;
                    }while(bool_password);   

                    clear_screen();
                    modifyData(&user, new_password);
                    free(new_password);
                    printf("-----------------------------------\n");
                    printf("Your password has been changed!\n");
                    printf("-----------------------------------\n");
                    break;

                case '7':
                    char *new_iban = malloc(sizeof(char)*(IBAN_LENGTH + 1));
                    do{
                        generate_random_iban(new_iban);
                    }while(validationData(new_iban));

                    modifyData(&user, new_iban);
                    free(new_iban);
                    clear_screen();
                    printf("-----------------------------------\n");
                    printf("Your IBAN has been changed!\n");
                    printf("-----------------------------------\n");
                    break;

                case '8':
                    clear_screen();
                    char delete_option;
                    printf("Are you sure? [y/N]\n");
                    scanf(" %c", &delete_option);
                    if(delete_option == 'y'){
                        deleteAccount(user);
                    }
                    else{
                        clear_screen();
                        printf("-----------------------------------\n");
                        printf("\n\t===MAIN MENU===\n\n");
                        break;
                    }

                case '9':
                    ext_bool = 0;
                    bool1 = 0;
                    clear_screen();
                    main();
                    break;

                default:
                    clear_screen();
                    bool1 = 0;
                    break;
            }

        }while(bool1);

    }while(ext_bool);
}

void loggingInto(char *bufferTelephone, char *bufferPassword){

    int length;
    int ext_bool = 1;

    free(bufferTelephone);
    free(bufferPassword);

    bufferTelephone = malloc(sizeof(char)*21);
    bufferPassword = malloc(sizeof(char)*21);

    do{
        printf("\n======================================================"); 
        printf("\nEnter your telephone number:\n\n");
        scanf(" %s", bufferTelephone);

        length = strlen(bufferTelephone);

        if(length < 7){
            clear_screen();
            printf("Telepehone number contains no less than 7 digits.\n");
            continue;
        }
        else if(length > 20){
            clear_screen();
            printf("You exceeded the number of digits for the telephone number.\n");
            continue;
        }

        int count_non_digits = 0;
        for(int i = 0; i < length; i++){
            if(!isdigit(bufferTelephone[i])){
                count_non_digits++;
            }
        }
        if(count_non_digits == 0){
            ext_bool = 0;
        }
        else{
            clear_screen();
            printf("Telephone number contains only digits.\n");
        }
    }while(ext_bool);

    clear_screen();
    ext_bool = 1;

    do{
        printf("\n======================================================"); 
        printf("\nEnter your password:\n\n");
        scanf(" %s", bufferPassword);
        length = strlen(bufferPassword);
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
        ext_bool = 0;
    }while(ext_bool);

    clear_screen();

    User_Credentials user = readForLogging(bufferTelephone, bufferPassword);
    mainMenu(user);

}

void createAccount(){

    createCSV(); // Creates when the CSV is not found
    clear_screen();

    User_Credentials user;

    // Choosing the Coin
    int ext_bool = 1;
    char currency[4];
    char option1;

    while (ext_bool){
        printf("\n======================================================"); 
        printf("\nChoose the currency for your account:\n\n  1. RON\n  2. USD\n  3. EUR\n\n");
        scanf(" %c", &option1); 

        switch(option1){
            case '1':
                strcpy(currency, "RON");
                clear_screen();
                ext_bool = 0;
                break;
            case '2':
                strcpy(currency, "USD");
                clear_screen();
                ext_bool = 0;
                break;
            case '3':
                strcpy(currency, "EUR");
                clear_screen();
                ext_bool = 0;
                break;
            default:
                clear_screen();
                continue; 
        break; 
        }
    }


    // First Name Field
    ext_bool = 1;

    char *buffer = (char*)malloc(sizeof(char)*21);
    int length;

    do{
        printf("\n======================================================"); 
        printf("\nEnter your first name:\n\n");

        scanf(" %s", buffer);
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
            ext_bool = 0;
        }
        else{
            clear_screen();
            printf("Name should include only letters.\n");
        }
        
    }while(ext_bool);

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

    ext_bool = 1;

    do{
        printf("\n======================================================"); 
        printf("\nEnter your last name:\n\n");

        scanf(" %s", buffer);
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
            ext_bool = 0;
        }
        else{
            clear_screen();
            printf("Last name should include only letters.\n");
        }
        
    }while(ext_bool);

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
    
    ext_bool = 1;

    do{
        printf("\n======================================================"); 
        printf("\nEnter your telephone number:\n\n");
        scanf(" %s", buffer);

        length = strlen(buffer);
        if(validationData(buffer) == 1){
            clear_screen();
            printf("This telephone number is already associated with another account.\n");
            continue;
        }
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
            ext_bool = 0;
        }
        else{
            clear_screen();
            printf("Telephone number should contain only digits.\n");
        }
    }while(ext_bool);

    buffer[length] = '\0';
    strcpy(user.telephone_number, buffer);
    free(buffer);
    clear_screen();

    // Password Field
    buffer = (char*)malloc(sizeof(char)*21);

    user.link = (Card_Data*)malloc(sizeof(Card_Data));

    ext_bool = 1;
    
    do{
        printf("\n======================================================"); 
        printf("\nEnter your password:\n\n");
        scanf(" %s", buffer);
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
        ext_bool = 0;
    }while(ext_bool);   

    buffer[length] = '\0';
    strcpy(user.password, buffer);
    free(buffer);
    clear_screen();


    // Generate ID

    // Card Data Field
    strcpy(user.link->currency, currency);

    char *iban = (char*)malloc((IBAN_LENGTH+1)*sizeof(char));

    do{
        generate_random_iban(iban);
    }while(validationData(iban));

    strcpy(user.link->iban, iban);
    free(iban);

    user.link->balance = 0;

    write_data(user);

    printf("\n======================================================"); 
    printf("\n\t+ Your account\n\t  has been succesfully created!\n\n");

    printf("\t+ Your current balance: %.2f%s\n", user.link->balance, user.link->currency);
    
    printf("\n\t+ Your IBAN is: %s\n", user.link->iban);
    printf("\n\t+ Your password is: %s\n", user.password);
    printf("======================================================"); 
    //

    char option2;

    printf("    \nDo you want to Log in? [y/N]\n");
    scanf(" %c", &option2);
    switch(option2)
    {
        case 'y':
            clear_screen();
            main();
            break;
        default:
            printf("Exiting...");
            exit(0);
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

