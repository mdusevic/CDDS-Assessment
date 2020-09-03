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

	// Other Functions
	int Hashing(std::string tel);
	bool IsListEmpty();
	bool IsNameValid(std::string name);
	bool IsPhoneNumberValid(std::string tel);
	bool ExistingPhoneNumber(std::string tel);
	
	// Insert Functions
	void Insert(std::string newName, std::string newTel);

	// Delete Functions
	void Delete(std::string oldName, std::string oldTel);

	// Search Functions
	void Search(std::string tel);

	// Print Functions
	void DisplayRecords();

protected:
private:
	// Sets the size of the hash table
	int maxRecords = HASHTABLE_SIZE;

	// Hash Table
	std::list<Record>* table;
};

