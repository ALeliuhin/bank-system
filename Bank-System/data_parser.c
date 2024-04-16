#include "data_parser.h"

#define CLIENT_FORMAT_CSV_IN "%s,%s,%s,%s,%d,%s,%f,%s,%s,%f,%s,%s,%f,%s\n"
#define CLIENT_FORMAT_CSV_OUT "%[^,], %[^,], %[^,], %[^,], %d, %[^,], %f, %[^,], %[^,], %f, %[^,], %[^,], %f, %[^,\n]\n"
#define CSV_HEADER "Name,Surname,Telephone,Password,Cards,IBAN-1,Balance-1,Currency-1,IBAN-2,Balance-2,Currency-2,IBAN-3,Balance-3,Currency-3\n"


int validationData(const char *data_to_check){
    User_Credentials user;
    FILE *file;
    fopen_s(&file, "customers.csv", "r");

    if (file == NULL) {
        printf("Error opening the file.\nPlease run the program again.");
        exit(1);
    }

    user.iban1 = malloc(sizeof(Card_Data)); 
    user.iban2 = malloc(sizeof(Card_Data)); 
    user.iban3 = malloc(sizeof(Card_Data)); 

    char header[300]; 
    
    fgets(header, sizeof(header), file);

    while (fscanf(file, CLIENT_FORMAT_CSV_OUT,
                                           user.name, 
                                           user.surname,
                                           user.telephone_number, 
                                           user.password, 
                                           &user.number_of_cards,
                                           user.iban1->iban, 
                                           &user.iban1->balance,
                                           user.iban1->currency, 
                                           user.iban2->iban, 
                                           &user.iban2->balance,
                                           user.iban2->currency, 
                                           user.iban3->iban, 
                                           &user.iban3->balance,
                                           user.iban3->currency) == 14) 
    {
        if (strcmp(user.telephone_number, data_to_check) == 0 ||
            strcmp(user.iban1->iban, data_to_check) == 0 ||
            strcmp(user.iban2->iban, data_to_check) == 0 ||
            strcmp(user.iban3->iban, data_to_check) == 0){
                fclose(file);
                free(user.iban1);
                free(user.iban2);
                free(user.iban3);
                return 1;
            }
    }

    fclose(file);
    free(user.iban1);
    free(user.iban2);
    free(user.iban3);
    return 0;
}

void modifyData(User_Credentials *user, char*data_to_modify, char iban_choice){
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
            strcmp(user->password, aux_user.password) == 0) {
            if(strlen(data_to_modify) == 24){
                if(iban_choice == '1'){
                    strcpy(aux_user.iban1->iban, data_to_modify);
                    strcpy(user->iban1->iban, data_to_modify);
                }
                else if(iban_choice == '2'){
                    strcpy(aux_user.iban2->iban, data_to_modify);
                    strcpy(user->iban2->iban, data_to_modify);
                }
                else if(iban_choice == '3'){
                    strcpy(aux_user.iban3->iban, data_to_modify);
                    strcpy(user->iban3->iban, data_to_modify);
                }
            }
            else{
                strcpy(aux_user.password, data_to_modify);
                strcpy(user->password, data_to_modify);
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


void createNewCard(User_Credentials *user, char *new_card_iban, float new_card_balance, char *new_card_currency){
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
            strcmp(user->password, aux_user.password) == 0) {
            if(aux_user.number_of_cards == 1){

                aux_user.number_of_cards++;
                user->number_of_cards++;

                strcpy(aux_user.iban2->iban, new_card_iban);
                strcpy(user->iban2->iban, new_card_iban);

                aux_user.iban2->balance = new_card_balance;
                user->iban2->balance = new_card_balance;

                strcpy(aux_user.iban2->currency, new_card_currency);
                strcpy(user->iban2->currency, new_card_currency);
            }
            else if(aux_user.number_of_cards == 2){
                
                aux_user.number_of_cards++;
                user->number_of_cards++;

                strcpy(aux_user.iban3->iban, new_card_iban);
                strcpy(user->iban3->iban, new_card_iban);

                aux_user.iban3->balance = new_card_balance;
                user->iban3->balance = new_card_balance;

                strcpy(aux_user.iban3->currency, new_card_currency);
                strcpy(user->iban3->currency, new_card_currency);
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


void deleteAccount(User_Credentials user) {
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
        if (strcmp(user.telephone_number, aux_user.telephone_number) == 0 &&
            strcmp(user.password, aux_user.password) == 0 &&
            strcmp(user.iban1->iban, aux_user.iban1->iban) == 0) {
            continue; 
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


User_Credentials readForLogging(char *bufferTelephone, char *bufferPassword) {
    User_Credentials user;
    FILE *file;
    fopen_s(&file, "customers.csv", "r");

    if (file == NULL) {
        printf("Error opening the file.\nPlease run the program again.");
        exit(1);
    }

    user.iban1 = malloc(sizeof(Card_Data)); 
    user.iban2 = malloc(sizeof(Card_Data));
    user.iban3 = malloc(sizeof(Card_Data));

    char header[300]; 
    
    fgets(header, sizeof(header), file);

    while (fscanf(file, CLIENT_FORMAT_CSV_OUT,
                                        user.name, 
                                        user.surname,
                                        user.telephone_number, 
                                        user.password, 
                                        &user.number_of_cards,
                                        user.iban1->iban, 
                                        &user.iban1->balance,
                                        user.iban1->currency, 
                                        user.iban2->iban, 
                                        &user.iban2->balance,
                                        user.iban2->currency, 
                                        user.iban3->iban, 
                                        &user.iban3->balance,
                                        user.iban3->currency) == 14) 
    {
        if (strcmp(user.telephone_number, bufferTelephone) == 0 && strcmp(user.password, bufferPassword) == 0){
            fclose(file);
            clear_screen();
            return user;
        }
        else{
            continue;
        }
    }
    free(user.iban1);
    free(user.iban2);
    free(user.iban3);
    fclose(file);
    printf("Invalid data or credentials. Please try again.\n");
    free(bufferTelephone);
    free(bufferPassword);
    mainTerminal();
}


void createCSV() {
  
    if (access("customers.csv", F_OK) != -1) {
        return;
    }

    FILE* file;
    fopen_s(&file, "customers.csv", "w");

    if (file != NULL) {
        fprintf(file, "%s", CSV_HEADER); 
        fclose(file); 
    } 

}

void write_data(User_Credentials user){
    FILE *file;
    fopen_s(&file, "customers.csv", "a"); 

    if (file != NULL) {
        fprintf(file, CLIENT_FORMAT_CSV_IN, 
                                        user.name, 
                                        user.surname, 
                                        user.telephone_number,
                                        user.password, 
                                        user.number_of_cards,
                                        user.iban1->iban, 
                                        user.iban1->balance, 
                                        user.iban1->currency,
                                        user.iban2->iban,
                                        user.iban2->balance,
                                        user.iban2->currency,
                                        user.iban3->iban,
                                        user.iban3->balance,
                                        user.iban3->currency);
        fclose(file); 
    } 
    else{
        printf("Error opening the file.\nPlease run the program again.");
        exit(1);
    }
}

