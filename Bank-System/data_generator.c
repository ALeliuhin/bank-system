#include "data_generator.h"

void generate_random_iban(char* iban) {
    sprintf(iban, "RO24");

    srand(time(0));

    for (int i = 4; i < 8; i++) {
        iban[i] = 'A' + (rand() % 26);
    }

    for (int i = 8; i < 24; i++) {
        iban[i] = '0' + (rand() % 10);
    }

    iban[IBAN_LENGTH] = '\0'; 
}
