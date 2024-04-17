#pragma once
#include <io.h>
#include "account_management.h"

void deleteAccount(User_Credentials user);
void modifyData(User_Credentials *user, char*data_to_modify, char iban_choice);
void createCSV();
void write_data(User_Credentials user);
int validationData(const char *data_to_check);
void createNewCard(User_Credentials *user, char *new_card_iban, float new_card_balance, char *new_card_currency);
User_Credentials readForLogging(char *bufferTelephone, char *buffernPassword);