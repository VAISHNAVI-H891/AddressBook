/*  
📂 main.c  
This is the starting point of the Address Book project.  
It shows a menu to:  
1. Add a contact  
2. Search a contact  
3. Edit a contact  
4. Delete a contact  
5. List all contacts (with sorting)  
6. Save contacts to file  
7.Block Contact
8.List block contact
9. Exit program  
 This project acts a Digital phone Addressbook where we can perform the above operations
 */

#include <stdio.h>
#include "contact.h"
#include "file.h"

int main() {
    int choice;
    AddressBook addressBook;

    initialize(&addressBook);   // ✅  // load contacts (from file or default)

    do {
        
        printf("\n--------------Address Book Menu:-----------------\n");
        printf("1. 👤Create contact\n");
        printf("2. 🔍Search contact\n");
        printf("3. ✏️Edit contact\n");
        printf("4. 🗑️ Delete contact\n");
        printf("5. 📋List all contacts\n");
        printf("6. 💾for save Save contacts\n");
        printf("7. 🔒Block Contact\n");
        printf("8. 🚫 List blocked contacts\n");
        printf("9. 🔓Unblock contact\n");
        printf("10. 🚪Exit\n");
        choice = getChoice();
        
        switch (choice) {
            case 1: createContact(&addressBook); break;// add new contact
            case 2: searchContact(&addressBook); break;// search existing
            case 3: editContact(&addressBook); break;// edit details
            case 4: deleteContact(&addressBook); break;// delete contact
            case 5: {
                int sortCriteria;
                printf("Enter sort choice (1. Name 2. Phone 3. Email): ");
                scanf("%d", &sortCriteria);       
                listContacts(&addressBook, sortCriteria);// show sorted list
                break;
            }
            case 6: saveContactsToFile(&addressBook); break;// save to file
            case 7: blockContact(&addressBook); break; //Block Contacts
            case 8: listBlockedContacts(&addressBook); break;//List the BlockeContacts
            case 9: unblockContact(&addressBook); break;
            case 10: saveAndExit(&addressBook); break;// save + exit
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 10);// loop until exit

    return 0;
}
