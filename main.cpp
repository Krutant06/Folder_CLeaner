// Capstone final.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "node.h"
#include "functions.cpp"

int main() {
	Linkedlist List, List_Delete;
	string File_URL;


	cin >> File_URL;
	ifstream file(File_URL);





















































	//L.Display();
	//bin.Display();

	remove_list(&List_Delete);
	//bin.Display();
	//L.Display();


	char check;
	cout << "press X to exit...\n";
	cin >> check;
	if (check == 'x')
		return 0;
	else return 0;
}