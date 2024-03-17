#include "data_generator.h"

#define IBAN_LENGTH 24

char* generate_random_iban() {
    char* iban = (char*)malloc((IBAN_LENGTH + 1) * sizeof(char)); 
    if (iban == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        printf("Please run the program again.");
        exit(1);
    }
    
    // Generate the 'RO24' prefix
    sprintf(iban, "RO24");

    srand(time(0));
    // Generate 4 random letters
    for (int i = 4; i < 8; i++) {
        iban[i] = 'A' + (rand() % 26);
    }

    // Generate 16 random digits
    for (int i = 8; i < 24; i++) {
        iban[i] = '0' + (rand() % 10);
    }

    iban[IBAN_LENGTH] = '\0'; // Null-terminate the string
    return iban;
}
