#include "transactions.h"
#define CLIENT_FORMAT_CSV_IN "%s,%s,%s,%s,%d,%s,%f,%s,%s,%f,%s,%s,%f,%s\n"
#define CLIENT_FORMAT_CSV_OUT "%[^,], %[^,], %[^,], %[^,], %d, %[^,], %f, %[^,], %[^,], %f, %[^,], %[^,], %f, %[^,\n]\n"
#define CSV_HEADER "Name,Surname,Telephone,Password,Cards,IBAN-1,Balance-1,Currency-1,IBAN-2,Balance-2,Currency-2,IBAN-3,Balance-3,Currency-3\n"


void withdrawCash(User_Credentials *user, Card_Data *selected_iban, char choice_iban, float amount_to_withdraw){
    User_Credentials aux_user;
    FILE *originalFile, *tempFile;
    fopen_s(&originalFile, "customers.csv", "r");
    fopen_s(&tempFile, "temp.csv", "w");
    if ((originalFile == NULL) || (tempFile == NULL)) {
        printf("Error opening the file.\nPlease run the program again.");
        exit(1);
    }

    fputs(CSV_HEADER, tempFile);
    
    aux_user.iban1 = malloc(sizeof(Card_Data));
    aux_user.iban2 = malloc(sizeof(Card_Data));
    aux_user.iban3 = malloc(sizeof(Card_Data));

    char header[300]; 
    fgets(header, sizeof(header), originalFile);

    while (fscanf(originalFile, CLIENT_FORMAT_CSV_OUT,
                                        aux_user.name, 
                                        aux_user.surname,
                                        aux_user.telephone_number, 
                                        aux_user.password, 
                                        &aux_user.number_of_cards,
                                        aux_user.iban1->iban, 
                                        &aux_user.iban1->balance,
                                        aux_user.iban1->currency, 
                                        aux_user.iban2->iban, 
                                        &aux_user.iban2->balance,
                                        aux_user.iban2->currency, 
                                        aux_user.iban3->iban, 
                                        &aux_user.iban3->balance,
                                        aux_user.iban3->currency) == 14) {
        if (strcmp(user->telephone_number, aux_user.telephone_number) == 0 &&
            strcmp(user->password, aux_user.password) == 0){
            if(choice_iban == '1'){
                aux_user.iban1->balance -= amount_to_withdraw;
                selected_iban->balance -= amount_to_withdraw;
            }
            else if(choice_iban == '2'){
                aux_user.iban2->balance -= amount_to_withdraw;
                selected_iban->balance -= amount_to_withdraw;
            }
            else if(choice_iban == '3'){
                aux_user.iban3->balance -= amount_to_withdraw;
                selected_iban->balance -= amount_to_withdraw;
            }
        }
        fprintf(tempFile, CLIENT_FORMAT_CSV_IN,
                                    aux_user.name, 
                                    aux_user.surname,
                                    aux_user.telephone_number, 
                                    aux_user.password, 
                                    aux_user.number_of_cards,
                                    aux_user.iban1->iban, 
                                    aux_user.iban1->balance,
                                    aux_user.iban1->currency, 
                                    aux_user.iban2->iban, 
                                    aux_user.iban2->balance,
                                    aux_user.iban2->currency, 
                                    aux_user.iban3->iban, 
                                    aux_user.iban3->balance,
                                    aux_user.iban3->currency);
    }

    fclose(originalFile);
    fclose(tempFile);

    remove("customers.csv");
    rename("temp.csv", "customers.csv");

    free(aux_user.iban1);
    free(aux_user.iban2);
    free(aux_user.iban3);

    return;
}

void topUpAccount(User_Credentials *user, Card_Data *selected_iban, char choice_iban, float amount_to_top_up){
    User_Credentials aux_user;
    FILE *originalFile, *tempFile;
    fopen_s(&originalFile, "customers.csv", "r");
    fopen_s(&tempFile, "temp.csv", "w");
    if ((originalFile == NULL) || (tempFile == NULL)) {
        printf("Error opening the file.\nPlease run the program again.");
        exit(1);
    }

    fputs(CSV_HEADER, tempFile);
    
    aux_user.iban1 = malloc(sizeof(Card_Data));
    aux_user.iban2 = malloc(sizeof(Card_Data));
    aux_user.iban3 = malloc(sizeof(Card_Data));

    char header[300]; 
    fgets(header, sizeof(header), originalFile);

    while (fscanf(originalFile, CLIENT_FORMAT_CSV_OUT,
                                        aux_user.name, 
                                        aux_user.surname,
                                        aux_user.telephone_number, 
                                        aux_user.password, 
                                        &aux_user.number_of_cards,
                                        aux_user.iban1->iban, 
                                        &aux_user.iban1->balance,
                                        aux_user.iban1->currency, 
                                        aux_user.iban2->iban, 
                                        &aux_user.iban2->balance,
                                        aux_user.iban2->currency, 
                                        aux_user.iban3->iban, 
                                        &aux_user.iban3->balance,
                                        aux_user.iban3->currency) == 14) {
        if (strcmp(user->telephone_number, aux_user.telephone_number) == 0 &&
            strcmp(user->password, aux_user.password) == 0){
            if(choice_iban == '1'){
                aux_user.iban1->balance += amount_to_top_up;
                selected_iban->balance += amount_to_top_up;
            }
            else if(choice_iban == '2'){
                aux_user.iban2->balance += amount_to_top_up;
                selected_iban->balance += amount_to_top_up;
            }
            else if(choice_iban == '3'){
                aux_user.iban3->balance += amount_to_top_up;
                selected_iban->balance += amount_to_top_up;
            }
        }
        fprintf(tempFile, CLIENT_FORMAT_CSV_IN,
                                    aux_user.name, 
                                    aux_user.surname,
                                    aux_user.telephone_number, 
                                    aux_user.password, 
                                    aux_user.number_of_cards,
                                    aux_user.iban1->iban, 
                                    aux_user.iban1->balance,
                                    aux_user.iban1->currency, 
                                    aux_user.iban2->iban, 
                                    aux_user.iban2->balance,
                                    aux_user.iban2->currency, 
                                    aux_user.iban3->iban, 
                                    aux_user.iban3->balance,
                                    aux_user.iban3->currency);
    }

    fclose(originalFile);
    fclose(tempFile);

    remove("customers.csv");
    rename("temp.csv", "customers.csv");

    free(aux_user.iban1);
    free(aux_user.iban2);
    free(aux_user.iban3);

    return;
}

float convertCurrency(float amount, char from_currency[4], char to_currency[4]) {
    if (strcmp(from_currency, "RON") == 0 && strcmp(to_currency, "USD") == 0){
        return amount / 5.0;
    } 
    else if (strcmp(from_currency, "USD") == 0 && strcmp(to_currency, "RON") == 0){
        return amount * 5.0;
    } 
    else if (strcmp(from_currency, "RON") == 0 && strcmp(to_currency, "EUR") == 0){
        return amount / 5.0;
    } 
    else if (strcmp(from_currency, "EUR") == 0 && strcmp(to_currency, "RON") == 0){
        return amount * 5.0;
    } 
    else if (strcmp(from_currency, "USD") == 0 && strcmp(to_currency, "EUR") == 0){
        return amount;
    } 
    else if (strcmp(from_currency, "EUR") == 0 && strcmp(to_currency, "USD") == 0){
        return amount;
    } 
    else if (strcmp(from_currency, to_currency) == 0){
        return amount;
    }
}



void transferMoney(User_Credentials *user, Card_Data *user_source, char *iban_destination, float amount_to_transfer) {
    User_Credentials aux_user;
    FILE *originalFile, *tempFile;
    fopen_s(&originalFile, "customers.csv", "r");
    fopen_s(&tempFile, "temp.csv", "w");
    if ((originalFile == NULL) || (tempFile == NULL)) {
        printf("Error opening the file.\nPlease run the program again.");
        exit(1);
    }

    fputs(CSV_HEADER, tempFile);

    aux_user.iban1 = malloc(sizeof(Card_Data));
    aux_user.iban2 = malloc(sizeof(Card_Data));
    aux_user.iban3 = malloc(sizeof(Card_Data));

    char header[300]; 
    fgets(header, sizeof(header), originalFile); 

    int aux_amount = amount_to_transfer;

    while (fscanf(originalFile, CLIENT_FORMAT_CSV_OUT,
                                        aux_user.name, 
                                        aux_user.surname,
                                        aux_user.telephone_number, 
                                        aux_user.password, 
                                        &aux_user.number_of_cards,
                                        aux_user.iban1->iban, 
                                        &aux_user.iban1->balance,
                                        aux_user.iban1->currency, 
                                        aux_user.iban2->iban, 
                                        &aux_user.iban2->balance,
                                        aux_user.iban2->currency, 
                                        aux_user.iban3->iban, 
                                        &aux_user.iban3->balance,
                                        aux_user.iban3->currency) == 14) 
    {
        amount_to_transfer = aux_amount;
        if (strcmp(iban_destination, user->iban1->iban) == 0 ||
            strcmp(iban_destination, user->iban2->iban) == 0 ||
            strcmp(iban_destination, user->iban3->iban) == 0) {
        
            if(strcmp(user_source->iban, aux_user.iban1->iban) == 0){
                aux_user.iban1->balance -= amount_to_transfer;
                user_source->balance -= amount_to_transfer;
                if(strcmp(aux_user.iban2->iban, iban_destination) == 0){
                    amount_to_transfer = convertCurrency(amount_to_transfer, user_source->currency, aux_user.iban2->currency);
                    aux_user.iban2->balance += amount_to_transfer;
                    user->iban2->balance += amount_to_transfer;
                }
                else if(strcmp(aux_user.iban3->iban, iban_destination) == 0){
                    amount_to_transfer = convertCurrency(amount_to_transfer, user_source->currency, aux_user.iban3->currency);
                    aux_user.iban3->balance += amount_to_transfer;
                    user->iban3->balance += amount_to_transfer;
                }
            }

            else if(strcmp(user_source->iban, aux_user.iban2->iban) == 0){
                user_source->balance -= amount_to_transfer;
                aux_user.iban2->balance -= amount_to_transfer;
                if(strcmp(aux_user.iban1->iban, iban_destination) == 0){
                    amount_to_transfer = convertCurrency(amount_to_transfer, user_source->currency, aux_user.iban1->currency);
                    aux_user.iban1->balance += amount_to_transfer;
                    user->iban1->balance += amount_to_transfer;
                }
                else if(strcmp(aux_user.iban3->iban, iban_destination) == 0){
                    amount_to_transfer = convertCurrency(amount_to_transfer, user_source->currency, aux_user.iban3->currency);
                    aux_user.iban3->balance += amount_to_transfer;
                    user->iban3->balance += amount_to_transfer;
                }
            }
            else if(strcmp(user_source->iban, aux_user.iban3->iban) == 0){
                user_source->balance -= amount_to_transfer;
                aux_user.iban3->balance -= amount_to_transfer;
                if(strcmp(aux_user.iban1->iban, iban_destination) == 0){
                    amount_to_transfer = convertCurrency(amount_to_transfer, user_source->currency, aux_user.iban1->currency);
                    aux_user.iban1->balance += amount_to_transfer;
                    user->iban1->balance += amount_to_transfer;
                }
                else if(strcmp(aux_user.iban2->iban, iban_destination) == 0){
                    amount_to_transfer = convertCurrency(amount_to_transfer, user_source->currency, aux_user.iban2->currency);
                    aux_user.iban2->balance += amount_to_transfer;
                    user->iban2->balance += amount_to_transfer;
                }
            }
        }
        
        else if (strcmp(iban_destination, user->iban1->iban) != 0 &&
                 strcmp(iban_destination, user->iban2->iban) != 0 &&
                 strcmp(iban_destination, user->iban3->iban) != 0){

            if (strcmp(aux_user.iban1->iban, user_source->iban) == 0) {
                aux_user.iban1->balance -= amount_to_transfer;
                user_source->balance -= amount_to_transfer;
            } 
            else if (strcmp(aux_user.iban2->iban, user_source->iban) == 0) {
                aux_user.iban2->balance -= amount_to_transfer;
                user_source->balance -= amount_to_transfer;
            } 
            else if (strcmp(aux_user.iban3->iban, user_source->iban) == 0) {
                aux_user.iban3->balance -= amount_to_transfer;
                user_source->balance -= amount_to_transfer;
            } 
            else if (strcmp(aux_user.iban1->iban, iban_destination) == 0){
                amount_to_transfer = convertCurrency(amount_to_transfer, user_source->currency, aux_user.iban1->currency);
                aux_user.iban1->balance += amount_to_transfer;
            }
            else if (strcmp(aux_user.iban2->iban, iban_destination) == 0){
                amount_to_transfer = convertCurrency(amount_to_transfer, user_source->currency, aux_user.iban2->currency);
                aux_user.iban2->balance += amount_to_transfer;
            }
            else if (strcmp(aux_user.iban3->iban, iban_destination) == 0){
                amount_to_transfer = convertCurrency(amount_to_transfer, user_source->currency, aux_user.iban3->currency);
                aux_user.iban3->balance += amount_to_transfer;
            }
        }
        
        fprintf(tempFile, CLIENT_FORMAT_CSV_IN,
                                    aux_user.name, 
                                    aux_user.surname,
                                    aux_user.telephone_number, 
                                    aux_user.password, 
                                    aux_user.number_of_cards,
                                    aux_user.iban1->iban, 
                                    aux_user.iban1->balance,
                                    aux_user.iban1->currency, 
                                    aux_user.iban2->iban, 
                                    aux_user.iban2->balance,
                                    aux_user.iban2->currency, 
                                    aux_user.iban3->iban, 
                                    aux_user.iban3->balance,
                                    aux_user.iban3->currency);
    }

    fclose(originalFile);
    fclose(tempFile);

    remove("customers.csv");
    rename("temp.csv", "customers.csv");

    free(aux_user.iban1);
    free(aux_user.iban2);
    free(aux_user.iban3);

    return;
}

