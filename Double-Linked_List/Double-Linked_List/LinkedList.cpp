#include "LinkedList.h"
#include "Colours.h"
#include <iostream>

LinkedList::LinkedList()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

LinkedList::~LinkedList()
{

}

struct Node* head;
struct Node* tail;

// -------------------- OTHER FUNCTIONS --------------------

// Sets the first and last node of the list to NULL
void LinkedList::Init()
{
	head = NULL;
	tail = NULL;
}

// Checks is list is empty, returns a bool value
bool LinkedList::IsListEmpty()
{
	if (head == NULL)
	{
		return true;
	}

	return false;
}

// Returns head node
Node* LinkedList::FirstNode()
{
	return head;
}

// Returns tail node
Node* LinkedList::LastNode()
{
	return tail;
}

// Returns the number of nodes
int LinkedList::NodeCount()
{
	// If list is not empty
	if (!IsListEmpty())
	{
		int count = 0;
		Node* temp = head;

		while (temp != NULL)
		{
			count++;
			temp = temp->next;
		}

		return count;
	}

	return 0;
}

// Sorts the content of linked list in ascending order
void LinkedList::BubbleSort()
{
	// If list is not empty
	if (!IsListEmpty())
	{
		// If only one node in list
		if (head == tail)
		{
			return;
		}

		// Bubble Sort 
		bool swapped{};
		Node* node;
		Node* temp = NULL;

		while (!swapped)
		{
			swapped = false;
			node = head;

			while (node->next != NULL)
			{
				if (node->data > node->next->data)
				{
					std::swap(node->data, node->next->data);
					swapped = true;
				}

				node = node->next;
			}

			temp = node;
		}

		return;
	}

	SetConsoleTextAttribute(hConsole, RED);
	std::cout << " Input invalid, list is empty." << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	return;
}

// -------------------- INSERT FUNCTIONS --------------------

// Inserts a new node at the front of the list
void LinkedList::InsertFirst(int new_data)
{
	Node* newNode = new Node();

	// If list is empty
	if (IsListEmpty())
	{
		head = newNode;
		newNode->prev = NULL;
		newNode->data = new_data;
		newNode->next = NULL;
		tail = newNode;
	}

	else
	{
		newNode->prev = NULL;
		newNode->data = new_data;
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
}

// Inserts a new node at the end of the list
void LinkedList::InsertLast(int new_data)
{
	Node* newNode = new Node();

	// If list is empty
	if (IsListEmpty())
	{
		InsertFirst(new_data);
	}

	else
	{
		newNode->prev = tail;
		newNode->data = new_data;
		newNode->next = NULL;
		tail->next = newNode;
		tail = newNode;
	}
}

// Inserts a new node after given point
void LinkedList::InsertAfter(int index, int new_data)
{
	Node* newNode = new Node();
	Node* temp = head;

	// If list is empty
	if (IsListEmpty())
	{
		SetConsoleTextAttribute(hConsole, RED);
		std::cout << " Input invalid, list is empty." << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
		return;
	}

	if (tail->data == index)
	{
		InsertLast(new_data);
		return;
	}

	while (temp->data != index)
	{
		temp = temp->next;

		if (temp == NULL)
		{
			SetConsoleTextAttribute(hConsole, RED);
			std::cout << " Input invalid, previous value does not exist." << std::endl;
			SetConsoleTextAttribute(hConsole, WHITE);
			return;
		}
	}

	newNode->next = temp->next;
	newNode->prev = temp;
	newNode->data = new_data;
	temp->next->prev = newNode;
	temp->next = newNode;
}

// -------------------- DELETE FUNCTIONS --------------------

// Deletes the node at the front of the list
void LinkedList::DeleteFirst()
{
	Node* n = head;

	// If list is empty
	if (IsListEmpty())
	{
		SetConsoleTextAttribute(hConsole, RED);
		std::cout << " Input invalid, list is empty." << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
		return;
	}

	// If there is only one item in list
	if (head == tail)
	{
		Init();
		delete n;
		return;
	}

	else
	{
		head = head->next;
		head->prev = NULL;
		delete n;
		return;
	}
}

// Deletes the node at the end of the list
void LinkedList::DeleteLast()
{
	Node* n = tail;

	// If list is empty
	if (IsListEmpty())
	{
		SetConsoleTextAttribute(hConsole, RED);
		std::cout << " Input invalid, list is empty." << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
		return;
	}

	// If there is only one item in list
	if (head == tail)
	{
		Init();
		delete n;
		return;
	}

	else
	{
		tail = tail->prev;
		tail->next = NULL;
		delete n;
		return;
	}
}

// Deletes the desired node from anywhere in the list
void LinkedList::DeleteNode(int old_data)
{
	Node* temp = head;

	// If list is empty
	if (IsListEmpty())
	{
		SetConsoleTextAttribute(hConsole, RED);
		std::cout << " Input invalid, list is empty." << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
		return;
	}

	// If there is only one item in list
	if (temp == tail)
	{
		Init();
		delete temp;
		return;
	}

	// If the head is the node to delete, call function to delete first node
	if (temp->data == old_data)
	{
		DeleteFirst();
		delete temp;
		return;
	}

	// If the tail is the node to delete, call function to delete last node
	if (tail->data == old_data)
	{
		DeleteLast();
		delete temp;
		return;
	}

	while (temp->data != old_data)
	{
		temp = temp->next;

		if (temp == NULL)
		{
			SetConsoleTextAttribute(hConsole, RED);
			std::cout << " Input invalid, value does not exist." << std::endl;
			SetConsoleTextAttribute(hConsole, WHITE);
			return;
		}
	}

	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;
	delete temp;
}

// -------------------- SEARCH FUNCTIONS --------------------

// Returns desired node 
Node* LinkedList::Search(int searched_data)
{
	Node* temp = head;

	// While no node is null, run search
	while (temp != NULL)
	{
		if (temp->data == searched_data)
		{
			return temp;
			break;
		}

		temp = temp->next;
	}

	return NULL;
}

// Calls search function to find the desired node
void LinkedList::SearchNode()
{
	// If list is not empty
	if (!IsListEmpty())
	{
		// Asks for input
		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Enter Value to Search: ";
		SetConsoleTextAttribute(hConsole, WHITE);
		
		int input;
		std::cin >> input;

		Node* node = Search(input);

		if (node != NULL)
		{
			SetConsoleTextAttribute(hConsole, LIGHTGREEN);
			std::cout << "  FOUND ";
			SetConsoleTextAttribute(hConsole, WHITE);
			std::cout << node->data << std::endl;
			return;
		}

		else
		{
			SetConsoleTextAttribute(hConsole, LIGHTRED);
			std::cout << "  NOT FOUND" << std::endl;
			SetConsoleTextAttribute(hConsole, WHITE);
			return;
		}
	}

	SetConsoleTextAttribute(hConsole, RED);
	std::cout << " Input invalid, list is empty. " << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	return;
}

// -------------------- PRINT FUNCTIONS --------------------

// Prints the first node in the list
void LinkedList::PrintFirstNode()
{
	// If list is empty
	if (IsListEmpty())
	{
		SetConsoleTextAttribute(hConsole, RED);
		std::cout << " Input invalid, list is empty. " << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
		return;
	}

	SetConsoleTextAttribute(hConsole, YELLOW);
	std::cout << std::endl << " First Node: ";
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << FirstNode()->data << std::endl;
	return;
}

// Prints the last node in the list
void LinkedList::PrintLastNode()
{
	// If list is empty
	if (IsListEmpty())
	{
		SetConsoleTextAttribute(hConsole, RED);
		std::cout << " Input invalid, list is empty. " << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
		return;
	}

	SetConsoleTextAttribute(hConsole, YELLOW);
	std::cout << std::endl << " Last Node: ";
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << LastNode()->data << std::endl;
	return;
}

// Prints the number of nodes in list
void LinkedList::PrintNodeCount()
{
	SetConsoleTextAttribute(hConsole, YELLOW);
	std::cout << std::endl << " Number of Nodes: ";
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << NodeCount() << std::endl;
	return;
}

// Prints contents of linked list
void LinkedList::PrintList()
{
	if (!IsListEmpty())
	{
		Node* temp = head;

		std::cout << " ";

		while (temp != NULL)
		{
			std::cout << " " << temp->data;

			if (temp->next != NULL)
			{
				SetConsoleTextAttribute(hConsole, LIGHTCYAN);
				std::cout << " <->";
				SetConsoleTextAttribute(hConsole, WHITE);
			}

			temp = temp->next;
		}

		std::cout << std::endl;
		return;
	}

	SetConsoleTextAttribute(hConsole, RED);
	std::cout << " Input invalid, list is empty." << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	return;
}

// -------------------- MENU FUNCTIONS --------------------

// Main Menu
void LinkedList::MainMenu()
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
void LinkedList::DisplayMenu()
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
		PrintList();
		Pause();
		break;

	// Sorts the nodes and prints the sorted list
	case 2:
		BubbleSort();
		PrintList();
		Pause();
		break;

	// Prints the first node
	case 3:
		PrintFirstNode();
		Pause();
		break;

	// Prints the last node
	case 4:
		PrintLastNode();
		Pause();
		break;

	// Prints the total number of nodes
	case 5:
		PrintNodeCount();
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
void LinkedList::SearchNodeMenu()
{
	system("cls");

	// Displays page message
	SetConsoleTextAttribute(hConsole, LIGHTCYAN);
	std::cout << " === Double Linked List === " << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " SEARCH PAGE" << std::endl << std::endl;

	SearchNode();
	Pause();

	MainMenu();
}

// Create Node Menu
void LinkedList::CreateNodeMenu()
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
		InsertFirst(new_value);

		PrintList();
		Pause();
		break;

	// Asks for new value before calling InsertLast function
	case 2:
		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Enter new node's value: ";
		SetConsoleTextAttribute(hConsole, WHITE);

		std::cin >> new_value;
		InsertLast(new_value);

		PrintList();
		Pause();
		break;

	// Asks for previous and new value before calling InsertAfter function
	case 3:
		PrintList();

		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Enter previous node's value: ";
		SetConsoleTextAttribute(hConsole, WHITE);

		int index;
		std::cin >> index;

		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Enter new node's value: ";
		SetConsoleTextAttribute(hConsole, WHITE);

		std::cin >> new_value;

		InsertAfter(index, new_value);

		PrintList();
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
void LinkedList::RemoveNodeMenu()
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
		std::cout << head->data;

		DeleteFirst();

		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Updated List: " << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);

		PrintList();
		Pause();
		break;

	// Calls DeleteLast function
	case 2:
		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " You are removing the last node with a value of: ";
		SetConsoleTextAttribute(hConsole, WHITE);
		std::cout << tail->data;

		DeleteLast();

		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Updated List: " << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);

		PrintList();
		Pause();
		break;

	// Asks for old value before calling DeleteNode function
	case 3:
		PrintList();

		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Enter old node's value: ";
		SetConsoleTextAttribute(hConsole, WHITE);

		int old_value;
		std::cin >> old_value;

		DeleteNode(old_value);

		SetConsoleTextAttribute(hConsole, DARKGRAY);
		std::cout << " Updated List: " << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);

		PrintList();
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
void LinkedList::ExitMenu()
{
	std::cout << std::endl << " Press 'Enter' exit the program.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	return;
}

// Error Message
void LinkedList::ErrorMessage()
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
void LinkedList::Pause()
{
	std::cout << std::endl << " Press 'Enter' to go back to the main menu.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	return;
}