#include "HashFunction.h"
#include "HashFunctionDefines.h"

#include <Windows.h>
#include <iostream>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

HashFunction hashtable;

void DisplayRecordsPage();
void SearchRecordPage();
void CreateRecordPage();
void RemoveRecordPage();
void ExitPage();
void ErrorMessage();
void Pause();

// -------------------- MENU FUNCTIONS --------------------

// Main Menu
void MainMenu()
{
	system("cls");

	// Displays a menu
	SetConsoleTextAttribute(hConsole, LIGHTCYAN);
	std::cout << " === Phone Directory === " << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " This directory stores mobile numbers." << std::endl << std::endl;
	std::cout << "    View All Records    [1]" << std::endl;
	std::cout << "    Search Records      [2]" << std::endl;
	std::cout << "    Add Records         [3]" << std::endl;
	std::cout << "    Remove Records      [4]" << std::endl;

	SetConsoleTextAttribute(hConsole, RED);
	std::cout << "     EXIT               [5]" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);

	SetConsoleTextAttribute(hConsole, DARKGRAY);
	std::cout << " Select an option: ";
	SetConsoleTextAttribute(hConsole, WHITE);

	int option{};
	std::cin >> option;
	switch (option)
	{
		// Takes user to display page 
	case 1:
		DisplayRecordsPage();
		break;

		// Takes user to search page
	case 2:
		SearchRecordPage();
		break;

		// Takes user to create page
	case 3:
		CreateRecordPage();
		break;

		// Takes user to remove page
	case 4:
		RemoveRecordPage();
		break;

		// Exits the loop
	case 5:
		break;

		// If input is invalid, user is asked again
	default:
		ErrorMessage();
		MainMenu();
		break;
	}

	return;
}

// Display Records Page
void DisplayRecordsPage()
{
	system("cls");

	// Displays page message
	SetConsoleTextAttribute(hConsole, LIGHTCYAN);
	std::cout << " === Phone Directory === " << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " DISPLAY PAGE" << std::endl << std::endl;

	hashtable.DisplayRecords();
	Pause();

	MainMenu();
}

// Search Record Page
void SearchRecordPage()
{
	system("cls");

	// Displays page message
	SetConsoleTextAttribute(hConsole, LIGHTCYAN);
	std::cout << " === Phone Directory === " << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " SEARCH PAGE" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, LIGHTRED);
	std::cout << " * Mobile numbers MUST be 10 numbers long and begin with a '0'. *" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);

	// Asks for input
	SetConsoleTextAttribute(hConsole, DARKGRAY);
	std::cout << " Enter the record's phone number: ";
	SetConsoleTextAttribute(hConsole, WHITE);

	std::string tel;
	std::cin >> tel;

	std::cout << std::endl;

	hashtable.Search(tel);
	
	Pause();

	MainMenu();
}

// Create Record Page
void CreateRecordPage()
{
	system("cls");

	// Displays page message
	SetConsoleTextAttribute(hConsole, LIGHTCYAN);
	std::cout << " === Phone Directory === " << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " CREATE PAGE" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, LIGHTRED);
	std::cout << " * Mobile numbers MUST be 10 numbers long and begin with a '0'. *" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);

	// Asks for input
	SetConsoleTextAttribute(hConsole, DARKGRAY);
	std::cout << " Enter the new record's name: ";
	SetConsoleTextAttribute(hConsole, WHITE);

	std::string name;
	std::cin >> name;

	SetConsoleTextAttribute(hConsole, DARKGRAY);
	std::cout << " Enter the new record's phone number: ";
	SetConsoleTextAttribute(hConsole, WHITE);

	std::string tel;
	std::cin >> tel;

	std::cout << std::endl;

	hashtable.Insert(name, tel);

	Pause();

	MainMenu();
}

// Remove Record Page
void RemoveRecordPage()
{
	system("cls");

	// Displays page message
	SetConsoleTextAttribute(hConsole, LIGHTCYAN);
	std::cout << " === Phone Directory === " << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " REMOVE PAGE" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, LIGHTRED);
	std::cout << " * Mobile numbers MUST be 10 numbers long and begin with a '0'. *" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);

	// Asks for input
	SetConsoleTextAttribute(hConsole, DARKGRAY);
	std::cout << " Enter the record's name to remove: ";
	SetConsoleTextAttribute(hConsole, WHITE);

	std::string name;
	std::cin >> name;

	SetConsoleTextAttribute(hConsole, DARKGRAY);
	std::cout << " Enter the record's phone number to remove: ";
	SetConsoleTextAttribute(hConsole, WHITE);

	std::string tel;
	std::cin >> tel;

	std::cout << std::endl;

	hashtable.Delete(name, tel);

	Pause();

	MainMenu();
}

// Exit Page
void ExitPage()
{
	std::cout << std::endl << " Press 'Enter' exit the program.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	return;
}

// Error Message
void ErrorMessage()
{
	SetConsoleTextAttribute(hConsole, RED);
	std::cout << " Invalid input." << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " Press 'Enter to try again." << std::endl;
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	return;
}

// Asks for user input to continue
void Pause()
{
	std::cout << std::endl << " Press 'Enter' to go back to the main menu.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	return;
}

// Main Function
int main()
{
	bool directoryRunning = true;

	// ------ Directory Loop ------ 
	while (directoryRunning)
	{
		MainMenu();

		directoryRunning = false;
	}

	// Exits the program
	ExitPage();
	return 0;
}