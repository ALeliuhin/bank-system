#include "data_parser.h"

#define CLIENT_FORMAT_CSV_IN "%s,%s,%s,%s,%s,%f,%s\n"
#define CLIENT_FORMAT_CSV_OUT "%[^,], %[^,], %[^,], %[^,], %[^,], %f,%[^,\n]\n"
#define CSV_HEADER "Name,Surname,Telephone,Password,IBAN,Balance,Currency\n"


int validationData(const char *data_to_check){
    User_Credentials user;
    FILE *file;
    fopen_s(&file, "customers.csv", "r");

    if (file == NULL) {
        printf("Error opening the file.\nPlease run the program again.");
        exit(1);
    }

    user.link = malloc(sizeof(Card_Data)); 
    char header[100]; 
    
    fgets(header, sizeof(header), file);

    while (fscanf(file, CLIENT_FORMAT_CSV_OUT,
                                           user.name, 
                                           user.surname,
                                           user.telephone_number, 
                                           user.password, 
                                           user.link->iban, 
                                           &user.link->balance,
                                           user.link->currency) == 7) 
    {
        if (strcmp(user.telephone_number, data_to_check) == 0 ||
            strcmp(user.link->iban, data_to_check) == 0){
                fclose(file);
                free(user.link);
                return 1;
            }
    }

    fclose(file);
    free(user.link);
    return 0;
}

void modifyData(User_Credentials *user, char*data_to_modify){
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
            if(strlen(data_to_modify) == 24){
                strcpy(aux_user.link->iban, data_to_modify);
                strcpy(user->link->iban, data_to_modify);
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
        if (strcmp(user.telephone_number, aux_user.telephone_number) == 0 &&
            strcmp(user.password, aux_user.password) == 0 &&
            strcmp(user.link->iban, aux_user.link->iban) == 0) {
            continue; 
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


User_Credentials readForLogging(char *bufferTelephone, char *bufferPassword) {
    User_Credentials user;
    FILE *file;
    fopen_s(&file, "customers.csv", "r");

    if (file == NULL) {
        printf("Error opening the file.\nPlease run the program again.");
        exit(1);
    }

    user.link = malloc(sizeof(Card_Data)); 
    char header[100]; 
    
    fgets(header, sizeof(header), file);

    while (fscanf(file, CLIENT_FORMAT_CSV_OUT,
                                           user.name, 
                                           user.surname,
                                           user.telephone_number, 
                                           user.password, 
                                           user.link->iban, 
                                           &user.link->balance,
                                           user.link->currency) == 7) 
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
    free(user.link);
    fclose(file);
    printf("Invalid data or credentials. Please try again.\n");
    free(bufferTelephone);
    free(bufferPassword);
    main();
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
                                         user.link->iban, 
                                         user.link->balance, 
                                         user.link->currency);
        fclose(file); 
    } 
    else{
        printf("Error opening the file.\nPlease run the program again.");
        exit(1);
    }
}

