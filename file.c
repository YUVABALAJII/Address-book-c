#include <stdio.h>
#include<string.h>
#include "file.h"

// Writes every contact to the text file so the address book persists between runs.
void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp=fopen("contacts.txt","w");
    if(fp==NULL)
    {
        printf("Error Opening File For Saving.\n");
        return;
    } 
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fp,"%s|%s|%s\n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fp);
}

// Reads valid, non-duplicate contact records from the text file into memory.
void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp=fopen("contacts.txt","r");
    if(fp==NULL)
    {
        printf("Error Opening File.\n");
        return;
    }
    char line[150];
    int i = 0;
    while (fgets(line, sizeof(line), fp) != NULL && i < MAX_CONTACTS)
    {
        Contact contact;
        if (sscanf(line, "%[^\n|]|%[^\n|]|%[^\n]", contact.name, contact.phone, contact.email) == 3 && !hasDuplicateContact(addressBook, contact.name, contact.phone, contact.email, -1))
        {
            addressBook->contacts[i] = contact;
            i++;
        }
    }
    addressBook->contactCount = i;

    fclose(fp);

    
}
