#include "transactions.h"
#define CLIENT_FORMAT_CSV_IN "%s,%s,%s,%s,%s,%f,%s\n"
#define CLIENT_FORMAT_CSV_OUT "%[^,], %[^,], %[^,], %[^,], %[^,], %f,%[^,\n]\n"
#define CSV_HEADER "Name,Surname,Telephone,Password,IBAN,Balance,Currency\n"
#define MAX_SIZE 1024

void withdrawCash(User_Credentials *user, float amount_to_withdraw){
    User_Credentials aux_user;
    FILE *originalFile, *tempFile;
    fopen_s(&originalFile, "customers.csv", "r");
    fopen_s(&tempFile, "temp.csv", "w");
    if ((originalFile == NULL) || (tempFile == NULL)) {
        printf("Error opening the file.\nPlease run the program again.");
        exit(1);
    }

    fputs(CSV_HEADER, tempFile);
    
    aux_user.link = malloc(sizeof(Card_Data));

    char header[100]; 
    fgets(header, sizeof(header), originalFile);

    while (fscanf(originalFile, CLIENT_FORMAT_CSV_OUT,
                  aux_user.name,
                  aux_user.surname,
                  aux_user.telephone_number,
                  aux_user.password,
                  aux_user.link->iban,
                  &aux_user.link->balance,
                  aux_user.link->currency) == 7) {
        if (strcmp(user->telephone_number, aux_user.telephone_number) == 0 &&
            strcmp(user->password, aux_user.password) == 0 &&
            strcmp(user->link->iban, aux_user.link->iban) == 0) {
            aux_user.link->balance -= amount_to_withdraw;
            user->link->balance -= amount_to_withdraw;
        }
        fprintf(tempFile, CLIENT_FORMAT_CSV_IN,
                aux_user.name,
                aux_user.surname,
                aux_user.telephone_number,
                aux_user.password,
                aux_user.link->iban,
                aux_user.link->balance,
                aux_user.link->currency);
    }

    fclose(originalFile);
    fclose(tempFile);

    remove("customers.csv");
    rename("temp.csv", "customers.csv");

    free(aux_user.link);
    
}

void topUpAccount(User_Credentials *user, float amount_to_top_up){
    User_Credentials aux_user;
    FILE *originalFile, *tempFile;
    fopen_s(&originalFile, "customers.csv", "r");
    fopen_s(&tempFile, "temp.csv", "w");
    if ((originalFile == NULL) || (tempFile == NULL)) {
        printf("Error opening the file.\nPlease run the program again.");
        exit(1);
    }

    fputs(CSV_HEADER, tempFile);
    
    aux_user.link = malloc(sizeof(Card_Data));

    char header[100]; 
    fgets(header, sizeof(header), originalFile);

    while (fscanf(originalFile, CLIENT_FORMAT_CSV_OUT,
                  aux_user.name,
                  aux_user.surname,
                  aux_user.telephone_number,
                  aux_user.password,
                  aux_user.link->iban,
                  &aux_user.link->balance,
                  aux_user.link->currency) == 7) {
        if (strcmp(user->telephone_number, aux_user.telephone_number) == 0 &&
            strcmp(user->password, aux_user.password) == 0 &&
            strcmp(user->link->iban, aux_user.link->iban) == 0) {
            aux_user.link->balance += amount_to_top_up;
            user->link->balance += amount_to_top_up;
        }
        fprintf(tempFile, CLIENT_FORMAT_CSV_IN,
                aux_user.name,
                aux_user.surname,
                aux_user.telephone_number,
                aux_user.password,
                aux_user.link->iban,
                aux_user.link->balance,
                aux_user.link->currency);
    }

    fclose(originalFile);
    fclose(tempFile);

    remove("customers.csv");
    rename("temp.csv", "customers.csv");

    free(aux_user.link);
}

void transferMoney(User_Credentials *user_source, char *iban_destination, float amount_to_transfer) {
    User_Credentials aux_user;
    FILE *originalFile, *tempFile;
    fopen_s(&originalFile, "customers.csv", "r");
    fopen_s(&tempFile, "temp.csv", "w");
    if ((originalFile == NULL) || (tempFile == NULL)) {
        printf("Error opening the file.\nPlease run the program again.");
        exit(1);
    }

    fputs(CSV_HEADER, tempFile);

    aux_user.link = malloc(sizeof(Card_Data));

    char header[100]; 
    fgets(header, sizeof(header), originalFile); 

    while (fscanf(originalFile, CLIENT_FORMAT_CSV_OUT,
                  aux_user.name,
                  aux_user.surname,
                  aux_user.telephone_number,
                  aux_user.password,
                  aux_user.link->iban,
                  &aux_user.link->balance,
                  aux_user.link->currency) == 7) 
    {
        if (strcmp(aux_user.link->iban, user_source->link->iban) == 0) {
            aux_user.link->balance -= amount_to_transfer;
            user_source->link->balance -= amount_to_transfer;
        } 
        else if (strcmp(aux_user.link->iban, iban_destination) == 0){
            aux_user.link->balance += amount_to_transfer;
        }
        fprintf(tempFile, CLIENT_FORMAT_CSV_IN,
                aux_user.name,
                aux_user.surname,
                aux_user.telephone_number,
                aux_user.password,
                aux_user.link->iban,
                aux_user.link->balance,
                aux_user.link->currency);
    }

    fclose(originalFile);
    fclose(tempFile);

    remove("customers.csv");
    rename("temp.csv", "customers.csv");

    free(aux_user.link);

    return;
}
