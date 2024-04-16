#pragma once
#include <io.h>
#include "account_management.h"

void withdrawCash(User_Credentials *user, float amount_to_withdraw);
void topUpAccount(User_Credentials *user, float amount_to_top_up);
void transferMoney(User_Credentials *user_source, char *iban_destination, float amount_to_append);