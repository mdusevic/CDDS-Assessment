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
	int count{};

	for (int i = 0; i < maxRecords; i++)
	{
		for (Record record : table[i])
		{
			count++;
		}
	}

	if (count > 0)
	{
		return false;
	}

	return true;
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

// Checks if phone number already exists, returns a bool value
bool HashFunction::ExistingPhoneNumber(std::string tel)
{
	// If the telephone number already exists
	int count{};

	for (int i = 0; i < maxRecords; i++)
	{
		for (Record record : table[i])
		{
			if (record.tel == tel)
			{
				count++;
			}
		}
	}

	if (count > 0)
	{
		return false;
	}

	return true;
}

// -------------------- INSERT FUNCTIONS --------------------

// Inserts a new record
void HashFunction::Insert(std::string newName, std::string newTel)
{
	// Validates name
	if (IsNameValid(newName))
	{
		// Validates phone number
		if (IsPhoneNumberValid(newTel) || !ExistingPhoneNumber(newTel))
		{
			Record newRecord;
			newRecord.name = newName;
			newRecord.tel = newTel;

			int index = Hashing(newTel);
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
void HashFunction::Delete(std::string oldName, std::string oldTel)
{
	// If list is not empty
	if (!IsListEmpty())
	{
		// Validates name
		if (IsNameValid(oldName))
		{
			// Validates phone number
			if (IsPhoneNumberValid(oldTel))
			{
				int index = Hashing(oldTel);

				for (auto const& i : table[index])
				{
					if (oldName == i.name)
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
			std::cout << " Input invalid, not a valid phone number" << std::endl;
			SetConsoleTextAttribute(hConsole, WHITE);
			return;
		}

		SetConsoleTextAttribute(hConsole, RED);
		std::cout << " Input invalid, not a valid name" << std::endl;
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
void HashFunction::Search(std::string tel)
{
	// If list is not empty
	if (!IsListEmpty())
	{
		// Validates phone number
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
			// This formats the index numbers to display two digits - '00'
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