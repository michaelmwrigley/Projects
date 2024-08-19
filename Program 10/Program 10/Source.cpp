//program 10 (larger program)
//gas purchase list
//add name, date, and a description
//spring 2021


#define _CRT_SECURE_NO_WARNINGS //for Visual Studio compiler
#pragma warning(disable:6031) //ignore scanf warnings for Visual Studio compiler
#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define SIZE 150 //size of the list
#define SIZE2 20//size of character arrays

typedef struct {
	//ADD fields here
	char gasType[SIZE2];
	char lastName[SIZE2];

	int	itemNumber;
	int	numGallons;

	double	pricePerGallon;
	double	totalCost;
}gasPurchase;

//function prototypes
void Greeting();

void RunMenu(char* selectionPtr);
//input: the user's selection (input/output parameter)
//display the program options and get the users selection (A, P, S, or Q)
//use an input/output parameter for the selection

void ProcessSelection(char selection, gasPurchase list[], int* count);
//input: the user's selection by copy (input parameter)
//input/output: the gasPurchase list and count 
//display a message that the selection has been entered
//call the required function for each selection (A, P, or S)

void AddTransaction(gasPurchase list[], int* count);
//input/output: the gasPurchase list and count 
//add a gas purchase transaction to the list and 
//add 1 to the "value at" count only if the itemNumber is valid 

int SetPrice(gasPurchase list[], int count);
//input/output: the gasPurchase list
//input count by copy (input parameter)
//checks to see if the itemNumber is valid
//sets the pricePerGallon and gasType
//returns a 1 if the itemNumber is valid and returns 0 if the itemNumber is not valid

void CalculateTotal(gasPurchase list[], int count);
//input/output: the gasPurchase list
//input count by copy (input parameter)
//and Calculates the totalCost based on the itemNumber

void PrintList(gasPurchase list[], int count);
//input/output: the gasPurchase list
//input count by copy (input parameter)
//prints the contents of the list onto the screen 


void PrintE85_purchases(gasPurchase list[], int count);
//input/output: the gasPurchase list
//input count by copy (input parameter)
//Searches the array and prints the name and 
//totalCost of any E85 purchases(list and count)
int main()
{
	//greet the user
	Greeting();

	//declare the gas purchase list
	gasPurchase list[SIZE];

	//declare and initialize count to 0
	int count = 0;

	//declare a character for the menu choice
	char choice;

	//run the menu choices
	//initialization
	RunMenu(&choice);


	//begin the while or while loop
	while (choice != 'q') //test
	{
		//process the selection
		ProcessSelection(choice, list, &count);

		//be sure to update the while loop (call run menu function to get the selection)
		//update
		RunMenu(&choice);
	}

	//say goodbye to the user
	return 0;
}


//function definitions

void Greeting()
//Greets the user
{
	printf("Welcome to the gas purchase list program\n");
	printf("\nWhen you enter a transaction, you will enter the customer's last name, the gas type, item number(1 through 5), and number of gallons\n");
	printf("\n1. Regular 2.35 per gallon\n");
	printf("\n2. Midgrade 2.65 per gallon\n");
	printf("\n3. Premium 2.99 per gallon\n");
	printf("\n4. Diesel 3.08 per gallon\n");
	printf("\n5. E85 2.09 per gallon\n");
}

void RunMenu(char* selectionPtr)
//input: the user's selection (input/output parameter)
//display the program options and get the users selection (A, P, S, or Q)
//use an input/output parameter for the selection
{
	printf("\n------------------------------------------------------------------------------------\n");
	printf("What would you like to do?\n");
	printf("\n Enter 'A' to add a gas purchase entry\n");
	printf("\n Enter 'P' to print the list onto the screen\n");
	printf("\n Enter 'S' to print the last name and total cost of any E85 purchase\n");
	printf("\n Enter 'Q' to quit\n");
	printf("\nEnter your selection: \n");
	scanf(" %c", selectionPtr);
	*selectionPtr = tolower(*selectionPtr);
}

void ProcessSelection(char selection, gasPurchase list[], int* countPtr)
//input: the user's selection by copy (input parameter)
//input/output: the gasPurchase list and count 
//display a message that the selection has been entered
//call the required function for each selection (A, P, or S)
{
	if (selection == 'a')
	{
		printf("\n----------------------------------\n");
		printf("You selected %c\n", selection);

		//ask and get the last name
		printf("\nEnter the customer last name: ");
		scanf(" %s", list[*countPtr].lastName);

		//call the Add Transaction function
		AddTransaction(list, countPtr);

		//keep track of how manyitems are in the list
		printf("\nThere are now %d gas purchases in the list", *countPtr);

	}
	//add the other options
	else if (selection == 'p')
	{
		printf("\n----------------------------------\n");
		printf("You selected %c\n", selection);
		PrintList(list, *countPtr);
	}

	else if (selection == 's')
	{
		printf("\n----------------------------------\n");
		printf("You selected %c\n", selection);
		PrintE85_purchases(list, *countPtr);
	}
	else printf("That is not an option\n");
}


void AddTransaction(gasPurchase list[], int* countPtr)
//input/output: the gasPurchase list and count 
//add a gas purchase transaction to the list and 
//add 1 to the "value at" count only if the itemNumber is valid 
{

	int validNumber = 1; // do not know if the user will enter a valid item number

	//list the item numbers and gas types
	printf("\n1. Regular 2.35 per gallon\n");
	printf("\n2. Midgrade 2.65 per gallon\n");
	printf("\n3. Premium 2.99 per gallon\n");
	printf("\n4. Diesel 3.08 per gallon\n");
	printf("\n5. E85 2.09 per gallon\n");

	//ask and get the item number
	printf("\nPlease enter the item number:\n");
	scanf("%d", &list[*countPtr].itemNumber);

	//ask and get the number of gallons
	printf("\nPlease enter the number of gallons:\n");
	scanf("%d", &list[*countPtr].numGallons);

	//call the set Price function
	validNumber = SetPrice(list, *countPtr);


	if (validNumber == 1)
	{
		//calculate the total (call the function)
		CalculateTotal(list, *countPtr);
		*countPtr = *countPtr + 1;
		printf("\nThe gas purchase transaction has been added to the list\n");

	}
	else// not a valid item number
	{
		printf("\nYou did not enter a valid item number, the gas purchase transaction will not be added to the list\n");
	}

}



int SetPrice(gasPurchase list[], int count)
//input/output: the gasPurchase list
//input count by copy (input parameter)
//checks to see if the itemNumber is valid
//sets the pricePerGallon and gasType
//returns a 1 if the itemNumber is valid and returns 0 if the itemNumber is not valid
{
	int returnValue = 1; // do not know if the user will enter a valid item number

	if (list[count].itemNumber == 1)
	{
		list[count].pricePerGallon = 2.35;
		strcpy(list[count].gasType, "Regular");
	}
	//add item numbers 2 through 5
	else if (list[count].itemNumber == 2)
	{
		list[count].pricePerGallon = 2.65;
		strcpy(list[count].gasType, "Midgrade");
	}
	else if (list[count].itemNumber == 3)
	{
		list[count].pricePerGallon = 2.99;
		strcpy(list[count].gasType, "Premium");
	}
	else if (list[count].itemNumber == 4)
	{
		list[count].pricePerGallon = 3.08;
		strcpy(list[count].gasType, "Disel");
	}
	else if (list[count].itemNumber == 5)
	{
		list[count].pricePerGallon = 2.09;
		strcpy(list[count].gasType, "E85");
	}
	else
	{
		printf("\nnot recognized\n");
		returnValue = 0; //the user did not enter a valid item number
	}
	//return a 1 or a 0
	return returnValue;
}


void CalculateTotal(gasPurchase list[], int count)
//input/output: the gasPurchase list
//input count by copy (input parameter)
//and Calculates the totalCost based on the itemNumber
{
	//calculate the total
	list[count].totalCost = list[count].numGallons * list[count].pricePerGallon;
}


void PrintList(gasPurchase list[], int count)
//input/output: the gasPurchase list
//input count by copy (input parameter)
//prints the contents of the list onto the screen 
{
	//int i;
	int i;
	printf("\n-----------------------------------------------------\n");
	if (count == 0)
	{
		printf("\nThe list is empty!\n");
	}
	//use a loop to print the list
	for (i = 0; i < count; i++)
		
	{
		printf("\n Customer last name : %s", list[i].lastName);
		printf("\nGas Type: %s", list[i].gasType);
		printf("\nNumber of gallons : %d", list[i].numGallons);
		printf("\nPrice per Gallon : %.2f", list[i].pricePerGallon);
		printf("\nTotal for the transaction : $%.2f", list[i].totalCost);

	}
}





void PrintE85_purchases(gasPurchase list[], int count)
//input/output: the gasPurchase list
//input count by copy (input parameter)
//Searches the array and prints the name and 
//totalCost of any E85 purchases(list and count)
{
	int i;
	printf("\n-----------------------------------------------------\n");
	if (count == 0)
	{
		printf("\nThe list is empty!\n");
	}
	//use a loop to search the list
	for (i = 0; i < count; i++)
	{
		if (strcmp(list[i].gasType, "E85") == 0)
		{
			//print the customer name and total cost
				printf("\nCustomer last name : %s", list[i].lastName);
				printf("\nTotal for transaction :%.2f", list[i].totalCost);
		}
	}

}




