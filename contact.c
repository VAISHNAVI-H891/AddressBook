/*
Name : Vaishnavi Hujaratti
Batch :25017E
Description : Address Book Project
This project is a simple program to store and manage contacts. It lets you add, view, edit, delete,block and search for contacts easily.
Date : 22-08-25
*/
/*  
📂 file.c  
This file has the main working functions of the Address Book.  
It can:  
- Show all contacts (sorted by name, phone, or email)  
- Load contacts from file or add default contacts  
- Save contacts to file  
- Create new contacts  
- Search contacts by name, phone, or email  
- Edit details of an existing contact  
- Delete a contact (with confirmation) 
-Block and list the block contacts 
It basically handles almost everything the address book can do.  
*/#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

/*
In this function we are Listing all the contacts from the addressbook ,by sorting them (name,phone,email).
It first checks that contacts are there or not,then sorts them.
It swaps them if the contcts are in wrong order using a temporary variable.
Then prints the sorted list.
*/
void listContacts(AddressBook *addressBook, int choice) 
{
    if (addressBook->contactCount == 0) 
    {
        printf("\nNo contacts available!\n");
        return;
    }

    int i, j;
    Contact temp;   // temporary variable for swapping

    // Bubble sort
    for (i = 0; i < addressBook->contactCount - 1; i++) 
    {
        for (j = 0; j < addressBook->contactCount - i - 1; j++) 
        {
            int cmp = 0;

            if (choice == 1) // sort by name
                cmp = strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name);
            else if (choice == 2) // sort by phone
                cmp = strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone);
            else if (choice == 3) // sort by email
                cmp = strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email);
            else 
            {
                printf("Invalid choice!\n");
                return;
            }

            if (cmp > 0) 
            {
                // swap
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    // Print sorted contacts
    printf("\nSorted Contact List:\n");
    for (i = 0; i < addressBook->contactCount; i++) 
    {
        printf("%d. Name: %s | Phone: %s | Email: %s\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
}


// Initialization function
/*
The initialize function sets up the address book when the program starts.
It starts with zero contacts and zero blocked contacts.
It then tries to load saved contacts from a file.
If the file is empty (no contacts found), it will:
Add some default contacts.
Save them into the file for future use.
*/
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
     addressBook->blockedCount = 0; 
    loadContactsFromFile(addressBook);
    // Always populate with default contacts
      if(addressBook->contactCount == 0 ) 
    {
    populateAddressBook(addressBook);

    // Save them to CSV (overwrite each run)
    saveContactsToFile(addressBook);
    }
}


// Save and exit function
/*
This function saves all contacts to a file and then closes the program safely after showing a message.
*/
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook);  // Save contacts to file
    printf("Contacts saved. Exiting program...\n");
    exit(EXIT_SUCCESS);  // Exit safely
}
/*
This function clears any extra characters left in the input (like when you press Enter or type extra stuff).
It keeps reading characters until it finds a newline (\n) or the end of the file (EOF).*/
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int getChoice() {
    int choice;
    while (1) {
        printf("Enter your choice: ");
        if (scanf("%d", &choice) == 1) {
            clearInputBuffer();  // clear leftover '\n'
            return choice;
        } else {
            printf("❌ Invalid input. Please enter a number.\n");
            clearInputBuffer();  // remove bad input
        }
    }
}
//// Function to create a new contact
/*
This function is used to create contact
-it askes user to enter name ,phone,and email
-it validates name ,phone and email by validate function.
-it checks if there is already a existing contact to avoid duplicates.
-then saves the contact to addressbook and increasing the contact count.*/
void createContact(AddressBook *addressBook) {
    char name_str[50];
    char phone_str[15];
    char email_str[50];

    // Ask for a valid name until it matches all condition
    do {
        printf("\n---------------Create Contact 👤---------------------\n");
        printf("Enter name: ");
         // Allowing user to cancel
        scanf(" %[^\n]", name_str);
        if (strcmp(name_str, "exit") == 0) {
            printf("⚠️ Contact creation cancelled.\n");
            return;
        }
        if (!getValidName(name_str)) printf("❌ Invalid name! Try again.\n");
        else break;
    } while (1);

    // Ask for a valid Phone number until it matches all condition
    do {
        printf("Enter phone: ");
        scanf("%s", phone_str);
        // Allowing user to cancel
        if (strcmp(phone_str, "exit") == 0) {
            printf("⚠️ Contact creation cancelled.\n");
            return;
        }
        if (!getValidPhone(phone_str)) printf("❌ Invalid phone! Must be 10 digits.\n");
        else break;
    } while (1);

    // Ask for a valid email  until it matches all condition
    do {
        printf("Enter email: ");
        scanf("%s", email_str);
         // Allowing user to cancel
        if (strcmp(email_str, "exit") == 0) {
            printf("⚠️ Contact creation cancelled.\n");
            return;
        }
        if (!isValidEmail(email_str)) printf("❌ Invalid email! Try again.\n");
        else break;
    } while (1);

    // check duplicates so that no duplicate contact is stored and contact is unique
    if (isDuplicate(addressBook, name_str, phone_str, email_str)) {
        printf("⚠️ Contact already exists with same name, phone, and email!\n");
        return;
    }

    // save contact
    strcpy(addressBook->contacts[addressBook->contactCount].name, name_str);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone_str);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email_str);
    addressBook->contactCount++;

    printf("✅ Contact added successfully.\n");
}

/*
This function is used to search contact.
-It askes user to enter choice -By what means user want to search.
-it calls different functions according to user choice like
- name -> searchbyname()
- phone-> searchbyphone()
- email-> searchbyemail()
  when the query matches the output is printed*/
void searchContact(AddressBook *addressBook) 
{
    int choice;
    char query[50]; // buffer for user input
    printf("\n--------------------Seach Contact🔍-----------------------\n");
    printf("Search by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter the choice: ");
    scanf(" %d", &choice);

    printf("Enter the query: ");
    scanf(" %49s", query);

    switch (choice) {
        case 1:
            searchByName(addressBook, query);
            break;
        case 2:
            searchByPhone(addressBook, query);
            break;
        case 3:
            searchByEmail(addressBook, query);
            break;
        default: 
            printf("Invalid choice!\n");
    }
}

// ✅ one helper to find contact
/*
This is used for searching match contact
choice 1->name
choice2-> phone
choice3->email
If it finds matching contact then reurns the index of contact and not the returns -1. */
int findContactIndex(AddressBook *addressBook, char *query, int choice) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if ((choice == 1 && strcmp(addressBook->contacts[i].name, query) == 0) ||
            (choice == 2 && strcmp(addressBook->contacts[i].phone, query) == 0) ||
            (choice == 3 && strcmp(addressBook->contacts[i].email, query) == 0)) {
            return i; // return index of found contact
        }
    }
    return -1; // not found
}
/*
This function is used to edit contact.
-It askes user to search contact by name,email,phone.
-If contact not found then warns saying no contact found.
-If found,then askes user what he want to edit: name ,phone,Email,all.
-After editing it validates the user input.
-Update the contact and shows a success message.*/
void editContact(AddressBook *addressBook) {
    int searchChoice;
    char query[50];
    printf("\n----------------Edit Contact ✏️---------------------------\n");
    printf("\nSearch contact to edit:\n");
    printf("1. By Name\n2. By Phone\n3. By Email\n");
    scanf("%d", &searchChoice);

    printf("Enter search query: ");
    scanf("%s", query);

    // use the index-based search
    int index = findContactIndex(addressBook, query, searchChoice);

    if (index == -1) {
        printf("⚠️ Contact not found!\n");
        return;
    }

    Contact *found = &addressBook->contacts[index];  // pointer to the contact

    int choice;
    char newValue[50];

    printf("\nWhat do you want to edit?\n");//Flexibility of what to edit
    printf("1. Name\n2. Phone\n3. Email\n4. All\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
        //Name editing
            printf("Enter new name: ");
            scanf(" %[^\n]", newValue);
            if (getValidName(newValue))//Validating entered name
                strcpy(found->name, newValue);//Updating the new name
            else
                printf("Invalid name!\n");
            break;

        case 2:
            //phone editing
            printf("Enter new phone: ");
            scanf("%s", newValue);
            if (getValidPhone(newValue))//Validating entered phone number 
                strcpy(found->phone, newValue);//Updating phone
            else
                printf("Invalid phone!\n");
            break;

        case 3:
            //Email editing
            printf("Enter new email: ");
            scanf("%s", newValue);
            if (isValidEmail(newValue))//Validating entered Email
                strcpy(found->email, newValue);//Updating email
            else
                printf("Invalid email!\n");
            break;

        case 4:
            //Editing whole contact-name,phone,email
            printf("Enter new name: ");
            scanf(" %[^\n]", newValue);
            if (getValidName(newValue))//Validating entered name
                strcpy(found->name, newValue);//Updating name

            printf("Enter new phone: ");
            scanf("%s", newValue);
            if (getValidPhone(newValue))//Validating entered phone number 
                strcpy(found->phone, newValue);//Updating phone

            printf("Enter new email: ");
            scanf("%s", newValue);
            if (isValidEmail(newValue))//Validating entered Email
                strcpy(found->email, newValue);//Updating email

            break;

        default:
            printf("Invalid choice!\n");
    }

    printf("Contact updated successfully!\n");
}
// Delete function for deleting Contact
/*
This function used for deleting contact.
It askes user to search contact by -name,e\phone,email.
-If contact not found then warns saying no contact found.
If found deletes the contact but before deleting asks for confirmation.
After delection of the contact in addressbook a contactcount is decremented.
A succes messahe of deletion is printed.
If the user enter exit then it returns back to menue.*/
void deleteContact(AddressBook *addressBook) {
    char query[50];
    int choice;
    int index = -1;

    printf("\n--------------Delete Contact🗑️------------------\n");
    printf("Search by:\n");//Allowing user to search by name,phone,email
    printf("1. Name\n2. Phone\n3. Email\n");
    scanf("%d", &choice);

    printf("\n------------------------------------------------\n");
    printf("Enter search query: ");
    scanf("%s", query);

    // find the contact index by comparing
    for (int i = 0; i < addressBook->contactCount; i++) {
        if ((choice == 1 && strcmp(addressBook->contacts[i].name, query) == 0) ||
            (choice == 2 && strcmp(addressBook->contacts[i].phone, query) == 0) ||
            (choice == 3 && strcmp(addressBook->contacts[i].email, query) == 0)) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        printf("Deleting contact: %s | %s | %s\n",
               addressBook->contacts[index].name,
               addressBook->contacts[index].phone,
               addressBook->contacts[index].email);


        char confirm;
        printf("Are you sure you want to delete this contact? (y/n): ");//Asking the user to confirm yes or no
        scanf(" %c", &confirm);  // space before %c to skip newline

        if (confirm == 'y' || confirm == 'Y') {
        // shift all contacts left
        for (int j = index; j < addressBook->contactCount - 1; j++) {
            addressBook->contacts[j] = addressBook->contacts[j + 1];
        }

        addressBook->contactCount--;   // reduce count

        printf("Contact deleted successfully!\n");
    } else {
            printf("❌ Deletion cancelled.\n");
        }
    } else {
        printf("⚠️ Contact not found!\n");
    }
}

// block function
/*Lets the user find a contact by name, phone, or email.
If found, moves that contact into the blocked list.(Blocks a contact and stores it in the blocked list.)
Removes it from the normal contact list.
Saves changes right away.*/
void blockContact(AddressBook *addressBook) {
    int choice, pos;
    char query[50];

    printf("\n--- Block Contact 🚫 ---\n");
    printf("1. Name\n2. Phone\n3. Email\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    printf("Enter value: ");
    scanf("%s", query);

    pos = findContactIndex(addressBook, query, choice);

    if (pos == -1) {
        printf("⚠️ Contact not found!\n");
        return;
    }

    // move to blocked
    addressBook->blocked[addressBook->blockedCount++] = addressBook->contacts[pos];

    // shift contacts left
    for (int i = pos; i < addressBook->contactCount - 1; i++) {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;

    printf("🚫 Contact blocked.\n");

    // ✅ Save changes immediately
    saveContactsToFile(addressBook);
}
// Show all blocked contacts
/*
This function is used to list the blocked contacts as they will not be diplayed in a common list.
First it checks if blocked contacts are there? if not then prints no blocked contact found.
If found prints them. */
void listBlockedContacts(AddressBook *addressBook) {
    if (addressBook->blockedCount == 0) {
        printf("\n🚫 No blocked contacts.\n");
        return;
    }

    printf("\n--- Blocked Contacts 🚫 ---\n");
    for (int i = 0; i < addressBook->blockedCount; i++) {
        printf("%d. Name: %s | Phone: %s | Email: %s\n",
               i + 1,
               addressBook->blocked[i].name,
               addressBook->blocked[i].phone,
               addressBook->blocked[i].email);
    }
}
/*
The unblockContact function allows a user to restore a contact that was previously blocked.
Checks if blocked contacts there?if no then prints no blocked contact to unblock.
Then search the contact to unblock if not found then returns -1 with message no contact found.
The function then searches through the blocked list, and if the name is found, it moves that contact back into the main contact list, updates its status to "Active," and shifts the remaining blocked contacts to fill the gap.
It confirms the successful unblocking of the contact and saves the updated contact list to the file immediately. */
void unblockContact(AddressBook *addressBook) {
    if (addressBook->blockedCount == 0) {
        printf("🚫 No blocked contacts to unblock!\n");
        return;
    }

    char name[50];
    printf("Enter the name of the contact to unblock: ");
    scanf("%s", name);

    int found = -1;

    // 🔍 Search in blocked list
    for (int i = 0; i < addressBook->blockedCount; i++) {
        if (strcmp(addressBook->blocked[i].name, name) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("❌ Contact not found in Blocked list!\n");
        return;
    }

    // ✅ Move from blocked[] → contacts[] and set status to Active
    addressBook->contacts[addressBook->contactCount] = addressBook->blocked[found];
    strcpy(addressBook->contacts[addressBook->contactCount].status, "Active");
    addressBook->contactCount++;

    // 🔄 Shift remaining blocked contacts left
    for (int i = found; i < addressBook->blockedCount - 1; i++) {
        addressBook->blocked[i] = addressBook->blocked[i + 1];
    }
    addressBook->blockedCount--;

    printf("✅ Contact '%s' unblocked successfully!\n", name);

     // ✅ Save changes immediately
    saveContactsToFile(addressBook);
}


