#include "HashFunction.h"
#include <iostream>

bool directoryRunning = true;

// ----------- Main Menu -----------
void MainMenu()
{
	system("cls");

	// ------ Main Menu ------
	std::cout << " -- Phone Book -- " << std::endl;
	std::cout << " This directory stores people's phonenumbers." << std::endl << std::endl;
	std::cout << "    View All Records  [1]" << std::endl;
	std::cout << "    Search Records    [2]" << std::endl;
	std::cout << "    Add Records       [3]" << std::endl;
	std::cout << "    Remove Records    [4]" << std::endl;

	std::cout << "    EXIT              [5]" << std::endl << std::endl;

	std::cout << " Select an option: ";

	// Asks for user input
	int menuOption{};
	std::cin >> menuOption;

	switch (menuOption)
	{
	// Takes user to a menu to view records
	case 1:
		// ViewAllMenu();
		break;

	// Takes user to a menu to search for records
	case 2:
		// SearchMenu();
		break;

	// Takes user to menu to add records
	case 3:
		// CreateMenu();
		break;

	// Takes user to menu to remove records
	case 4:
		// RemoveMenu();
		break;

	// Allows user to exit program
	case 5:
		directoryRunning = false;
		break;

	// Menu is repeated if input is invalid
	default:
		std::cout << " Invalid input." << std::endl;

		std::cout << " Press 'Enter' to try again." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin.get();
		break;
	}
}

int main(int argc, char* argv[])
{
	// ------ HashTable Loop ------ 
	while (directoryRunning)
	{
		MainMenu();
	}

	// Exits the program
	std::cout << std::endl << " Press 'Enter' to exit.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	return 0;
}