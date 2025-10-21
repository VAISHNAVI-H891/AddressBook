/*
This file contains helper functions to:  
- validate name, phone, and email inputs  
- check for duplicate contacts in the address book  */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

/*
This function checks if a given name is valid.
The name cannot start or end with a space or a dot (.).
Only letters (A–Z, a–z), dots (.), and spaces ( ) are allowed.
If any other character is found, it’s invalid.
If all rules are followed, it returns 1 (valid), otherwise 0 (invalid).*/
int getValidName(const char *name_str) {
    int len = strlen(name_str); 
    if (name_str[0] == ' ' || name_str[0] == '.' ||
        name_str[len - 1] == ' ' || name_str[len - 1] == '.') {
        return 0;// not valid if it starts/ends with space or dot
    }

    for (int i = 0; name_str[i] != '\0'; i++) {
        char ch = name_str[i];
        if (!((ch >= 'A' && ch <= 'Z') ||
              (ch >= 'a' && ch <= 'z') ||
              ch == '.' || ch == ' ')) {
            return 0;// not valid if other characters found
        }
    }
    return 1;// valid name
}

// ✅ check if phone is okay (must be exactly 10 digits)
/*
The getValidPhone function checks if a phone number is valid.
It must be exactly 10 digits long.
Every character must be a number (0–9).
If these conditions are met, it returns 1 (valid); otherwise, it returns 0 (invalid).*/
int getValidPhone(char *phone_str) {
    if (strlen(phone_str) != 10) return 0;
    for (int i = 0; phone_str[i] != '\0'; i++) {
        if (!(phone_str[i] >= '0' && phone_str[i] <= '9')) {
            return 0; // Not valid if not a number
        }
    }
    return 1; // valid phone
}

// ✅ check if email is okay (must have @, must end with .com, no double dots)
/*
This function checks if an email is valid.
Must be at least 5 characters long.
Must end with “.com”.
Must have exactly one @, not at the start or end.
Must have at least one dot (.) after the @.
Cannot start with a dot, and no two dots together.
Can only contain letters, numbers, or _ besides @ and ..
also converts the user entered email to lowercase
*/
int isValidEmail(char *email_str) {  // remove const so we can modify
    int len = strlen(email_str), at = 0, dot = 0;
    // 🔽 Convert entire email to lowercase in place
    for (int i = 0; i < len; i++) {
        email_str[i] = tolower((unsigned char) email_str[i]);
    }
    if (len < 5) return 0; // too short
    if (strcmp(email_str + len - 4, ".com") != 0) return 0; // must end with .com

    for (int i = 0; i < len; i++) {
        char ch = email_str[i]; 
        if (ch == '@') {
            if (at || i == 0 || i == len - 1) return 0; // only one @ allowed, not first/last
            at = 1;
        } else if (ch == '.') {
            if (i == 0 || email_str[i - 1] == '.') return 0; // no starting dot or two dots together
            if (at) dot = 1; // dot must come after @
        } else if (!(isalnum(ch) || ch == '_')) {
            return 0; // only letters, numbers, and _ allowed
        }
    }
    return (at && dot); // must have @ and at least one dot after it
}

// ✅check if contact is already saved (same name, phone, and email)
/*
The isDuplicate function checks if a contact with the same name, phone, and email already exists in the address book.
 It goes through all saved contacts one by one, and if it finds an exact match, it returns 1 (meaning duplicate). 
If no match is found, it returns 0 (meaning it’s a new contact)*/
int isDuplicate(AddressBook *addressBook, const char *name, const char *phone, const char *email) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0 &&
            strcmp(addressBook->contacts[i].phone, phone) == 0 &&
            strcmp(addressBook->contacts[i].email, email) == 0) {
            return 1;// found same contact
        }
    }
    return 0; // not duplicate
}
