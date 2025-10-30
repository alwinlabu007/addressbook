#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>

struct Contact
{
    char name[50];
    char phone[20];
    char email[50];
};

struct AddressBook
{
    struct Contact contacts[100];
    int contactCount;
};

void createContact(struct AddressBook *addressBook);
void editContact(struct AddressBook *addressBook);
void deleteContact(struct AddressBook *addressBook);
void listContacts(struct AddressBook *addressBook);
void initialize(struct AddressBook *addressBook);
void saveContactsToFile(struct AddressBook *AddressBook);

int is_valid_mobile(struct AddressBook *addressBook, char temp_mobile[]);
int is_valid_email(struct AddressBook *addressBook,char temp_email[]);

int search_by_name(struct AddressBook* addressBook);
int search_by_phone(struct AddressBook* addressBook);
int search_by_email(struct AddressBook* addressBook);

void searchContact1(struct AddressBook * addressBook);
void search_by_name1(struct AddressBook *addressBook);

void editContact(struct AddressBook *addressBook);
void edit_field(struct AddressBook* addressBook,int index);
void edit_name(struct AddressBook* addressBook,int index);
void edit_phone(struct AddressBook* addressBook, int index);
void edit_Email(struct AddressBook* addressBook, int index);
void delete_field(struct AddressBook* addressBook, int index);
#endif
