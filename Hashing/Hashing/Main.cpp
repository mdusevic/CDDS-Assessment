#include "HashFunction.h"

// Main Function
int main()
{
	bool directoryRunning = true;

	HashFunction hashtable;

	// ------ Directory Loop ------ 
	while (directoryRunning)
	{
		hashtable.MainMenu();

		directoryRunning = false;
	}

	// Exits the program
	hashtable.ExitPage();
	return 0;
}