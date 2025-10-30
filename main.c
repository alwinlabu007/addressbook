/*
Alwin Labu
10-10-25
AddressBook

The AddressBook project is that allows users to efficiently manage contact information. It is C based. 

    It provides the following core functionalities:
        1. Create a new contact with details such as name, phone, and email.
        2. Search for existing contacts by name, phone number, or email.
        3. Edit the details of an existing contact.
        4. Delete a contact from the list.
        5. Display (list) all stored contacts.
        6. Save contacts to a file before exiting, ensuring data persistence.

Structures,Functions,Pointers,Loops concepts,Switch cases, various operators and built in functions are used to create this project.
*/


#include "contact.h"

int main() 
{
    int choice;

    struct AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do 
    {
	printf("\n\t     ✧ ✧  Address Book Menu  ✧ ✧\n");
	printf("\n\t\t1. Create contact\n");
	printf("\t\t2. Search contact\n");
	printf("\t\t3. Edit contact\n");
	printf("\t\t4. Delete contact\n");
	printf("\t\t5. List all contacts\n");
	printf("\t\t6. Exit\n\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);
	getchar();

	switch (choice) 
	{
	    case 1:
		createContact(&addressBook);
		break;
	    case 2:
		searchContact1(&addressBook);
		break;
	    case 3:
		editContact(&addressBook);
		break;
	    case 4:
		deleteContact(&addressBook);
		break;
	    case 5:
		listContacts(&addressBook);
		break;
	    case 6:
		printf("Saving and Exiting...\n");
		saveContactsToFile(&addressBook);
		break;
	    default:
		printf("Invalid choice. Please try again.\n\n");
	}
    } while (choice != 6);

    return 0;
}
