#include "LinkedList.h"

// Main Function
int main()
{
	bool linkedListRunning = true;

	LinkedList linkedList;

	// ------ Linked List Loop ------ 
	while (linkedListRunning)
	{
		linkedList.MainMenu();

		linkedListRunning = false;
	}

	// Exits the program
	linkedList.ExitMenu();
	return 0;
}