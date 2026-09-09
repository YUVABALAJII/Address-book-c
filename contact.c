#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

// Sorts the saved contacts by name and prints them in a readable table.
void listContacts(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0) 
    { 
        printf("No contacts to show.\n\n"); 
        return; 
    }
    for (int i=0;i<addressBook->contactCount-1;i++)
    {
        for (int j=0;j<addressBook->contactCount-i -1;j++)
        {
            if (strcmp(addressBook->contacts[j].name,addressBook->contacts[j + 1].name) >0) 
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
    int emailWidth = 20;
    for (int i=0;i<addressBook->contactCount;i++) 
    {
        int length = (int)strlen(addressBook->contacts[i].email);
        if (length > emailWidth) 
        {
            emailWidth = length;
        }
    }
    int tableWidth = emailWidth+53;
    int titleWidth = tableWidth-2;
    const char *title = "ADDRESS BOOK - Contact Directory";
    int titleLeft = (titleWidth - (int)strlen(title)) / 2;
    int titleRight = titleWidth - (int)strlen(title) - titleLeft;
    printf("\n+");
    for (int i = 0; i < tableWidth - 2; i++) 
    {
        putchar('-');
    }
    printf("+\n|%*s%s%*s|\n+", titleLeft, "", title, titleRight, "");
    for (int i = 0; i < tableWidth - 2; i++) 
    {
        putchar('-');
    }
    printf("+\n| %-9s%-18s%-22s%-*s |\n+", "S.No.", "Name", "Phone Number", emailWidth, "Email");
    for (int i = 0; i < tableWidth - 2; i++) 
    {
        putchar('-');
    }
    printf("+\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-9d%-18s%-22s%-*s |\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, emailWidth, addressBook->contacts[i].email);
    }
    printf("+");
    for (int i = 0; i < tableWidth - 2; i++) 
    {
        putchar('-');
    }
    printf("+\n");
}

// Clears the address book and loads any contacts saved on disk.
void initialize(AddressBook *addressBook) 
{ 
    addressBook->contactCount = 0; loadContactsFromFile(addressBook); 
}

// Saves the current contacts before closing the program.
void saveAndExit(AddressBook *addressBook) 
{ 
    saveContactsToFile(addressBook);
    exit(EXIT_SUCCESS); 
}

// Checks whether a name contains only the characters accepted by the address book.
int validate_name(char *str)
{
    for (int i = 0; str[i] != 0; i++)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || str[i] == ' ' || str[i] == '.')) return 0;
    }
    return 1;
}

// Confirms that a phone number contains exactly ten digits.
int validate_phone(char *str)
{
    if (strlen(str) != 10) 
    {
        return -1;
    }
    for (int i = 0; str[i] != 0; i++) 
    {
        if (str[i] < '0' || str[i] > '9') 
        {
            return 0;
        }
    }
    return 1;
}

// Checks whether an email contains only the characters supported by this program.
int validate_email(char *str)
{
    for (int i = 0; str[i] != 0; i++)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '@' || str[i] == '.')) 
        {
            return 0;
        }
    }
    return 1;
}

// Looks for an existing contact that shares any unique field with the new values.
int hasDuplicateContact(AddressBook *addressBook, const char *name, const char *phone, const char *email, int excludedIndex)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i != excludedIndex && (strcmp(addressBook->contacts[i].name, name) == 0 || strcmp(addressBook->contacts[i].phone, phone) == 0 || strcmp(addressBook->contacts[i].email, email) == 0)) 
        {
            return 1;
        }
    }
    return 0;
}

// Collects and validates the details for a new contact before storing it.
void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS) 
    { 
        printf("Address Book is full! Cannot add more contacts.\n"); 
        return; 
    }
    char name[50], phone[20], email[50];
    do 
    { 
        printf("Enter the name :"); scanf(" %49[^\n]", name); 
    } while (!validate_name(name));
    do 
    { 
        printf("Enter the phone :"); scanf(" %19[^\n]", phone); 
    } while (validate_phone(phone) != 1);
    do 
    { 
        printf("Enter the email :"); scanf(" %49[^\n]", email); 
    } while (!validate_email(email));
    if (hasDuplicateContact(addressBook, name, phone, email, -1)) 
    { 
        printf("Contact already exists. Name, phone number, and email must be unique.\n");
        return; 
    }
    int index = addressBook->contactCount++;
    strcpy(addressBook->contacts[index].name, name);
    strcpy(addressBook->contacts[index].phone, phone);
    strcpy(addressBook->contacts[index].email, email);
}

// Finds the first contact whose selected field exactly matches the search text.
static int findContact(AddressBook *addressBook, int choice, const char *search)
{
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        const char *value = choice == 1 ? addressBook->contacts[i].name : choice == 2 ? addressBook->contacts[i].phone : addressBook->contacts[i].email;
        if (strcmp(value, search) == 0) 
        {
            return i;
        }
    }
    return -1;
}

// Searches contacts by name, phone number, or email and displays the match.
void searchContact(AddressBook *addressBook)
{
    int choice; char search[50];
    printf("Search by:\n1. Name\n2. Phone\n3. Email\nEnter choice: "); 
    scanf("%d", &choice);
    if (choice < 1 || choice > 3) 
    { 
        printf("Invalid choice.\n"); 
        return; 
    }
    printf("Enter value to search: "); scanf(" %49[^\n]", search);
    int index = findContact(addressBook, choice, search);
    if (index == -1) printf("Contact Not Found.\n");
    else printf("Found -> %s %s %s\n", addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
}

// Replaces an existing contact after validating its new details.
void editContact(AddressBook *addressBook)
{
    int choice; char search[50];
    printf("Edit by:\n1. Name\n2. Phone\n3. Email\nEnter choice: "); 
    scanf("%d", &choice);
    if (choice < 1 || choice > 3) 
    { 
        printf("Invalid choice.\n"); 
        return; 
    }
    printf("Enter value to edit: "); 
    scanf(" %49[^\n]", search);
    int index = findContact(addressBook, choice, search);
    if (index == -1) 
    { 
        printf("Contact Not Found.\n"); 
        return; 
    }
    char name[50], phone[20], email[50];
    printf("Enter The New Name: "); 
    scanf(" %49[^\n]", name);
    printf("Enter The New Phone Number: "); 
    scanf(" %19[^\n]", phone);
    printf("Enter The New Email: "); 
    scanf(" %49[^\n]", email);
    if (!validate_name(name) || validate_phone(phone) != 1 || !validate_email(email) || hasDuplicateContact(addressBook, name, phone, email, index)) 
    { 
        printf("Invalid or duplicate contact. Name, phone number, and email must be unique.\n"); 
        return; 
    }
    strcpy(addressBook->contacts[index].name, name); 
    strcpy(addressBook->contacts[index].phone, phone); 
    strcpy(addressBook->contacts[index].email, email);
    printf("Contact Updated.\n");
}

// Removes the selected contact and shifts later contacts into its place.
void deleteContact(AddressBook *addressBook)
{
    int choice; char search[50];
    printf("Delete by:\n1. Name\n2. Phone\n3. Email\nEnter choice: "); 
    scanf("%d", &choice);
    if (choice < 1 || choice > 3) 
    { 
        printf("Invalid choice.\n"); 
        return; 
    }
    printf("Enter value to delete: "); 
    scanf(" %49[^\n]", search);
    int index = findContact(addressBook, choice, search);
    if (index == -1) 
    { 
        printf("Contact Not Found.\n"); 
        return; 
    }
    for (int i = index; i < addressBook->contactCount - 1; i++) 
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--; printf("Contact Deleted!\n");
}
