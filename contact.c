#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"
//it is display all contacts stored in the addressbook
void listContacts(AddressBook *addressBook) 
{
    // helps to check any contacts available
   if(addressBook->contactCount == 0){
    printf("No contacts display.\n");
    return;
   } // its prints the heading for the contact list
   printf("\n%-20s %-15s %-30s\n","Name","Phone Number", "Gmail Id");
// its a seperater line
   printf("-----------------------------------------------------------------\n");
for(int i=0;i<addressBook->contactCount;i++){
//    // Loop from 0 to addressBook->contactCount-1;
    printf("%-20s %-15s %-30s\n",
        addressBook->contacts[i].name,
        addressBook->contacts[i].phone,
        addressBook->contacts[i].email);
}
}
// intialize the addressbook and loads the previously saved contacts
void initialize(AddressBook *addressBook) {
    //it intially set the contact count to zero
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
// it helps to save the all contacts to the file and exits the program
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
// this validates the name entered by the user
int validate_name(char *str)
{
    for(int i=0;str[i]!=0;i++)
    {
        if( ! ((str[i]>='a'&& str[i]<='z')|| 
        (str[i]>='A' && str[i]<='Z')||
         (str[i]==' ' )|| (str[i]=='.'))) // not valid
        {
            return 0; // invalid
        }
    }
    return 1; //valid
}
// validate the phone number
int validate_phone(char *str){
int i;
    int flag=0;
    // find the length of the phone number
    int len = strlen(str);
    // phone should contain only 10 characters
    if(len!=10){
        return 0;
    }
    // loop helps to check each and every character
    for(i=0;str[i]!=0;i++){
        if(!(str[i]>='0' && str[i]<='9')){
            return 0;
        }
    }
    return 1;
}
// validates the email address
int validate_email(char *str){
  int i;
  // help to find the length of the email
  int len = strlen(str);
  //reject an empty email
  if(len==0){
    return 0;
  }
  // this if condition email must start with alphabet only
    if(!((str[0] >= 'a' && str[0] <= 'z') ||
         (str[0] >= 'A' && str[0] <= 'Z')))
    {
        return 0;
    }
    // to find the position of '@' in the email
    char *at = strchr(str, '@');
    // if not present invalid email
    if(at == NULL)
    {
        return 0;
    }
    // Check whether domain is exactly gmail.com
    if(strcmp(at, "@gmail.com") != 0)
    {
        return 0;
    }
    // helps to check all characters
    for(int i = 0; i < at - str; i++)
    {
        if(!((str[i] >= 'a' && str[i] <= 'z') ||
             (str[i] >= 'A' && str[i] <= 'Z') ||
             (str[i] >= '0' && str[i] <= '9')))
        {
            return 0;
        }
    }

    return 1;//valid email
}
// to creates a new contact in the addressbook .
void createContact(AddressBook *addressBook)
{
    // arrays to store the input for temp
    char str1[30], str2[30], str3[30];
    int res;
// loop helps to keep asking until they gave valid name
    do
    {
        printf("Enter the name: ");
        scanf(" %29[^\n]", str1);

        res = validate_name(str1);// valid name entered

        if(!res)// not valid msg
            printf("Invalid name. Try again\n");

    } while(res == 0);
    // this loop helps to keep asking until they gave valid phone number
    do
    {
        printf("Enter the phone number: ");
        scanf(" %29[^\n]", str2);

        res = validate_phone(str2);// valid entered

        if(!res){//not valid msg
            printf("Invalid phone number. Try again\n");
    }else{// check whether the phone number is already presents are not
        for (int i=0;i<addressBook->contactCount;i++){
            // compare existing number by using strcmp();
            if(strcmp(addressBook->contacts[i].phone,str2)==0){
                printf("This phone number already exists.Try again\n");
                // if input as invalid
                res=0;
                break;
            }
        }
    } 
}
    while(res == 0);

// this loop helps until they gave valid email
    do
    {
        printf("Enter the Email address: ");
       scanf(" %29[^\n]", str3);

        res = validate_email(str3);// valid entered

        if(!res){// invalid error msg
            printf("Invalid Email address. Try again\n");
    }
    else{//check whether the email already presents or not
        for(int i=0;i<addressBook->contactCount;i++){
            // compare existing emailid by using strcmp
            if(strcmp(addressBook->contacts[i].email,str3)==0){
                printf("This email already exists.Try again\n");
                // input as invalid
                res=0;
                break;
            }
        }
    }
}
     while(res == 0);


    int ind = addressBook->contactCount;// it store new contact at the next available index

    strcpy(addressBook->contacts[ind].name, str1);//cpoy the entered  name
    strcpy(addressBook->contacts[ind].phone, str2);//copy the entered phone number
    strcpy(addressBook->contacts[ind].email, str3);// copy the entered emailid

    addressBook->contactCount++;//increase the addressbook contact count 

    printf("Contact added successfully\n");
}
// searches for a contact using the name 
    int search_by_name(AddressBook *addressBook)
{
    char name[30];
    int matchIndexes[MAX_CONTACTS];// array to strore maximum contacts
    int matchCount = 0;// contacts matched intially
    int choice;

    printf("Enter the name: ");
    scanf(" %29[^\n]", name);
// search through all contacts
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // compare entered name and stored name
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            matchIndexes[matchCount] = i;// matching contact it stores the index
            matchCount++;//increases the number of matches
        }
    }
    if (matchCount == 0)// if no matching contact
    {
        printf("Contact not found.\n");
        return -1;
    }
    // if exactly one contact matched 
    if (matchCount == 1)
    {
        int index = matchIndexes[0];
        // Display all contact details
        printf("\nName  : %s\n", addressBook->contacts[index].name);
        printf("Phone : %s\n", addressBook->contacts[index].phone);
        printf("Email : %s\n", addressBook->contacts[index].email);

        return index;// it returns the index 
    }
    // if multiple contacts found
    printf("\nMultiple contacts found:\n");
    for (int i = 0; i < matchCount; i++)
    {
        int index = matchIndexes[i];
// display all matching contacts
        printf("\n%d.\n", i + 1);
        printf("Name  : %s\n", addressBook->contacts[index].name);
        printf("Phone : %s\n", addressBook->contacts[index].phone);
        printf("Email : %s\n", addressBook->contacts[index].email);
    }
// select yhe contact by using index 
    printf("\nSelect the contact: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > matchCount)
    {
        printf("Invalid choice.\n");
        return -1;
    }

    return matchIndexes[choice - 1];// return the contact what user selected 
}
// searches contact by using phone number
int search_by_phone(AddressBook *addressBook)
{
    char phone[30];
    int found = 0;

    printf("Enter the phone number to search: ");
    scanf(" %29[^\n]", phone);
// search through all contacts
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        // compare the entered phone number with stored phone number
        if(strcmp(addressBook->contacts[i].phone, phone) == 0)
        {// display matching contacts
            printf("\nName  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);

            found = 1;
            return i;
        }
    }

    if(found == 0)// if not found
    {
        printf("Contact not found.\n");
        return -1;
    }
}
// searches by using emailid 
int search_by_email(AddressBook *addressBook)
{
    char email[30];
    int found = 0;

    printf("Enter the email address to search: ");
    scanf(" %29[^\n]", email);
// search through all contacts
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        //compare the entered emailid to stored email id 
        if(strcmp(addressBook->contacts[i].email, email) == 0)
        {
            // display the matched contact details
            printf("\nName  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);

            found = 1;
            return i;
        }
    }

    if(found == 0)// if not found
    {
        printf("Contact not found.\n");
        return -1;
    }
}
// searches the contacts through this methods
void searchContact(AddressBook *addressBook)
{
    int choice;

    printf("\nSearch Contact\n");
    printf("1. Search by name\n");
    printf("2. Search by phone\n");
    printf("3. Search by email\n");
    printf("Enter your choice: ");

    scanf("%d", &choice);
// selets the search function
    switch(choice)
    {
        case 1:
            search_by_name(addressBook);
            break;

        case 2:
            search_by_phone(addressBook);
            break;

        case 3:
            search_by_email(addressBook);
            break;

        default:
            printf("Invalid choice.\n");
            break;
    }
}
// searches for a contact and updates one of its fields
void editContact(AddressBook *addressBook)
{
    int searchChoice;
    int updateChoice;
    int ind = -1;

    printf("\nEdit Contact\n");
    printf("How do you want to search the contact?\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone\n");
    printf("3. Search by Email\n");

    printf("Enter your choice: ");
    scanf(" %d", &searchChoice);
// select the search function
    switch(searchChoice)
    {
        case 1:
            ind = search_by_name(addressBook);
            break;

        case 2:
            ind = search_by_phone(addressBook);
            break;

        case 3:
            ind = search_by_email(addressBook);
            break;

        default:
            printf("Invalid choice.\n");
            return;
    }
    // if no contact found
    if(ind == -1)
    {
        return;
    }
    // asking which field you want to edit 
    printf("\nWhich field do you want to update?\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");

    printf("Enter your choice: ");
    scanf(" %d", &updateChoice);
// select the filed update
    switch(updateChoice)
    {
        case 1:
        {
            char name[30];

            printf("Enter new name: ");
            scanf(" %29[^\n]", name);
            // entered vaild name

            if(validate_name(name))
            {
                strcpy(addressBook->contacts[ind].name, name);
                printf("Name updated successfully.\n");
            }
            else
            {
                printf("Invalid name.\n");
            }
            break;
        }

        case 2:
        {
            char phone[30];

            printf("Enter new phone number: ");
            scanf(" %29[^\n]", phone);

            if(validate_phone(phone))
            {
                strcpy(addressBook->contacts[ind].phone, phone);
                printf("Phone updated successfully.\n");
            }
            else
            {
                printf("Invalid phone number.\n");
            }
            break;
        }

        case 3:
        {
            char email[30];

            printf("Enter new email: ");
            scanf(" %29[^\n]", email);

            if(validate_email(email))
            {
                strcpy(addressBook->contacts[ind].email, email);
                printf("Email updated successfully.\n");
            }
            else
            {
                printf("Invalid email.\n");
            }
            break;
        }

        default:
            printf("Invalid choice.\n");
    }
}
// searches for a contact and delete it after confirmation
void deleteContact(AddressBook *addressBook)
{
	
    int searchchoise;
    int ind = -1;
     printf("\n delete Contact\n");
    printf("How do you want to search the contact?\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone\n");
    printf("3. Search by Email\n");
    scanf("%d",&searchchoise);
    // select the search function
    switch(searchchoise){
         case 1:
           ind= search_by_name(addressBook);
            break;
        case 2:
           ind = search_by_phone(addressBook);
            break;
        case 3:
            ind = search_by_email(addressBook);
            break;
        default:
        printf("Invalid choise.\n");
        break;
    }
    if(ind == -1){
        printf("cannot delete , contact not found\n");
        return;
    }
   char confirm;
   // ask user to confirm deletion
   printf("Are you sure you want to delete this contact (y/n)? ");
   scanf(" %c",&confirm);
   // cancle the deletion process if user doesnt enter y or Y
   if(confirm != 'y' && confirm != 'Y'){
    printf("deletion cancelled.\n");
    return;
   }
   // shift all contacts after the deleted contact one position left
   for(int i= ind;i<addressBook->contactCount-1;i++){
    addressBook->contacts[i] = addressBook->contacts[i+1];
   }
   // decrease the total number of contacts
   addressBook->contactCount--;
   printf("contact deleted successfully\n");
}
