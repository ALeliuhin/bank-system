#include "account_management.h"
#include "data_generator.h"
#include "data_parser.h"
#include "transactions.h"
#define MAX_LIMIT 100000000

void mainMenu(User_Credentials user){

    printf("--------------------------------------------------\n");
    printf("\t Welcome, %s %s!\n", user.name, user.surname);
    bool ext_bool = true;
    do{
        printf("--------------------------------------------------\n");
        printf("\n\t===MAIN MENU===\n\n");

        bool bool1 = true;
        do{
            char option1;
            printf("Select one of the options:");
            printf("\n  1. Inspect personal data\n  2. Inspect card data\n  3. Withdraw cash\n  4. Top up account\n");
            printf("  5. Make a transaction\n  6. Change password\n  7. Change IBAN\n  8. Delete account\n  9. Create new card\n  0. Log out\n");
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
                    if(user.number_of_cards == 1){
                        printf("\t+ Your IBAN-1: %s\n", user.iban1->iban);
                        printf("\t\t+ Your balance: %0.2f%s\n", user.iban1->balance, user.iban1->currency);
                    }
                    else if(user.number_of_cards == 2){
                        printf("\t+ Your IBAN-1: %s\n", user.iban1->iban);
                        printf("\t\t+ Your balance: %0.2f%s\n", user.iban1->balance, user.iban1->currency);
                        printf("\t+ Your IBAN-2: %s\n", user.iban2->iban);
                        printf("\t\t+ Your balance: %0.2f%s\n", user.iban2->balance, user.iban2->currency);
                    }
                    else if(user.number_of_cards == 3){
                        printf("\t+ Your IBAN-1: %s\n", user.iban1->iban);
                        printf("\t\t+ Your balance: %0.2f%s\n", user.iban1->balance, user.iban1->currency);
                        printf("\t+ Your IBAN-2: %s\n", user.iban2->iban);
                        printf("\t\t+ Your balance: %0.2f%s\n", user.iban2->balance, user.iban2->currency);
                        printf("\t+ Your IBAN-3: %s\n", user.iban3->iban);
                        printf("\t\t+ Your balance: %0.2f%s\n", user.iban3->balance, user.iban3->currency);
                    }
                    printf("======================================================\n");
                    break;

                case '3':
                    clear_screen();
                    float amount_to_withdraw;
                    bool bool_withdraw = true;
                    bool bool_withdraw_cancel = true;
                    bool bool_withdraw_option = true;

                    char choice_iban;
                    Card_Data *selected_iban;

                    do{
                        printf("======================================================\n");
                        printf("Choose the IBAN:\n");
                        if(user.number_of_cards == 1){
                            printf("\t1. %s\n", user.iban1->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban1->balance, user.iban1->currency);
                            printf("======================================================\n\n");
                            scanf(" %c", &choice_iban);
                            switch(choice_iban){
                            case '1':
                                selected_iban = user.iban1;
                                break;
                            default:
                                clear_screen();
                                continue;
                            }
                        }
                        else if(user.number_of_cards == 2){
                            printf("\t1. %s\n", user.iban1->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban1->balance, user.iban1->currency);
                            printf("\t2. %s\n", user.iban2->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban2->balance, user.iban2->currency);
                            printf("======================================================\n\n");
                            scanf(" %c", &choice_iban);
                            switch(choice_iban){
                            case '1':
                                selected_iban = user.iban1;
                                break;
                            case '2':
                                selected_iban = user.iban2;
                                break;
                            default:
                                clear_screen();
                                continue;
                            }
                        }
                        else if(user.number_of_cards == 3){
                            printf("\t1. %s\n", user.iban1->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban1->balance, user.iban1->currency);
                            printf("\t2. %s\n", user.iban2->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban2->balance, user.iban2->currency);
                            printf("\t3. %s\n", user.iban3->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban3->balance, user.iban3->currency);
                            printf("======================================================\n\n");
                            scanf(" %c", &choice_iban);
                            switch(choice_iban){
                                case '1':
                                    selected_iban = user.iban1;
                                    break;
                                case '2':
                                    selected_iban = user.iban2;
                                    break;
                                case '3':
                                    selected_iban = user.iban3;
                                    break;
                                default:
                                    clear_screen();
                                    continue;
                            }
                        }
                        bool_withdraw_option = false;
                    }while(bool_withdraw_option);

                    clear_screen();

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
                            clear_screen();
                            printf("Minimum 5%s to withdraw.", selected_iban->currency);
                            continue;
                        }
                        else if(selected_iban->balance < amount_to_withdraw){
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

                    withdrawCash(&user, selected_iban, choice_iban, amount_to_withdraw);
                    printf("--------------------------------------------------\n");
                    printf("You have succesfully withdrawn cash!\n");
                    printf("--------------------------------------------------\n");
                    break;

                case '4':
                    clear_screen();
                    float amount_to_top_up;
                    bool bool_top_up = true;
                    bool bool_top_up_cancel = true;
                    bool bool_top_up_option = true;

                    do{
                        printf("======================================================\n");
                        printf("Choose the IBAN:\n");
                        if(user.number_of_cards == 1){
                            printf("\t1. %s\n", user.iban1->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban1->balance, user.iban1->currency);
                            printf("======================================================\n\n");
                            scanf(" %c", &choice_iban);
                            switch(choice_iban){
                            case '1':
                                selected_iban = user.iban1;
                                break;
                            default:
                                clear_screen();
                                continue;
                            }
                        }
                        else if(user.number_of_cards == 2){
                            printf("\t1. %s\n", user.iban1->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban1->balance, user.iban1->currency);
                            printf("\t2. %s\n", user.iban2->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban2->balance, user.iban2->currency);
                            printf("======================================================\n\n");
                            scanf(" %c", &choice_iban);
                            switch(choice_iban){
                            case '1':
                                selected_iban = user.iban1;
                                break;
                            case '2':
                                selected_iban = user.iban2;
                                break;
                            default:
                                clear_screen();
                                continue;
                            }
                        }
                        else if(user.number_of_cards == 3){
                            printf("\t1. %s\n", user.iban1->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban1->balance, user.iban1->currency);
                            printf("\t2. %s\n", user.iban2->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban2->balance, user.iban2->currency);
                            printf("\t3. %s\n", user.iban3->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban3->balance, user.iban3->currency);
                            printf("======================================================\n\n");
                            scanf(" %c", &choice_iban);
                            switch(choice_iban){
                                case '1':
                                    selected_iban = user.iban1;
                                    break;
                                case '2':
                                    selected_iban = user.iban2;
                                    break;
                                case '3':
                                    selected_iban = user.iban3;
                                    break;
                                default:
                                    clear_screen();
                                    continue;
                            }
                        }
                        bool_top_up_option = false;
                    }while(bool_top_up_option);

                    clear_screen();

                    do{
                        printf("\n======================================================");
                        printf("\nInput the amount to top up: [0 - cancel]\n\n");
                        scanf(" %f", &amount_to_top_up);
                        if(amount_to_top_up < 5){
                            if(amount_to_top_up == 0){
                                clear_screen();
                                bool_top_up = false;
                                bool_top_up_cancel = false;
                                break;
                            }
                            clear_screen();
                            printf("Minimum 5%s to top up.", selected_iban->currency);
                            continue;
                        }
                        else if(amount_to_top_up > MAX_LIMIT - selected_iban->balance){
                            clear_screen();
                            printf("Maximum amount exceeded.");
                            continue;
                        }
                        bool_top_up = false;
                    }while(bool_top_up);

                    if(bool_top_up_cancel == false){
                        clear_screen();
                        break;
                    }
                    clear_screen();

                    topUpAccount(&user, selected_iban, choice_iban, amount_to_top_up);
                    printf("--------------------------------------------------\n");
                    printf("You have succesfully appended account!\n");
                    printf("--------------------------------------------------\n");
                    break;
                
                case '5':
                    clear_screen();
                    bool bool_transfer = true;
                    char iban_destination[IBAN_LENGTH + 1];
                    float amount_to_transfer;

                    do{
                        printf("======================================================\n");
                        printf("Choose the IBAN:\n");
                        if(user.number_of_cards == 1){
                            printf("\t1. %s\n", user.iban1->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban1->balance, user.iban1->currency);
                            printf("======================================================\n\n");
                            scanf(" %c", &choice_iban);
                            switch(choice_iban){
                                case '1':
                                    selected_iban = user.iban1;
                                    break;
                                default:
                                    clear_screen();
                                    continue;
                            }
                        }
                        else if(user.number_of_cards == 2){
                            printf("\t1. %s\n", user.iban1->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban1->balance, user.iban1->currency);
                            printf("\t2. %s\n", user.iban2->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban2->balance, user.iban2->currency);
                            printf("======================================================\n\n");
                            scanf(" %c", &choice_iban);
                            switch(choice_iban){
                                case '1':
                                    selected_iban = user.iban1;
                                    break;
                                case '2':
                                    selected_iban = user.iban2;
                                    break;
                                default:
                                    clear_screen();
                                    continue;
                            }
                        }
                        else if(user.number_of_cards == 3){
                            printf("\t1. %s\n", user.iban1->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban1->balance, user.iban1->currency);
                            printf("\t2. %s\n", user.iban2->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban2->balance, user.iban2->currency);
                            printf("\t3. %s\n", user.iban3->iban);
                            printf("\t\t+ Your balance: %0.2f%s\n", user.iban3->balance, user.iban3->currency);
                            printf("======================================================\n\n");
                            scanf(" %c", &choice_iban);
                            switch(choice_iban){
                                case '1':
                                    selected_iban = user.iban1;
                                    break;
                                case '2':
                                    selected_iban = user.iban2;
                                    break;
                                case '3':
                                    selected_iban = user.iban3;
                                    break;
                                default:
                                    clear_screen();
                                    continue;
                            }
                        }
                        bool_transfer = false;
                    }while(bool_transfer);

                    if(selected_iban->balance < 5){
                        clear_screen();
                        printf("Insufficient funds to perform a transfer.\n");
                        printf("--------------------------------------------------\n");
                        break;
                    }
                    bool_transfer = true;
                    clear_screen();

                    do{
                        printf("\n======================================================");
                        printf("\nInput the destination IBAN:\n\n");
                        scanf("\n");
                        fgets(iban_destination, IBAN_LENGTH + 1, stdin);

                        if(strcmp(selected_iban->iban, iban_destination) == 0){
                            clear_screen();
                            printf("Cannot transfer to the same IBAN.\n");
                            continue;
                        }
                        if(validationData(iban_destination) == 1){
                            clear_screen();
                            do{
                                printf("======================================================");
                                printf("\nInput amount to transfer: (min: 5%s)\n\n", selected_iban->currency);
                                scanf(" %f", &amount_to_transfer);
                                if(amount_to_transfer > selected_iban->balance){
                                    clear_screen();
                                    printf("Insufficient funds. Please enter a valid amount.\n");
                                    continue;
                                }
                                else if(amount_to_transfer < 5){
                                    clear_screen();
                                    printf("Minimum 5%s to transfer.\n", selected_iban->currency);
                                    continue;
                                }
                                else if(amount_to_transfer > 100000){
                                    clear_screen();
                                    printf("Maximum 100000%s to transfer.\n", selected_iban->currency);
                                    continue;
                                }
                                bool_transfer = false;
                            }while(bool_transfer);
                            transferMoney(&user, selected_iban, iban_destination, amount_to_transfer);
                        }
                        else{
                            clear_screen();
                            printf("No matching IBAN in the database.");
                            continue;
                        }
                    }while(bool_transfer);

                    clear_screen();
                    printf("--------------------------------------------------\n");
                    printf("You have succesfully transfered money!\n");
                    printf("--------------------------------------------------\n");
                    break;

                case '6':
                    clear_screen();
                    char *new_password = malloc(sizeof(char)*21);
                    bool bool_password = true;
    
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
                        bool_password = false;
                    }while(bool_password);   

                    clear_screen();
                    char aux_choice = 'F';
                    modifyData(&user, new_password, aux_choice);
                    free(new_password);
                    printf("--------------------------------------------------\n");
                    printf("Your password has been changed!\n");
                    printf("--------------------------------------------------\n");
                    break;

                case '7':
                    clear_screen();
                    char *new_iban = malloc(sizeof(char)*(IBAN_LENGTH + 1));
                    bool bool_new_iban = true;
                    char new_iban_choice;

                    do{
                        generate_random_iban(new_iban);
                    }while(validationData(new_iban));

                    do{
                        printf("======================================================\n");
                        printf("Select the IBAN to change:\n");
                        printf("======================================================\n");
                        if(user.number_of_cards == 1){
                            printf("\t1. %s\n", user.iban1->iban);
                            printf("======================================================\n");
                            scanf(" %c", &new_iban_choice);
                            switch(new_iban_choice){
                                case '1':
                                    modifyData(&user, new_iban, new_iban_choice);
                                    break;
                                default:
                                    clear_screen();
                                    continue;
                            }
                        }
                        else if(user.number_of_cards == 2){
                            printf("\t1. %s\n\n", user.iban1->iban);
                            printf("\t2. %s\n", user.iban2->iban);
                            printf("======================================================\n");
                            scanf(" %c", &new_iban_choice);
                            if(new_iban_choice == '1' || new_iban_choice == '2'){
                                modifyData(&user, new_iban, new_iban_choice);
                            }
                            else{
                                clear_screen();
                                continue;
                            }
                        }
                        else if(user.number_of_cards == 3){
                            printf("\t1. %s\n\n", user.iban1->iban);
                            printf("\t2. %s\n\n", user.iban2->iban);
                            printf("\t3. %s\n", user.iban3->iban);
                            printf("======================================================\n");
                            scanf(" %c", &new_iban_choice);
                            if(new_iban_choice == '1' || new_iban_choice == '2' || new_iban_choice == '3'){
                                modifyData(&user, new_iban, new_iban_choice);
                            }
                            else{
                                clear_screen();
                                continue;
                            }
                        }
                        bool_new_iban = false;
                    }while(bool_new_iban);

                    free(new_iban);
                    clear_screen();
                    printf("--------------------------------------------------\n");
                    printf("Your IBAN has been changed!\n");
                    printf("--------------------------------------------------\n");
                    break;

                case '8':
                    clear_screen();
                    char delete_option;
                    printf("Are you sure? [y/N]\n");
                    scanf(" %c", &delete_option);
                    if(delete_option == 'y'){
                        deleteAccount(user);
                        mainTerminal();
                    }
                    else{
                        clear_screen();
                        printf("--------------------------------------------------\n");
                        printf("\n\t===MAIN MENU===\n\n");
                        break;
                    }
                
                case '9':
                    clear_screen();
                    if(user.number_of_cards == 3){
                        printf("Maximum number of accounts exceeded.\n");
                        printf("--------------------------------------------------\n");
                        break;
                    }
                    bool bool_new_card = true;
                    char choice_currency;
                    char *new_card = (char*)malloc((IBAN_LENGTH+1)*sizeof(char));
                    char new_card_currency[4];
                    float new_card_balance = 0;

                    do{
                        printf("\n======================================================"); 
                        printf("\nChoose the currency for your account:\n\n  1. RON\n  2. USD\n  3. EUR\n\n");
                        scanf(" %c", &choice_currency);
                        switch(choice_currency){
                            case '1':
                                strcpy(new_card_currency, "RON");
                                bool_new_card = false;
                                break;
                            case '2':
                                strcpy(new_card_currency, "USD");
                                bool_new_card = false;
                                break;
                            case '3':
                                strcpy(new_card_currency, "EUR");
                                bool_new_card = false;
                                break;
                            default:
                                clear_screen();
                                continue;
                        }
                    }while(bool_new_card);

                    do{
                        generate_random_iban(new_card);
                    }while(validationData(new_card));

                    createNewCard(&user, new_card, new_card_balance, new_card_currency);
                    free(new_card);
                    clear_screen();
                    printf("--------------------------------------------------\n");
                    printf("You have succesfully created a new card!\n");
                    printf("--------------------------------------------------\n");
                    break;

                case '0':
                    ext_bool = false;
                    bool1 = false;
                    clear_screen();
                    mainTerminal();
                    break;

                default:
                    clear_screen();
                    bool1 = false;
                    break;
            }

        }while(bool1);

    }while(ext_bool);
}

void loggingIntoArgv(char *bufferTelephone, char *bufferPassword){
    User_Credentials user = readForLogging(bufferTelephone, bufferPassword);
    mainMenu(user);
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


    // Card Data Field

    user.iban1 = (Card_Data*)malloc(sizeof(Card_Data));
    user.iban2 = (Card_Data*)malloc(sizeof(Card_Data));
    user.iban3 = (Card_Data*)malloc(sizeof(Card_Data));

    strcpy(user.iban1->currency, currency);

    char *iban = (char*)malloc((IBAN_LENGTH+1)*sizeof(char));

    do{
        generate_random_iban(iban);
    }while(validationData(iban));

    strcpy(user.iban1->iban, iban);

    free(iban);

    user.iban1->balance = 0;

    strcpy(user.iban2->iban, "(null)");
    user.iban2->balance = -1;
    strcpy(user.iban2->currency, "(null)");

    strcpy(user.iban3->iban, "(null)");
    user.iban3->balance = -1;
    strcpy(user.iban3->currency, "(null)");

    user.number_of_cards = 1;

    write_data(user);

    free(user.iban1);
    free(user.iban2);
    free(user.iban3);

    printf("\n======================================================"); 
    printf("\n\t+ Your account\n\t  has been succesfully created!\n\n");

    printf("\t+ Your current balance: %.2f%s\n", user.iban1->balance, user.iban1->currency);
    
    printf("\n\t+ Your IBAN is: %s\n", user.iban1->iban);
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
            mainTerminal();
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

