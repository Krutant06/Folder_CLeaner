// Capstone final.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "node.h"
#include "functions.cpp"
using namespace std;

int main() {
	Linkedlist List, List_Delete;
	string File_URL;


	cout << "Enter a Number";


	cin >> File_URL;
	ifstream file(File_URL);



	cout << "On which basis do you want to clean your file :\n";
	cout << "1) remove Redundant files \n";
	cout << "2) remove old files \n";
	cout << "3) remove empty files \n";
	cout << "4) remove low access files \n";
	cout << "5) according to all of the above  \n";
	cout << "now select according to any of the above :\n";
	cout << "(Note : you can make two choices later on so don't worry about it)\n";

	int i = 0; int min_acc = 0; string date_str;
	cin >> i;
	if (i > 5 || i < 1) goto start;
	switch (i) {
	case 5: {
		cout << "Give the minimun nmber of access :\n(Note: anything which has less access count than minimum access count will be removed)\n";
		cin >> min_acc;
		cout << "Plese enter the date from before you want to delete files(in dd-mm-yyyy) : ";
		cin >> date_str;
		int dd, mm, yyyy;
		long date;

		sscanf(date_str.c_str(), "%d-%d-%d", &dd, &mm, &yyyy);

		date = (yyyy * 10000) + (mm * 100) + dd;
		sepratedata_by_all(file_location, &remain, &bin, min_acc, date, "By creation date");
		break;
	}


	case 2: {
		cout << "Plese enter the date from before you want to delete files(in dd-mm-yyyy) : ";
		cin >> date_str;
		int dd, mm, yyyy;
		long date;

		sscanf(date_str.c_str(), "%d-%d-%d", &dd, &mm, &yyyy);

		date = (yyyy * 10000) + (mm * 100) + dd;
		sepratedata_by_date(file_location, &remain, &bin, date, "By creation date");
		break;
	}
	case 4: {
		cout << "Give the minimun nmber of access :\n(Note: anything which has less access count than minimum access count will be removed)\n";
		cin >> min_acc;
		sepratedata_by_access_count(file_location, &remain, &bin, min_acc);
		break;
	}
	case 3: {
		sepratedata_by_empty(file_location, &remain, &bin);
		break;
	}

	case 1: {
		sepratedata_by_empty(file_location, &remain, &bin);
		break;
	}
	}


}

	char check;
	cout << "press X to exit...\n";
	cin >> check;
	if (check == 'x')
		return 0;
	else return 0;
}