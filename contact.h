#ifndef CONTACT_H
#define CONTACT_H

// ------------------- Structures -------------------

typedef struct {
    char name[50];
    char phone[15];
    char email[50];
    char status[10];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;

    Contact blocked[100];
    int blockedCount;
} AddressBook;

// ------------------- Validation -------------------
int getValidName(const char *name);
int getValidPhone(char *phone);
int isValidEmail(char *email);
int isDuplicate(AddressBook *addressBook, const char *name, const char *phone, const char *email);

// ------------------- Core Operations -------------------
int getChoice();
void clearInputBuffer();
void initialize(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
int findContactIndex(AddressBook *addressBook, char *query, int choice);
void blockContact(AddressBook *addressBook);
void listBlockedContacts(AddressBook *addressBook);
void unblockContact(AddressBook *addressBook);
// ------------------- Search Helpers -------------------
void searchByName(AddressBook *addressBook, char *query);
void searchByPhone(AddressBook *addressBook, char *query);
void searchByEmail(AddressBook *addressBook, char *query);

// ------------------- File Handling -------------------
void saveContacts(AddressBook *addressBook, const char *filename);
void loadContacts(AddressBook *addressBook, const char *filename);
void saveAndExit(AddressBook *addressBook);

#endif // CONTACT_H

