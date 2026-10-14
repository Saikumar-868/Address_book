#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;//structure what are the variables we used that helps to store

typedef struct {
    Contact contacts[MAX_CONTACTS];// it will takes user maximum input upto 100
    int contactCount; 
} AddressBook;
// these are the functons we used in the contact.c 
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);

void saveContactsToFile(AddressBook *AddressBook);// it will helps to write all in contacts.txt
void loadContactsFromFile(AddressBook *addressBook);// it helpful to read the user input from contacts.txt
// these are the validation checking functions
int validate_name(char *str);
int validate_phone(char *str);
int validate_email(char *str);
// these are the functions for search contact 
int search_by_name(AddressBook *addressBook);
int search_by_phone(AddressBook *addressBook);
int search_by_email(AddressBook *addressBook);

#endif
