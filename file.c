#include <stdio.h>
#include "file.h"

void saveContactsToFile(struct AddressBook *addressBook) 
{
       FILE* fp = fopen("contacts.csv", "w");
       if(fp == NULL)
       {
            printf("File is not opened\n");
            return;
       }
       fprintf(fp, "#%d\n", addressBook -> contactCount); 

       for(int i = 0; i < addressBook -> contactCount; i++)
       {
            fprintf(fp, "%s,%s,%s\n", addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook-> contacts[i].email);
       }
       fclose(fp);
}

void loadContactsFromFile(struct AddressBook *addressBook) 
{
    FILE* fp = fopen("contacts.csv", "r");
    if(fp == NULL)
    {
        printf("File is not available\n");
        return;
    }
    fscanf(fp,"#%d",&addressBook -> contactCount);
    for(int i = 0; i < addressBook -> contactCount; i++)
    {
        fscanf(fp," %[^,],%[^,],%[^\n]\n",addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
    }
    fclose(fp);
}