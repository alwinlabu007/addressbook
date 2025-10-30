#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

//Function to list all contacts
void listContacts(struct AddressBook *addressBook) 
{
    printf("\n\t\t  <<<<<<  Contact Details  >>>>>>\n\n");
    /* Print table header */
    printf(" --------------------------------------------------------------------------\n");
    printf("|  %-5s   %-15s   %-15s   %-27s |\n", "No.", "Name", "Phone", "Email");
    printf(" --------------------------------------------------------------------------\n");

    /* Print all contacts */
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("|  %-5d   %-15s   %-15s   %-27s |\n", i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf(" --------------------------------------------------------------------------\n");
}


void initialize(struct AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(struct AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

//Function for creating contact
void createContact(struct AddressBook *addressBook)
{   
    //Name	collecting in temp variable			    
    char temp_name[50];     		
    printf("Enter the name: ");	
    scanf(" %[^\n]",temp_name);                

    //Mobile collecting in temp variable
    char temp_phone[20];
    do
    {
        printf("Enter the mobile number: ");
        scanf(" %[^\n]",temp_phone);

    }while(is_valid_mobile(addressBook,temp_phone) == 0); //Mobile number validation

    //Email collecting in temp variable
    char temp_email[50];
    do
    {
	printf("Enter the email address: ");
	scanf(" %[^\n]",temp_email);
    }while(is_valid_email(addressBook,temp_email) == 0);  //email validation

    strcpy(addressBook -> contacts[addressBook -> contactCount].name,temp_name);
    strcpy(addressBook -> contacts[addressBook -> contactCount].phone,temp_phone);
    strcpy(addressBook -> contacts[addressBook -> contactCount].email,temp_email);

	printf("\nContact created successfully.\n");
    addressBook -> contactCount++;

}

// Mobile number checking function
int is_valid_mobile(struct AddressBook *addressBook,char temp_phone[])
{

    //To check if mobile number has 10 digits
    if(strlen(temp_phone) != 10)
    {
        printf("Lenth of mobile number should be 10\n\n");
        return 0;
    }

    //To check if mobile has only digits
    int i = 0;
    while(temp_phone[i] != '\0')
    {
        if(isdigit(temp_phone[i]) == 0)
        {
            printf("Mobile number should only contain digits\n\n");
            return 0;
        }
        i++;
    }

    //To check if number is unique
    for(int i = 0; i < addressBook -> contactCount; i++)
    {
        if(strcmp(addressBook -> contacts[i].phone, temp_phone) == 0)
        {
            printf("Mobile number already exists\n\n");
            return 0;
        }
    }
    return 1;
}

//Email checking function
int is_valid_email(struct AddressBook *addressBook,char temp_email[])
{

	//To check if mail contains @ and.com 
	if(strchr(temp_email,'@') == NULL || strstr(temp_email,".com") == NULL
		|| temp_email[0] == '@' || temp_email[strlen(temp_email) - 1] == '@')
	{
		printf("Email should contain @ , .com and a character before and after @\n\n");
		return 0;
	}

	//To check if mail is lowercase only
	int i = 0;
	while(temp_email[i] != '\0')
	{
		if(isupper(temp_email[i]))
		{
			printf("Email should contain lowercase letters only\n\n");
			return 0;
		}
		i++;
	}

	//To check if .com comes last
	int l = strlen(temp_email);	
	if(strcmp(temp_email + l - 4, ".com") != 0)
	{
		printf(".com should come last\n\n");
		return 0;
	}
	
	//To check if email already exists
	for(int i = 0; i < addressBook -> contactCount; i++)
	{
		if(strcmp(addressBook -> contacts[i].email,temp_email) == 0)
		{
			printf("Email already exists\n\n");
			return 0;
		}
	}

	return 1;
}

//Function for searching the contact
void searchContact1(struct AddressBook * addressBook)	 
{
	int opt;
	do
	{
	printf("\n\t      <<<  Search Menu  >>>\n\n");
	printf("\t\t1.Search by name\n");
	printf("\t\t2.Search by phone\n");
	printf("\t\t3.Search by email\n");
	printf("\t\t4.Exit\n\n");
	printf("Enter your choice: ");
	
	if(scanf(" %d",&opt) != 1)
	{
		printf("\nInvalid choice!\nPlease enter a number between 1 to 4\n\n");  // scanf returns number of successful inputs
		while(getchar() != '\n');												//Clear invalid input from buffer
		continue;	
	}
	switch(opt)
	{
		case 1: search_by_name1(addressBook);
		        break;

		case 2: search_by_phone(addressBook);
		        break;

		case 3: search_by_email(addressBook);
		        break;

		case 4: printf("Exiting search Menu...\n");
				break;

		default: printf("\nInvalid choice!\nPlease enter a number between 1 to 4\n\n");
	}
	} while (opt != 4);

}

void search_by_name1(struct AddressBook *addressBook) //Seperate search function without index return
{
	char search_name[50];
	printf("Enter the name: ");
	scanf(" %[^\n]",search_name);
	int count = 0;
	for(int i = 0; i < addressBook -> contactCount; i++)
	{
		if(strcmp(addressBook -> contacts[i].name, search_name) == 0)
		{
			printf("\t\t----------------------------------------------\n");
			printf("\n");
			printf("\t\tContact %d \n",count + 1);
			printf("\t\tName   : %s\n",addressBook -> contacts[i].name);
			printf("\t\tPhone  : %s\n",addressBook -> contacts[i].phone);
			printf("\t\tEmail  : %s\n\n",addressBook -> contacts[i].email);
			count++;
			
		}
	}
	printf("\t\t----------------------------------------------\n");
	if(count == 0)
	{
		printf("\n\t\tContact not found!\n");
		printf("\n\t\t----------------------------------------------\n");
	}	
}


//Name search function with index return
int search_by_name(struct AddressBook* addressBook)
{
	char search_name[50];
	printf("Enter the name: ");
	scanf(" %[^\n]",search_name);
	int found_index[addressBook -> contactCount];
	int found_contact_count = 0;

	
	for(int i = 0; i < addressBook -> contactCount; i++)
	{
		if(strcmp(addressBook -> contacts[i].name, search_name) == 0)
		{
			printf("\t\t----------------------------------------------\n");
			printf("\n");
			printf("\t\tContact %d\n",found_contact_count + 1);
			printf("\t\tName   : %s\n",addressBook -> contacts[i].name);
			printf("\t\tPhone  : %s\n",addressBook -> contacts[i].phone);
			printf("\t\tEmail  : %s\n\n",addressBook -> contacts[i].email);
			found_index[found_contact_count++] = i;
		}
	}

	//if no contact is present 
	if(found_contact_count == 0)
	{
		printf("\n\t\t----------------------------------------------\n");
		printf("\n\t\tContact not found!\n");
		printf("\n\t\t----------------------------------------------\n");
		return -1;
	}

	//if only one contact is present
	if(found_contact_count == 1)
	{
		printf("\t\t----------------------------------------------\n");
		return(found_index[0]);
	}

	//If multiple contacts are present,ask user to choose from many
	int choice;
	do
	{
		printf("\t\t----------------------------------------------\n");
		printf("\nMultiple contacts with same name found!\nSelect a contact: ");
		scanf("%d",&choice);

		if (choice < 1 || choice > found_contact_count)
		{
			printf("\t\t----------------------------------------------\n");	
			printf("\n\t\tInvalid choice!\n\t\tChoose from 1 to %d\n\n",found_contact_count);
			
		}
		else
		{
			return found_index[choice - 1];
		}
	}while(choice < 1 || choice > found_contact_count);
	return -1;
}

//Function for checking  phone number
int search_by_phone(struct AddressBook* addressBook)
{
	int index = 0; 
	int count = 0;
	char search_phone[20];
	printf("Enter the phone number: ");
	scanf(" %[^\n]",search_phone);

	int flag = 0;

	for(int i = 0; i < addressBook -> contactCount; i++)
	{
		if(strcmp(addressBook -> contacts[i].phone, search_phone) == 0)
		{
			printf("\t\t----------------------------------------------\n");
			flag = 1;
			printf("\n");
			printf("\t\tContact %d \n",count + 1);
			printf("\t\tName   : %s\n",addressBook -> contacts[i].name);
			printf("\t\tPhone  : %s\n",addressBook -> contacts[i].phone);
			printf("\t\tEmail  : %s\n",addressBook -> contacts[i].email);
			printf("\n\t\t----------------------------------------------\n");
			index = i;
			count++;
			return index;
			
		}		
	}
	if(flag == 0)
	{
		printf("\t\t----------------------------------------------\n");
		printf("\n\t\tContact not found!\n");
		printf("\n\t\t----------------------------------------------\n");
		return -1;
	}
	return -1; //last check
}

//Function for searching using email
int search_by_email(struct AddressBook* addressBook)
{
	int index = 0;
	int count = 0;
	char search_email[50];
	printf("Enter the email address: ");
	scanf(" %[^\n]",search_email);

	int flag = 0;

	for(int i = 0; i < addressBook -> contactCount; i++)
	{
		if(strcmp(addressBook -> contacts[i].email, search_email) == 0)
		{
			printf("\t\t----------------------------------------------\n");
			flag = 1;
			printf("\n");
			printf("\t\tContact %d \n",count + 1);
			printf("\t\tName   : %s\n",addressBook -> contacts[i].name);
			printf("\t\tPhone  : %s\n",addressBook -> contacts[i].phone);
			printf("\t\tEmail  : %s\n",addressBook -> contacts[i].email);
			printf("\n\t\t----------------------------------------------\n");
			index = i;
			count++;
			return index;
					
		}
	}
	if(flag == 0)
	{
		printf("\t\t----------------------------------------------\n");
		printf("\n\t\tContact not found!\n");
		printf("\n\t\t----------------------------------------------\n");
		return -1;
	}
	return -1; //last check
}

//Function for editing contact
void editContact(struct AddressBook *addressBook)
{
    //Define the logic for Editcontact
	int choice;
	do
	{
		int index = -1;
		printf("\n\t\t <<< Edit Menu >>>\n\n");
		printf("\t\tSelect from options\n");
		printf("\t\t1. Search by name\n");
		printf("\t\t2. Search by phone\n");
		printf("\t\t3. Search by email\n");
		printf("\t\t4. Exit\n\n");
		printf("Enter your choice: ");
		
		scanf("%d",&choice);
		getchar();

		switch(choice)
		{
				case 1:
					index = search_by_name(addressBook);
					break;

				case 2:
					index = search_by_phone(addressBook);
					break;

				case 3:
					index = search_by_email(addressBook);
					break;

				case 4:
					printf("Exiting the Edit menu...\n");
					return;

				default:
					printf("\nInvalid choice!\nPlease enter a number between 1 to 4\n");
		}
		if(index != -1)
		{
			edit_field(addressBook, index);
		}
	} while (choice != 4);
}

void edit_field(struct AddressBook* addressBook,int index)		//Function for selecting which field to be edited
{
	int opt;
	do
	{
	printf("\n\t        <<< Edit field >>>\n\n");
	printf("\t\tSelect from options\n");
	printf("\t\t1. Name\n");
	printf("\t\t2. Phone\n");
	printf("\t\t3. Email\n");
	printf("\t\t4. Exit\n\n");
	printf("Enter your choice:");
	scanf("%d",&opt);
	getchar();

	switch(opt)
	{
		case 1:
			edit_name(addressBook, index);
			break;

		case 2: 
			edit_phone(addressBook, index);
			break;

		case 3: 
			edit_Email(addressBook, index);
			break;

		case 4:
			printf("Exiting...\n");
			return;

		default:
			printf("\nInvalid choice!\nPlease enter a number between 1 to 4\n");
	}
	} while (opt != 4);
}

	//Function for editing name
	void edit_name(struct AddressBook* addressBook, int index)
	{

		printf("Enter the new name: ");
		char new_name[50];
		scanf(" %[^\n]",new_name);

		strcpy(addressBook -> contacts[index].name, new_name);

		printf("\t\t----------------------------------------------\n");
		printf("\n\t\tUpdated contact is\n");
		printf("\t\tName   : %s\n",addressBook -> contacts[index].name);
		printf("\t\tPhone  : %s\n",addressBook -> contacts[index].phone);
		printf("\t\tEmail  : %s\n",addressBook -> contacts[index].email);
		printf("\n\t\t----------------------------------------------\n");
		
	}

	//Function for editing phone number
	void edit_phone(struct AddressBook* addressBook, int index)
	{	
		char new_num[20];
		do
		{
			printf("Enter the new phone number: ");
			scanf(" %[^\n]",new_num);

		}while(is_valid_mobile(addressBook,new_num) == 0);

		strcpy(addressBook -> contacts[index].phone, new_num);

		printf("\t\t----------------------------------------------\n");
		printf("\n\t\tUpdated contact is\n");
		printf("\t\tName   : %s\n",addressBook -> contacts[index].name);
		printf("\t\tPhone  : %s\n",addressBook -> contacts[index].phone);
		printf("\t\tEmail  : %s\n",addressBook -> contacts[index].email);
		printf("\n\t\t----------------------------------------------\n");
		return;

	}

	//Function for editing email
	void edit_Email(struct AddressBook* addressBook, int index)
	{	
		char new_email[50];
		do
		{
			printf("Enter the new email: ");
			scanf(" %[^\n]",new_email);

		}while(is_valid_email(addressBook,new_email) == 0);

		strcpy(addressBook -> contacts[index].email, new_email);

		printf("\t\t----------------------------------------------\n");
		printf("\n\t\tUpdated contact is\n");
		printf("\t\tName   : %s\n",addressBook -> contacts[index].name);
		printf("\t\tPhone  : %s\n",addressBook -> contacts[index].phone);
		printf("\t\tEmail  : %s\n",addressBook -> contacts[index].email);
		printf("\n\t\t----------------------------------------------\n");
		return;

	}

//Function for deleting contact
void deleteContact(struct AddressBook *addressBook)
{
    //Calls the same functions used in edit function
	int choice;
	do
	{
		int index = -1;
		printf("\n\t        <<< Delete Menu >>>\n");
		printf("\n\t\tSelect from options\n");
		printf("\t\t1. Search by name\n");
		printf("\t\t2. Search by phone\n");
		printf("\t\t3. Search by email\n");
		printf("\t\t4. Exit\n");
		printf("Enter your choice: \n");
		
		scanf("%d",&choice);

		switch(choice)
		{
				case 1:
					index = search_by_name(addressBook);
					break;

				case 2:
					index = search_by_phone(addressBook);
					break;

				case 3:
					index = search_by_email(addressBook);
					break;

				case 4:
					printf("Exiting...\n");
					return;

				default:
					printf("Invalid choice\n");
					return;
		}
		if(index != -1)
		{
			int opt;
			printf("\nDo you want to delete[1 -> Yes] [0 -> No]\n");
			scanf(" %d",&opt);
			if(opt)
			{
				delete_field(addressBook, index);
			}
			else
			{
				printf("Going back to Delete Menu...\n\n"); 
			}
		}

	} while (choice != 4);
}
	
//Function for selecting field
void delete_field(struct AddressBook* addressBook, int index)
{
	for(int i = index; i < addressBook -> contactCount - 1; i++)
	{
		addressBook -> contacts[i] = addressBook -> contacts[i + 1];
	}
	addressBook -> contactCount--;
	printf("\nContact deleted successfully...\n\n");
}
