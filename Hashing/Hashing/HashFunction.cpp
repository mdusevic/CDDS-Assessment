#include "HashFunction.h"
#include "HashFunctionDefines.h"

#include <iostream>

HashFunction::HashFunction()
{
	table = new std::list<Record>[maxRecords];
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

HashFunction::~HashFunction()
{

}

// -------------------- OTHER FUNCTIONS --------------------

// Creates the hash value via the telephone number
int HashFunction::Hashing(std::string tel)
{
	int digit_tel = std::stoi(tel);
	return (digit_tel % maxRecords);
}

// Checks if list is empty, returns a bool value
bool HashFunction::IsListEmpty()
{
	if (table->empty())
	{
		return true;
	}

	return false;
}

// Checks if name is valid, returns a bool value
bool HashFunction::IsNameValid(std::string name)
{
	if (name.length() > NAME_SIZE)
	{
		return false;
	}

	for (int i = 0; i < name.length(); i++)
	{
		if (isdigit(name[i] == true))
		{
			return false;
		}
	}

	return true;
}

// Checks if phone number is valid, returns a bool value
bool HashFunction::IsPhoneNumberValid(std::string tel)
{
	if (tel.length() != TEL_SIZE)
	{
		return false;
	}

	if (tel[0] != '0')
	{
		return false;
	}

	for (int i = 0; i < tel.length(); i++)
	{
		if (isdigit(tel[i] == false))
		{
			return false;
		}
	}

	return true;
}

// -------------------- INSERT FUNCTIONS --------------------

// Inserts a new record
void HashFunction::Insert()
{
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

	if (IsNameValid(name))
	{
		if (IsPhoneNumberValid(tel))
		{
			Record newRecord;
			newRecord.name = name;
			newRecord.tel = tel;

			int index = Hashing(tel);
			table[index].push_back(newRecord);

			SetConsoleTextAttribute(hConsole, LIGHTGREEN);
			std::cout << "  SUCCESS " << std::endl;
			SetConsoleTextAttribute(hConsole, WHITE);
			std::cout << "  " << newRecord.name << ", " << newRecord.tel << std::endl;
			return;
		}

		SetConsoleTextAttribute(hConsole, RED);
		std::cout << " Input invalid, not a valid phone number" << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
		return;
	}

	SetConsoleTextAttribute(hConsole, RED);
	std::cout << " Input invalid, not a valid name" << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	return;
}

// -------------------- DELETE FUNCTIONS --------------------

// Deletes the desired record
void HashFunction::Delete()
{
	if (!IsListEmpty())
	{
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

		int index = Hashing(tel);

		for (auto const& i : table[index])
		{
			if (name == i.name)
			{
				SetConsoleTextAttribute(hConsole, LIGHTRED);
				std::cout << "  DELETING ... " << i.name << ", " << i.tel << std::endl;
				SetConsoleTextAttribute(hConsole, WHITE);

				table[index].clear();
				return;
			}
		}

		SetConsoleTextAttribute(hConsole, RED);
		std::cout << " Input invalid, record does not exist." << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
		return;
	}

	SetConsoleTextAttribute(hConsole, RED);
	std::cout << " Input invalid, list is empty." << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	return;
}

// -------------------- SEARCH FUNCTIONS --------------------

// Searchs table for desired record
void HashFunction::Search()
{
	if (!IsListEmpty())
	{
		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Enter the record's phone number: ";
		SetConsoleTextAttribute(hConsole, WHITE);

		std::string tel;
		std::cin >> tel;

		std::cout << std::endl;

		if (IsPhoneNumberValid(tel))
		{
			int index = Hashing(tel);

			for (auto const& i : table[index])
			{
				SetConsoleTextAttribute(hConsole, LIGHTGREEN);
				std::cout << "  FOUND: ";
				SetConsoleTextAttribute(hConsole, WHITE);
				std::cout << i.name << ", " << i.tel << std::endl;
				return;
			}

			SetConsoleTextAttribute(hConsole, LIGHTRED);
			std::cout << "  NOT FOUND " << std::endl;
			SetConsoleTextAttribute(hConsole, WHITE);
			return;
		}

		SetConsoleTextAttribute(hConsole, RED);
		std::cout << " Input invalid, not a phone number" << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
		return;
	}

	SetConsoleTextAttribute(hConsole, RED);
	std::cout << " Input invalid, list is empty." << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	return;
}

// -------------------- PRINT FUNCTIONS --------------------

// Prints contents of table
void HashFunction::DisplayRecords()
{
	if (!IsListEmpty())
	{
		for (int i = 0; i < maxRecords; i++)
		{
			if (i < 10)
			{
				SetConsoleTextAttribute(hConsole, YELLOW);
				std::cout << " 0" << i;
				SetConsoleTextAttribute(hConsole, WHITE);
			}

			else
			{
				SetConsoleTextAttribute(hConsole, YELLOW);
				std::cout << " " << i;
				SetConsoleTextAttribute(hConsole, WHITE);
			}

			for (Record record : table[i])
			{
				SetConsoleTextAttribute(hConsole, LIGHTCYAN);
				std::cout << " ---> ";
				SetConsoleTextAttribute(hConsole, WHITE);
				std::cout << record.name << ", " << record.tel;
			}

			std::cout << std::endl;
		}

		return;
	}

	SetConsoleTextAttribute(hConsole, RED);
	std::cout << " Input invalid, list is empty." << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	return;
}

// -------------------- MENU FUNCTIONS --------------------

// Main Menu
void HashFunction::MainMenu()
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
void HashFunction::DisplayRecordsPage()
{
	system("cls");

	// Displays page message
	SetConsoleTextAttribute(hConsole, LIGHTCYAN);
	std::cout << " === Phone Directory === " << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " DISPLAY PAGE" << std::endl << std::endl;

	DisplayRecords();
	Pause();

	MainMenu();
}

// Search Record Page
void HashFunction::SearchRecordPage()
{
	system("cls");

	// Displays page message
	SetConsoleTextAttribute(hConsole, LIGHTCYAN);
	std::cout << " === Phone Directory === " << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " SEARCH PAGE" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, LIGHTRED);
	std::cout << " * Mobile numbers MUST be 12 numbers long and begin with a '0'. *" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);

	Search();
	Pause();

	MainMenu();
}

// Create Record Page
void HashFunction::CreateRecordPage()
{
	system("cls");

	// Displays page message
	SetConsoleTextAttribute(hConsole, LIGHTCYAN);
	std::cout << " === Phone Directory === " << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " CREATE PAGE" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, LIGHTRED);
	std::cout << " * Mobile numbers MUST be 12 numbers long and begin with a '0'. *" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);

	Insert();
	Pause();

	MainMenu();
}

// Remove Record Page
void HashFunction::RemoveRecordPage()
{
	system("cls");

	// Displays page message
	SetConsoleTextAttribute(hConsole, LIGHTCYAN);
	std::cout << " === Phone Directory === " << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " REMOVE PAGE" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, LIGHTRED);
	std::cout << " * Mobile numbers MUST be 12 numbers long and begin with a '0'. *" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);

	Delete();
	Pause();

	MainMenu();
}

// Exit Page
void HashFunction::ExitPage()
{
	std::cout << std::endl << " Press 'Enter' exit the program.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	return;
}

// Error Message
void HashFunction::ErrorMessage()
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
void HashFunction::Pause()
{
	std::cout << std::endl << " Press 'Enter' to go back to the main menu.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	return;
}