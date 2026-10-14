#include <stdio.h>
#include "file.h"
// this is the file used to store the contact
#define FILENAME "contacts.txt"

// saves all contacts from the addressbook
void saveContactsToFile(AddressBook *addressBook) {
    FILE *ptr = fopen("contacts.txt","w");// it will use to opening file and its a write mode(w);

    if(ptr == NULL){//check whether the file opened sucessfully
        printf("Not opened\n");
        return;
    }
fprintf(ptr,"# %d\n",addressBook->contactCount);// it will uses to shows the contacts count i mean how many contacts are available
// loop through all contacts in the addressbook 
for(int i=0;i<addressBook->contactCount;i++){
    // each contact is stored on a seperate 
    fprintf(ptr, "%s,%s,%s\n",
        addressBook->contacts[i].name,
        addressBook->contacts[i].phone,
        addressBook->contacts[i].email
    );
}
// close the file after saving all contacts
fclose(ptr);
  printf("contacts saved successfully\n");
}
// loads previously saved contacts fromthe file
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt", "r");//it will helps the read data which is already existed file

    if(fp == NULL)//condition failure
    {
        // check the file doesnot exist,thre are no contacts load
        addressBook->contactCount = 0;
        return;
    }

    fscanf(fp, "# %d", &addressBook->contactCount);// it reads the user input and help store the data
    // loop through all contacts stored in the file
    for(int i = 0; i < addressBook->contactCount; i++)
    {

        fscanf(fp, " %49[^,],%19[^,],%49[^\n]",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
    // close the file after loading the contacts
    fclose(fp);

    printf("%d contacts loaded successfully\n",
           addressBook->contactCount);
}