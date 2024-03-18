#include "data_parser.h"
#include "account_management.h"

const char* CLIENT_FORMAT_IN = "(%s, %s, %s, %s, %s, %.2f)\n";

void write_data(User_Credentials user){

    FILE* file;
    fopen_s(&file, "customers.dat", "a");

    fprintf(file, CLIENT_FORMAT_IN, user.link->account_id, user.name, user.surname, user.telephone_number, user.link->iban, user.link->balance);
    fseek(file, 0, SEEK_SET);

    fclose(file); 

}
