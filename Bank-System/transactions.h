#pragma once
#include <io.h>
#include "account_management.h"

void withdrawCash(User_Credentials *user, Card_Data *selected_iban, char choice_iban, float amount_to_withdraw);
void topUpAccount(User_Credentials *user, Card_Data *selected_iban, char choice_iban, float amount_to_top_up);
void transferMoney(Card_Data *user_source, char *iban_destination, float amount_to_append);