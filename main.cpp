#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include "Car.h"

using namespace std;

/*
TEST CASES:

CASE 1:
Inputs: 1, 2, 3, 4, 5
Expected Result: No Inventory, $10000.00, Add car (Mustang, Black, 10000), Sell car (Mustang), No car to paint
Actual Result: No Inventory, $10000.00, Add car (Mustang, Black, 10000), Sell car (Mustang), No car to paint

CASE 2:
Inputs: 6, cars1.txt, 1, 3, 1, 8
Expected Result: add cars1.txt, lists cars in cars1.txt, add car, list cars (should have the one that was added at the end of the list), exit program
Actual Result: add cars1.txt, lists cars in cars1.txt, add car, list cars (should have the one that was added at the end of the list), exit program

CASE 3:
Inputs: 6, cars2.txt, 3 (Mustang, Blue, 3000), 5 (Mustang, Yellow), 1
Expected Result: add cars2.txt, add (Mustang, Blue, 3000), paint mustang yellow, list inventory (mustang should be yellow and worth 4000)
Actual Result: add cars2.txt, add (Mustang, Blue, 3000), paint mustang yellow, list inventory (mustang should be yellow and worth 4000)

*/

//Global Constants
const int NOT_FOUND = -1;

//This function displays all the cars in the dealership's inventory
void showInventory(vector<Car> allCars)
{
	if (allCars.size() == 0)
	{
		cout << "Inventory Empty" << endl << endl;
	}
	else {
		cout << "Inventory:" << endl << endl;
		for (int carIndex = 0; carIndex < allCars.size(); carIndex++)
		{
			cout << allCars[carIndex].toString() << endl;
		}
		cout << endl;
	}
}

//This functions searches through car inventory to find a match
int findCar(vector<Car> all_cars, string userCarChoice)
{
	int found;

	for (int carIndex = 0; carIndex < all_cars.size(); carIndex++)
	{
		if (userCarChoice == all_cars[carIndex].getName())
		{
			found = carIndex;
			return found;
		}
	}

	found = NOT_FOUND;
	return found;
}

//Displays the dealership's balance
void showBalance(vector<Car> allCars, double &balance)
{
	cout << "Balance: $" << fixed << setprecision(2) << balance << endl << endl;
}

//Adds car to inventory (as long as car isn't already in the inventory) and subtracts the cost from the balance
void buyCar(vector<Car> &allCars, double &balance)
{

	string name;
	string color;
	double price;

	cout << "Name: ";
	cin >> name;

	cout << "Color: ";
	cin >> color;

	cout << "Price: ";
	cin >> price;

	Car newCar(name, color, price);

	string userCarChoice = name;
	int found = findCar(allCars, userCarChoice);

	if (found != NOT_FOUND)
	{
		cout << "You already own this car!" << endl << endl;
	}
	else if (balance - price < 0 && found == NOT_FOUND)
	{
		cout << "You can't afford this car!" << endl << endl;
	}
	else
	{
		allCars.push_back(newCar);
		balance -= newCar.getPrice();
		cout << "Car purchased" << endl << endl;
	}
}

//Removes car from inventory (as long as car is in the inventory) and adds back the cost of the car to the balance
void sellCar(vector<Car> &allCars, double& balance)
{
	string carToSell;
	cout << "Car to sell: ";
	cin >> carToSell;

	string userCarChoice = carToSell;
	int found = findCar(allCars, userCarChoice);

	if (found != NOT_FOUND)
	{
		Car sellCar = allCars[found];
		balance += sellCar.getPrice();

		allCars.erase(allCars.begin() + found);

		cout << "Car sold" << endl << endl;
	}
	if (found == NOT_FOUND)
	{
		cout << "Car not owned" << endl << endl;
	}
}

//Changes the color of the car (as long as car is in the inventory) and add $1000 to the value of the car
void paintCar(vector<Car> &allCars, double &balance)
{
	string carToPaint;
	cout << "Car to paint: ";
	cin >> carToPaint;

	string userCarChoice = carToPaint;
	int found = findCar(allCars, userCarChoice);

	if (found != NOT_FOUND)
	{
		Car paintCar = allCars[found];

		string newColor;
		cout << "New paint color: ";
		cin >> newColor;

		paintCar.paint(newColor);
		allCars[found] = paintCar;
		cout << "Car painted " << newColor << endl << endl;
	}
	else
	{
		cout << "Car not owned" << endl << endl;
	}

}

//Loads file with cars into inventory of dealership
void loadFile(vector<Car> &allCars, double &balance)
{
	string fileName;
	double fileBalance;
	string name;
	string color;
	double price;

	ifstream fileToLoad;
	cout << "File name: ";
	cin >> fileName;
	cout << endl;
	fileToLoad.open(fileName.c_str());

	fileToLoad >> fileBalance;

	while (fileToLoad >> name)
	{
		fileToLoad >> color;
		fileToLoad >> price;
		Car new_car(name, color, price);
		allCars.push_back(new_car);
	}
	balance += fileBalance;
}

//Saves the curret inventory of the dealership
void saveFile(vector<Car> allCars, double balance)
{
	string name;
	string color;
	double price;
	string fileName;
	ofstream saveFile;
	cout << "File name: ";
	cin >> fileName;

	saveFile.open(fileName);

	saveFile << fixed << setprecision(2) << balance << "\n";

	for (int carIndex = 0; carIndex < allCars.size(); carIndex++)
	{
		name = allCars[carIndex].getName();
		color = allCars[carIndex].getColor();
		price = allCars[carIndex].getPrice();

		saveFile << name << " ";
		saveFile << color << " ";
		saveFile << price << "\n";
	}

	saveFile.close();
	cout << "File saved as " << fileName << endl << endl;
}

int main()
{
	const int EXIT_PROGRAM = 1;
	double balance = 10000;

	vector<Car> allCars;

	int runProgram = 0;
	while (runProgram == 0)
	{
		cout << "1 - Show Current Inventory" << endl;
		cout << "2 - Show Current Balance" << endl;
		cout << "3 - Buy a Car" << endl;
		cout << "4 - Sell a Car" << endl;
		cout << "5 - Paint a Car" << endl;
		cout << "6 - Load a File" << endl;
		cout << "7 - Save File" << endl;
		cout << "8 - Quit Program" << endl << endl;

		int input;
		cin >> input;

		if (input == 1)
		{
			showInventory(allCars);
		}
		else if (input == 2)
		{
			showBalance(allCars, balance);
		}
		else if (input == 3)
		{
			buyCar(allCars, balance);
		}
		else if (input == 4)
		{
			sellCar(allCars, balance);
		}
		else if (input == 5)
		{
			paintCar(allCars, balance);
		}
		else if (input == 6)
		{
			loadFile(allCars, balance);
		}
		else if (input == 7)
		{
			saveFile(allCars, balance);

		}
		else if (input == 8)
		{
			runProgram = EXIT_PROGRAM;
		}

	}

	cout << endl;
	system("pause");
	return 0;
}