/*
  CS3321 Final Project
  Programmers: Yvan, Cuong, Noah, Damian*/


#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>

using namespace std;

const int ITEM_QUANTITY = 5;
const int ITEM_SELECTION = 5;

struct item_data {
	string name;
	float cost;
	int quantityLeft;
};

int showChoices(item_data[]);
float calculateExpenses(item_data[]);
void processSelection(int, item_data[]);

int main()
{

	item_data itemList[ITEM_SELECTION] =
	{
		{"Reebok Shoes",250,ITEM_QUANTITY},
		{"Nike Jacket",150.54,ITEM_QUANTITY},
		{"Balenciaga Purse",3000,ITEM_QUANTITY},
		{"Gucci Belt",350.50,ITEM_QUANTITY},
		{"Rayban Shades",450,ITEM_QUANTITY}
	};

	int user_choice;
	int itemIndex;

	cout << fixed << setprecision(2);
	cout << "Please select items to purchase" << endl;
	user_choice = showChoices(itemList);

	while (user_choice != ITEM_SELECTION + 1)
	{
		processSelection(user_choice, itemList);
		user_choice = showChoices(itemList);
	}

	float earnings = calculateExpenses(itemList);
	cout << "Amount Spent: $" << earnings << endl; // earnings is the final price of the program, how much the total cost is

}

int showChoices(item_data list[]) {
	int choice;
	cout << endl;
	for (int i = 0; i < ITEM_SELECTION; i++)
	{
		cout << i + 1 << ". " << list[i].name << endl;
	}
	cout << ITEM_SELECTION + 1 << ". Quit the program\n\n";
	cout << "ENTER YOUR CHOICE: ";
	cin >> choice;

	while (choice < 1 || choice > ITEM_SELECTION + 1)
	{
		cout << "Please senter a value between 1 and "
			<< ITEM_SELECTION << ": ";
		cin >> choice;
	}
	return choice;
}

void processSelection(int selection, item_data list[]) {
	int itemIndex = selection - 1;

	if (list[itemIndex].quantityLeft == 0) {
		cout << "That choice is sold out." << endl;
	}
	else {
		cout << "The cost is: $" << list[itemIndex].cost << endl;
		list[itemIndex].quantityLeft--;
	}
}

float calculateExpenses(item_data list[]) { // we need to pass the customer id to this function when login gets put in
	float result = 0.0;
	int customerID = 01; //set to 0 for testing purposes, we would pass this as a n number from login
	string filename,cID,final_reciept,final_price; // filename and final reciept ( product), and final price ( for output file)
	cID = to_string(customerID); // sets the customer id to a string to be used in filename generation
	filename = "Reciept_"+cID+".cvs"; // sets filename to customerid and as a cvs
	ofstream myfile(filename); // opens file
	myfile << "sep=," << endl;
	myfile << "CustomerID, ,Product, , Final Price, ,Card Number, ,Security Code\n";
	//************************************************* this is for yvan's work
	for (int i = 0; i < ITEM_SELECTION; i++) {
		result = result + list[i].cost * (ITEM_QUANTITY - list[i].quantityLeft);
	}
	//***************************************************
	for (int z = 0; z < ITEM_SELECTION; z++) //set int to z such that it wont interfere with above for loop
	{
		int temp = 0;
		do
		{
			temp = list[z].quantityLeft; // this sets temp to how much inventory of z is left
			if (temp != ITEM_QUANTITY)
			{
				
				do {

					final_reciept += " " + list[z].name;
					temp++;
				} while (temp != ITEM_QUANTITY); // this do while will loop until 
			}
		} while (temp < ITEM_QUANTITY); //do while runs until temp = ITEM_QUANTITY, this is done so that we dont effect the actual inventory, just work backwards with a temp int
		temp = 0;
	}
	long long int cn, sc; //cn= card number, sc= security code for payments
	cout << "Please enter your payment information." << endl;
	cout << "Card Number: ";
	cin >> cn;
	cout << "Security Code: ";
	cin >> sc;
	final_price = to_string(result); // sets the final price to result
	myfile << customerID << ", ," << final_reciept << ", ," << final_price << ", ," << cn << ", ," << sc << "\n"; // sends everything to our output file
	myfile.close(); // closes output file
	return result;
}