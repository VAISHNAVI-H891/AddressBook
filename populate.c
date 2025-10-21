/*  
📂 populate.c  
This file is used to add some default contacts into the Address Book.  
These are important emergency numbers like Ambulance, Police, etc.  
When the program starts for the first time, these contacts will be added automatically.  
*/

#include "populate.h"
#include <string.h>


void populateAddressBook(AddressBook *addressBook) {
    strcpy(addressBook->contacts[0].name, "Ambulance");
    strcpy(addressBook->contacts[0].phone, "108");
    strcpy(addressBook->contacts[0].email, "hospital@gmail.com");

    strcpy(addressBook->contacts[1].name, "ChildHelpline");
    strcpy(addressBook->contacts[1].phone, "1098");
    strcpy(addressBook->contacts[1].email, "childhelp@gmail.com");

    strcpy(addressBook->contacts[2].name, "Police");
    strcpy(addressBook->contacts[2].phone, "100");
    strcpy(addressBook->contacts[2].email, "police@gmail.com");

    strcpy(addressBook->contacts[3].name, "Women");
    strcpy(addressBook->contacts[3].phone, "1091");
    strcpy(addressBook->contacts[3].email, "womenhelp@gmail.com");


     addressBook->contactCount=4;   
}