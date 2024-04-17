#pragma once
#include <io.h>
#include "account_management.h"

void withdrawCash(User_Credentials *user, Card_Data *selected_iban, char choice_iban, float amount_to_withdraw);
void topUpAccount(User_Credentials *user, Card_Data *selected_iban, char choice_iban, float amount_to_top_up);
void transferMoney(User_Credentials *user, Card_Data *user_source, char *iban_destination, float amount_to_transfer);
float convertCurrency(float amount, char from_currency[4], char to_currency[4]);