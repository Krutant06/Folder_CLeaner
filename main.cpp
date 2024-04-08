// Capstone final.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "functions.cpp"

using namespace std;

int main() {
	Linkedlist List, List_Delete;
	string File_URL;

	cin >> File_URL;
	ifstream file(File_URL);

start:

	cout << "Select a Number :\n";
	cout << "1) Remove Redundant files \n";
	cout << "2) Remove old files \n";
	cout << "3) Remove empty files \n";
	cout << "4) Remove low access files \n";
	cout << "5) According to all of the above  \n";
	cout << "now select according to any of the above :\n";

	int i = 0; int min_acc = 0; string date_str;
	cin >> i;
	if (i > 5 || i < 1) {
		cout << "Please Enter a valid Number";
		goto start;
	}
	switch (i) {
	case 5: {
		cout << "Give the minimun nmber of access :\n(Note: anything which has less access count than minimum access count will be removed)\n";
		cin >> min_acc;
		cout << "Plese enter the date from before you want to delete files(in dd-mm-yyyy) : ";
		cin >> date_str;
		int dd, mm, yyyy;
		long date;

		sscanf_s(date_str.c_str(), "%d-%d-%d", &dd, &mm, &yyyy);

		date = (yyyy * 10000) + (mm * 100) + dd;
		//File_seprate(File_URL, &List, &List_Delete, min_acc, date);
		break;
	}


	case 2: {
		cout << "Plese enter the date from before you want to delete files(in dd-mm-yyyy) : ";
		cin >> date_str;
		int dd, mm, yyyy;
		long date;

		sscanf_s(date_str.c_str(), "%d-%d-%d", &dd, &mm, &yyyy);

		date = (yyyy * 10000) + (mm * 100) + dd;
		//File_seprate(File_URL, &List, &List_Delete, date, "By creation date");
		break;
	}
	case 4: {
		cout << "Give the minimun nmber of access :\n(Note: anything which has less access count than minimum access count will be removed)\n";
		cin >> min_acc;
		File_Accessed(File_URL, &List, &List_Delete, min_acc);
		break;
	}
	case 3: {
		File_empty(File_URL, &List, &List_Delete);
		break;
	}

	case 1: {
		File_empty(File_URL, &List, &List_Delete);
		break;
	}
	}

	return 0;
}