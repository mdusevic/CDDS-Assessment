#include "LinkedList.h"
#include "Colours.h"
#include <Windows.h>
#include <iostream>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

LinkedList linkedList;

void DisplayMenu();
void SearchNodeMenu();
void CreateNodeMenu();
void RemoveNodeMenu();
void ExitMenu();
void ErrorMessage();
void Pause();

// -------------------- MENU FUNCTIONS --------------------

// Main Menu
void MainMenu()
{
	system("cls");

	// Displays a menu
	SetConsoleTextAttribute(hConsole, LIGHTCYAN);
	std::cout << " === Double Linked List === " << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " This is a linked list that contains numbers." << std::endl << std::endl;
	std::cout << "    Display Nodes        [1]" << std::endl;
	std::cout << "    Search Nodes         [2]" << std::endl;
	std::cout << "    Create Nodes         [3]" << std::endl;
	std::cout << "    Remove Nodes         [4]" << std::endl;
	SetConsoleTextAttribute(hConsole, RED);
	std::cout << "     EXIT                [5]" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);

	SetConsoleTextAttribute(hConsole, DARKGRAY);
	std::cout << " Select an option: ";
	SetConsoleTextAttribute(hConsole, WHITE);

	int option{};
	std::cin >> option;
	switch (option)
	{
		// Takes user to display menu 
	case 1:
		DisplayMenu();
		break;

		// Takes user to search menu
	case 2:
		SearchNodeMenu();
		break;

		// Takes user to create menu
	case 3:
		CreateNodeMenu();
		break;

		// Takes user to remove menu
	case 4:
		RemoveNodeMenu();
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

// Display Menu
void DisplayMenu()
{
	system("cls");

	// Displays a menu
	SetConsoleTextAttribute(hConsole, LIGHTCYAN);
	std::cout << " === Double Linked List === " << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " DISPLAY MENU" << std::endl << std::endl;
	std::cout << "    Display Nodes        [1]" << std::endl;
	std::cout << "    Sort Nodes           [2]" << std::endl;
	std::cout << "    Display First Node   [3]" << std::endl;
	std::cout << "    Display Last Node    [4]" << std::endl;
	std::cout << "    Display Node Count   [5]" << std::endl;
	SetConsoleTextAttribute(hConsole, RED);
	std::cout << "     BACK TO MENU        [6]" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);

	SetConsoleTextAttribute(hConsole, DARKGRAY);
	std::cout << " Select an option: ";
	SetConsoleTextAttribute(hConsole, WHITE);

	int option{};
	std::cin >> option;
	switch (option)
	{
		// Prints all the nodes
	case 1:
		linkedList.PrintList();
		Pause();
		break;

		// Sorts the nodes and prints the sorted list
	case 2:
		linkedList.BubbleSort();
		linkedList.PrintList();
		Pause();
		break;

		// Prints the first node
	case 3:
		linkedList.PrintFirstNode();
		Pause();
		break;

		// Prints the last node
	case 4:
		linkedList.PrintLastNode();
		Pause();
		break;

		// Prints the total number of nodes
	case 5:
		linkedList.PrintNodeCount();
		Pause();
		break;

		// Goes back to main menu
	case 6:
		break;

		// If input is invalid, user is asked again
	default:
		ErrorMessage();
		DisplayMenu();
		break;
	}

	MainMenu();
}

// Search Node Menu
void SearchNodeMenu()
{
	system("cls");

	// Displays page message
	SetConsoleTextAttribute(hConsole, LIGHTCYAN);
	std::cout << " === Double Linked List === " << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " SEARCH PAGE" << std::endl << std::endl;

	linkedList.SearchNode();
	Pause();

	MainMenu();
}

// Create Node Menu
void CreateNodeMenu()
{
	system("cls");

	// Displays a menu
	SetConsoleTextAttribute(hConsole, LIGHTCYAN);
	std::cout << " === Double Linked List === " << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " CREATE NODE MENU" << std::endl << std::endl;
	std::cout << "    Insert Node First    [1]" << std::endl;
	std::cout << "    Insert Node Last     [2]" << std::endl;
	std::cout << "    Insert Node After    [3]" << std::endl;
	SetConsoleTextAttribute(hConsole, RED);
	std::cout << "     BACK TO MENU        [4]" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);

	SetConsoleTextAttribute(hConsole, DARKGRAY);
	std::cout << " Select an option: ";
	SetConsoleTextAttribute(hConsole, WHITE);

	int option{};
	std::cin >> option;
	switch (option)
	{
		// Asks for new value before calling InsertFirst function
	case 1:
		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Enter new node's value: ";
		SetConsoleTextAttribute(hConsole, WHITE);

		int new_value;
		std::cin >> new_value;
		linkedList.InsertFirst(new_value);

		linkedList.PrintList();
		Pause();
		break;

		// Asks for new value before calling InsertLast function
	case 2:
		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Enter new node's value: ";
		SetConsoleTextAttribute(hConsole, WHITE);

		std::cin >> new_value;
		linkedList.InsertLast(new_value);

		linkedList.PrintList();
		Pause();
		break;

		// Asks for previous and new value before calling InsertAfter function
	case 3:
		linkedList.PrintList();

		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Enter previous node's value: ";
		SetConsoleTextAttribute(hConsole, WHITE);

		int index;
		std::cin >> index;

		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Enter new node's value: ";
		SetConsoleTextAttribute(hConsole, WHITE);

		std::cin >> new_value;

		linkedList.InsertAfter(index, new_value);

		linkedList.PrintList();
		Pause();
		break;

		// Goes back to main menu
	case 4:
		break;

		// If input is invalid, user is asked again
	default:
		ErrorMessage();
		CreateMenu();
		break;
	}

	MainMenu();
}

// Remove Node Menu
void RemoveNodeMenu()
{
	system("cls");

	// Displays a menu
	SetConsoleTextAttribute(hConsole, LIGHTCYAN);
	std::cout << " === Double Linked List === " << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " REMOVE NODE MENU" << std::endl << std::endl;
	std::cout << "    Remove Node First    [1]" << std::endl;
	std::cout << "    Remove Node Last     [2]" << std::endl;
	std::cout << "    Remove Any Node      [3]" << std::endl;
	SetConsoleTextAttribute(hConsole, RED);
	std::cout << "     BACK TO MENU        [4]" << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);

	SetConsoleTextAttribute(hConsole, DARKGRAY);
	std::cout << " Select an option: ";
	SetConsoleTextAttribute(hConsole, WHITE);

	int option{};
	std::cin >> option;
	switch (option)
	{
		// Calls DeleteFirst function
	case 1:
		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " You are removing the first node with a value of: ";
		SetConsoleTextAttribute(hConsole, WHITE);
		std::cout << linkedList.FirstNode();

		linkedList.DeleteFirst();

		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Updated List: " << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);

		linkedList.PrintList();
		Pause();
		break;

		// Calls DeleteLast function
	case 2:
		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " You are removing the last node with a value of: ";
		SetConsoleTextAttribute(hConsole, WHITE);
		std::cout << linkedList.LastNode();

		linkedList.DeleteLast();

		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Updated List: " << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);

		linkedList.PrintList();
		Pause();
		break;

		// Asks for old value before calling DeleteNode function
	case 3:
		linkedList.PrintList();

		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Enter old node's value: ";
		SetConsoleTextAttribute(hConsole, WHITE);

		int old_value;
		std::cin >> old_value;

		linkedList.DeleteNode(old_value);

		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Updated List: " << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);

		linkedList.PrintList();
		Pause();
		break;

		// Goes back to main menu
	case 4:
		break;

		// If input is invalid, user is asked again
	default:
		ErrorMessage();
		CreateMenu();
		break;
	}

	MainMenu();
}

// Exit Menu
void ExitMenu()
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
	bool linkedListRunning = true;

	// ------ Linked List Loop ------ 
	while (linkedListRunning)
	{
		MainMenu();

		linkedListRunning = false;
	}

	// Exits the program
	ExitMenu();
	return 0;
}