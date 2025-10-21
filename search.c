/*This FILE is used for searching the contacts
by- name
    phone
    Email
    If many contacts match, you can pick one from the list.
*/
#include <stdio.h>
#include <string.h>
#include "contact.h"
#include <ctype.h>
// find contact by name
/*
This function search contact by name.
It asks for query.
If the query matches with the addressbook contact it should print.
Even if the substring matches also it should display.
If multiple contact matches then display all of them and ask user which contact to select.
then prints the selected contact. */
void searchByName(AddressBook *addressBook, char *query) {
    Contact found[100];
    int foundCount = 0;

    // convert query to lowercase
    for (int k = 0; query[k]; k++) query[k] = tolower((unsigned char)query[k]);

    for (int i = 0; i < addressBook->contactCount; i++) {
        char nameLower[50];
        strcpy(nameLower, addressBook->contacts[i].name);
        for (int k = 0; nameLower[k]; k++) nameLower[k] = tolower((unsigned char)nameLower[k]);

        if (strstr(nameLower, query)) {
            found[foundCount] = addressBook->contacts[i];
            printf("%d. %s | %s | %s\n",
                   foundCount + 1,
                   found[foundCount].name,
                   found[foundCount].phone,
                   found[foundCount].email);
            foundCount++;
        }
    }

    if (foundCount == 0) {
        printf("Contact not found!\n");
        return;
    }

    int select = 1;
    if (foundCount > 1) {
        printf("\nMultiple contacts found. Enter number to select (1-%d): ", foundCount);
        scanf("%d", &select);
    }

    if (select > 0 && select <= foundCount) {
        Contact chosen = found[select - 1];
        printf("\nSelected Contact:\n");
        printf("Name : %s\n", chosen.name);
        printf("Phone: %s\n", chosen.phone);
        printf("Email: %s\n", chosen.email);
    } else {
        printf("Invalid selection!\n");
    }
}
//Search Contacts by phone number
/*
This function uses searchbyphone option.
It goes through all contacts and checks if the name contains the search text (query).
If matches are found, it lists them.
If no matches are found, it shows “Contact not found!”.
If multiple matches exist, it asks the user to pick one from the list.
Finally, it shows the details (name, phone, email) of the selected contact.
*/
void searchByPhone(AddressBook *addressBook, char *query) {
    Contact found[100];
    int foundCount = 0;

    for (int k = 0; query[k]; k++) query[k] = tolower((unsigned char)query[k]);

    for (int i = 0; i < addressBook->contactCount; i++) {
        char phoneLower[20];
        strcpy(phoneLower, addressBook->contacts[i].phone);
        for (int k = 0; phoneLower[k]; k++) phoneLower[k] = tolower((unsigned char)phoneLower[k]);

        if (strstr(phoneLower, query)) {
            found[foundCount] = addressBook->contacts[i];
            printf("%d. %s | %s | %s\n",
                   foundCount + 1,
                   found[foundCount].name,
                   found[foundCount].phone,
                   found[foundCount].email);
            foundCount++;
        }
    }

    if (foundCount == 0) {
        printf("Contact not found!\n");
        return;
    }

    int select = 1;
    if (foundCount > 1) {
        printf("\nMultiple contacts found. Enter number to select (1-%d): ", foundCount);
        scanf("%d", &select);
    }

    if (select > 0 && select <= foundCount) {
        Contact chosen = found[select - 1];
        printf("\nSelected Contact:\n");
        printf("Name : %s\n", chosen.name);
        printf("Phone: %s\n", chosen.phone);
        printf("Email: %s\n", chosen.email);
    } else {
        printf("Invalid selection!\n");
    }
}
//Search contact by Email
/*
The searchByEmail function looks for contacts using an email or part of an email.
It goes through all contacts and checks if their email contains the given search text (query).
Every match is saved and displayed in a list.
If no contact matches, it shows “Contact not found!”.
If multiple matches are found, it asks the user to pick one from the list.
Finally, it displays the full details (name, phone, email) of the selected contact.*/
void searchByEmail(AddressBook *addressBook, char *query) {
    Contact found[100];
    int foundCount = 0;

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strstr(addressBook->contacts[i].email, query))//search for query
         {
            found[foundCount] = addressBook->contacts[i];//save to contact
            printf("%d. %s | %s | %s\n",                   //display the contact
                   foundCount + 1,
                   found[foundCount].name,
                   found[foundCount].phone,
                   found[foundCount].email);
            foundCount++;
        }
    }

    //If no matches found
    if (foundCount == 0) {
        printf("Contact not found!\n");
        return;
    }

    //If multiple matches found
    int select = 1;
    if (foundCount > 1) {
        printf("\nMultiple contacts found. Enter number to select (1-%d): ", foundCount);
        scanf("%d", &select);
    }

    //Display the selected contact
    if (select > 0 && select <= foundCount) {
        Contact chosen = found[select - 1];
        printf("\nSelected Contact:\n");
        printf("Name : %s\n", chosen.name);
        printf("Phone: %s\n", chosen.phone);
        printf("Email: %s\n", chosen.email);
    } else {
        printf("Invalid selection!\n");
    }
}
