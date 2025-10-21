#include <stdio.h>
#include <string.h>
#include "file.h"

/*
Open "contacts.csv" in read mode.
If file not found → return.
Reset contactCount and blockedCount to 0.
Skip the CSV header line.
Read each line from the file.
Extract name, phone, email, status using sscanf.
If status == "Active" → store in contacts list.
If status == "Blocked" → store in blocked list.
Sort Active contacts alphabetically by name.
Sort Blocked contacts alphabetically by name and close the file.*/
void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp = fopen("contacts.csv", "r");// Open contacts.csv for reading
    if (!fp) {
        return; // Exit if file does not exist
    }

    addressBook->contactCount = 0; // Reset active contacts count
    addressBook->blockedCount = 0;// Reset blocked contacts count

    char line[200];
    fgets(line, sizeof(line), fp); // skip header

    while (fgets(line, sizeof(line), fp)) // Read each contact line
     {
        char name[50], phone[20], email[50], status[20];
        if (sscanf(line, "%49[^,],%19[^,],%49[^,],%19s",
                   name, phone, email, status) == 4) {

            if (strcmp(status, "Active") == 0)// If status is Active
             {
                strcpy(addressBook->contacts[addressBook->contactCount].name, name);
                strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
                strcpy(addressBook->contacts[addressBook->contactCount].email, email);
                addressBook->contactCount++;// Increment active count
            } else if (strcmp(status, "Blocked") == 0)// If status is Blocked
             {
                strcpy(addressBook->blocked[addressBook->blockedCount].name, name);
                strcpy(addressBook->blocked[addressBook->blockedCount].phone, phone);
                strcpy(addressBook->blocked[addressBook->blockedCount].email, email);
                addressBook->blockedCount++;// Increment blocked count
            }
        }
    }

    fclose(fp); // Close file after reading

    // ✅ Sort only Active contacts alphabetically
    for (int i = 0; i < addressBook->contactCount - 1; i++) {
        for (int j = i + 1; j < addressBook->contactCount; j++) {
            if (strcmp(addressBook->contacts[i].name, addressBook->contacts[j].name) > 0) {
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }

    // ✅ Sort only Blocked contacts alphabetically
    for (int i = 0; i < addressBook->blockedCount - 1; i++) {
        for (int j = i + 1; j < addressBook->blockedCount; j++) {
            if (strcmp(addressBook->blocked[i].name, addressBook->blocked[j].name) > 0) {
                Contact temp = addressBook->blocked[i];
                addressBook->blocked[i] = addressBook->blocked[j];
                addressBook->blocked[j] = temp;
            }
        }
    }
}
/*Open "contacts.csv" in write mode.
If file cannot be opened → show error and return.
Write the CSV header (Name,Phone,Email,Status).
Sort Active contacts alphabetically by name.
Sort Blocked contacts alphabetically by name.
Loop through each Active contact.
Write Active contact details to file with status "Active".
Loop through each Blocked contact.
Write Blocked contact details to file with status "Blocked".
Close the file and show success message.*/
void saveContactsToFile(AddressBook *addressBook) {
    FILE *file = fopen("contacts.csv", "w");// Open file in write mode
    if (!file) {
        printf("❌ Error saving contacts to file!\n"); // Error if file not created
        return;
    }

    // Write header
    fprintf(file, "Name,Phone,Email,Status\n");// Write CSV header

    // ✅ Sort Active contacts alphabetically
    for (int i = 0; i < addressBook->contactCount - 1; i++) {
        for (int j = i + 1; j < addressBook->contactCount; j++) {
            if (strcmp(addressBook->contacts[i].name, addressBook->contacts[j].name) > 0) {
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }

    // ✅ Sort Blocked contacts alphabetically
    for (int i = 0; i < addressBook->blockedCount - 1; i++) {
        for (int j = i + 1; j < addressBook->blockedCount; j++) {
            if (strcmp(addressBook->blocked[i].name, addressBook->blocked[j].name) > 0) {
                Contact temp = addressBook->blocked[i];
                addressBook->blocked[i] = addressBook->blocked[j];
                addressBook->blocked[j] = temp;
            }
        }
    }

    // ✅ Save Active contacts
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s,%s,%s,Active\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    // ✅ Save Blocked contacts
    for (int i = 0; i < addressBook->blockedCount; i++) {
        fprintf(file, "%s,%s,%s,Blocked\n",
                addressBook->blocked[i].name,
                addressBook->blocked[i].phone,
                addressBook->blocked[i].email);
    }

    fclose(file); // Close the file
    printf("💾 Contacts saved successfully!\n"); // Confirmation message
}

