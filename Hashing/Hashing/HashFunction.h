#pragma once

#include "HashFunctionDefines.h"

#include <Windows.h>
#include <list>
#include <string>

// Record class
class Record
{
public:
	std::string name;
	std::string tel;
};

// Hash Function class
class HashFunction
{
public:
	HashFunction();
	~HashFunction();

	// Console Handle
	HANDLE hConsole;

	// Menu Functions
	void MainMenu();
	void DisplayRecordsPage();
	void SearchRecordPage();
	void CreateRecordPage();
	void RemoveRecordPage();
	void ExitPage();
	void ErrorMessage();
	void Pause();

protected:
	// Other Functions
	int Hashing(std::string tel);
	bool IsListEmpty();
	bool IsNameValid(std::string name);
	bool IsPhoneNumberValid(std::string tel);
	
	// Insert Functions
	void Insert();

	// Delete Functions
	void Delete();

	// Search Functions
	void Search();

	// Print Functions
	void DisplayRecords();

private:
	// Sets the size of the hash table
	int maxRecords = HASHTABLE_SIZE;

	// Hash Table
	std::list<Record>* table;
};

