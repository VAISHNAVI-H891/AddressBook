#ifndef FILE_H
#define FILE_H

#include "contact.h"   // so AddressBook is known here

// Function declarations
void saveContactsToFile(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);

#endif
