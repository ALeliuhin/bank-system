#include "data_generator.h"

#define IBAN_LENGTH 24

char* generate_random_iban() {
    char* iban = (char*)malloc((IBAN_LENGTH + 1) * sizeof(char)); 
    
    sprintf(iban, "RO24");

    srand(time(0));

    for (int i = 4; i < 8; i++) {
        iban[i] = 'A' + (rand() % 26);
    }

    for (int i = 8; i < 24; i++) {
        iban[i] = '0' + (rand() % 10);
    }

    iban[IBAN_LENGTH] = '\0'; 
    return iban;
    free(iban);
}
