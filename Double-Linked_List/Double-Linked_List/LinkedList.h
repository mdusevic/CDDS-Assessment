#pragma once

#include <Windows.h>

// Node class 
class Node
{
public:
	int data;
	struct Node* prev;
	struct Node* next;
};

// Linked List class
class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	// Console Handle
	HANDLE hConsole;

	// Menu Functions
	void MainMenu();
	void DisplayMenu();
	void SearchNodeMenu();
	void CreateNodeMenu();
	void RemoveNodeMenu();
	void ExitMenu();
	void ErrorMessage();
	void Pause();

protected:
	// Other Functions
	void Init();
	bool IsListEmpty();
	Node* FirstNode();
	Node* LastNode();
	int NodeCount();
	void BubbleSort();

	// Insert Functions
	void InsertFirst(int new_data);
	void InsertLast(int new_data);
	void InsertAfter(int index, int new_data);

	// Delete Functions
	void DeleteFirst();
	void DeleteLast();
	void DeleteNode(int old_data);

	// Search Functions
	Node* Search(int searched_data);
	void SearchNode();

	// Print Functions
	void PrintFirstNode();
	void PrintLastNode();
	void PrintNodeCount();
	void PrintList();

private:
};