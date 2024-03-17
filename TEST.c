#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

// Your structures
typedef struct {
    char account_id[6];
    char password[20];
    char iban[25];
    float balance;
} Personal_Data;

typedef struct {
    char name[20];
    char surname[20];
    char telephone_number[20];
    Personal_Data *link;
} User_Credentials;

// Function to convert User_Credentials to JSON object
json_object *user_credentials_to_json(User_Credentials *user) {
    json_object *user_json = json_object_new_object();
    json_object_object_add(user_json, "name", json_object_new_string(user->name));
    json_object_object_add(user_json, "surname", json_object_new_string(user->surname));
    json_object_object_add(user_json, "telephone_number", json_object_new_string(user->telephone_number));
    
    // Here you can add more fields as necessary
    
    return user_json;
}

// Function to append JSON data to file
void append_to_json_file(const char *filename, json_object *new_data) {
    FILE *file = fopen(filename, "a+");
    if (file != NULL) {
        // Get current file size
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        if (size > 0) {
            // If file is not empty, move back before the last character ("]")
            fseek(file, -1, SEEK_END);
            fprintf(file, ",");
        }
        
        // Convert JSON object to string and write to file
        const char *json_str = json_object_to_json_string_ext(new_data, JSON_C_TO_STRING_PRETTY);
        fprintf(file, "\n%s]", json_str); // Closing bracket for array
        
        fclose(file);
    } else {
        printf("Failed to open file for appending.\n");
    }
}

int main() {
    // Create sample user
    User_Credentials user;
    strcpy(user.name, "John");
    strcpy(user.surname, "Doe");
    strcpy(user.telephone_number, "1234567890");
    
    // Convert user credentials to JSON
    json_object *user_json = user_credentials_to_json(&user);
    
    // Append JSON data to file
    append_to_json_file("users.json", user_json);
    
    // Free memory
    json_object_put(user_json);
    
    return 0;
}