#pragma once
#include <io.h>
#include "account_management.h"

void deleteAccount(User_Credentials user);
void modifyData(User_Credentials *user, char *data_to_modify);
void createCSV();
void write_data(User_Credentials user);
int validationData(const char *data_to_check);
User_Credentials readForLogging(char *bufferTelephone, char *buffernPassword);