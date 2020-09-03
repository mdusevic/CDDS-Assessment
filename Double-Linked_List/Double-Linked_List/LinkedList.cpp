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

// Checks if list is empty, returns a bool value
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

// Swap function for bubble sort
void LinkedList::Swap(Node* node_1, Node* node_2)
{
	int temp = node_1->data;
	node_1->data = node_2->data;
	node_2->data = temp;
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

		do
		{
			swapped = false;
			node = head;

			while (node->next != temp)
			{
				if (node->data > node->next->data)
				{
					Swap(node, node->next);
					swapped = true;
				}

				node = node->next;
			}

			temp = node;
		} while (swapped);

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
	// If list is not empty
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