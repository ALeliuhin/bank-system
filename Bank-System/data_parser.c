#include "data_parser.h"

#define CLIENT_FORMAT_CSV "%s,%s,%s,%s,%s,%s,%.2f%s\n"
#define CSV_HEADER "ID,Name,Surname,Telephone,Password,IBAN,Balance"


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
    FILE* file;
    fopen_s(&file, "customers.csv", "a"); 

    if (file != NULL) {
        fprintf(file, CLIENT_FORMAT_CSV, user.account_id, 
                                         user.name, 
                                         user.surname, 
                                         user.telephone_number,
                                         user.password, 
                                         user.link->iban, 
                                         user.link->balance, 
                                         user.link->currency);
        fclose(file); 
    } 
}