#include <bits/stdc++.h>
#include <filesystem>

using namespace std;

long memory_saved = 0;

struct node
{
    string* File_Name;
    string* date_of_creation;
    int Accessed;
    double size_file;
    string* URL_File;
    node* next;

    node(const string& Name, int Accessed, const string& date_of_creation, double size_file, const string& URL_File)
        : Accessed(Accessed), size_file(size_file), next(nullptr)
    {
        this->File_Name = new string(Name);
        this->date_of_creation = new string(date_of_creation);
        this->URL_File = new string(URL_File);
    }

    ~node()
    {
        delete File_Name;
        delete date_of_creation;
        delete URL_File;
    }
};


class Linkedlist {
    node* Head;
    int size;
public:
    Linkedlist();

    void Insertion(node* element);
    node* Remove_Node(string name);
    int Size();
    void Display_Linkedlist();
    bool Find_redundant(int key);
    node* gethead();
    bool search(string name);
    void Empty_Linkedlist();


    ~Linkedlist();

};

Linkedlist::Linkedlist() {
    size = 0;
    Head = NULL;
}

Linkedlist::~Linkedlist() {
    node* temp = Head;
    while (temp != nullptr) {
        node* temp = temp;
        temp = temp->next;
        delete temp;
    }
}

void Linkedlist::Display_Linkedlist() {
    node* temp = Head;
    if (temp == nullptr) {
        return;
    }
    while (temp != nullptr) {
        cout << "\nFile Name  : " << *temp->File_Name << "\n";
        cout << "Accessed     : " << temp->Accessed << "\n";
        cout << "Created Date : " << *temp->date_of_creation << "\n";
        cout << "File size    : " << temp->size_file << "\n";
        cout << "File URL     : " << *temp->URL_File << "\n\n";
        cout << "******************************************************" << "\n\n";
        temp = temp->next;
    }
}


void Linkedlist::Empty_Linkedlist() {
    node* temp = Head;
    node* nextNode;

    while (temp != nullptr) {
        nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }

    Head = NULL;
}
int Linkedlist::Size() { return size; }

void Linkedlist::Insertion(node* data) {
    size++;
    if (Head == NULL) {
        Head = data;
    }
    else {
        node* temp = Head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = data;
    }
}
node* Linkedlist::Remove_Node(string Name) {
    node* temp = Head->next;
    node* prev = temp;
    if (*prev->File_Name == Name) {
        size--;
        Head = temp;
        return prev;
    }

    while (prev != nullptr) {
        if (*temp->File_Name == Name) {
            size--;
            prev->next = temp->next;
            return temp;
        }
    }
    return nullptr;
}
bool Linkedlist::Find_redundant(int key) {
    node* temp = Head;
    while (temp != nullptr) {
        if (temp->size_file == key) break;
        temp = temp->next;
    }
    if (temp != nullptr) return true;
    else return false;
}
bool Linkedlist::search(string name) {
    node* temp = Head;
    while (temp != nullptr) {
        if (*(temp->File_Name) == name) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}
node* Linkedlist::gethead() {
    return Head;
}




void remove_redundant(node* file, Linkedlist* Linkedlist)
{
    node* temp = Linkedlist->gethead();
    while (temp != nullptr)
    {
        if (Linkedlist->Find_redundant(file->size_file))
        {
            if (remove(file->File_Name->c_str()) != 0)
            {
                string description = "Error deleting a file: In the File " + (*file->URL_File) + "\nPlease check that the file.";
                //displayErrorMessage("Error deleting a file", &description);
                exit(0);
            }
            else
            {
                memory_saved += file->size_file;
            }
        }
    }
    return;
}





long new_date(node* file)
{
    int dd, mm, yyyy;
    long x;

    sscanf((*file->date_of_creation).c_str(), "%d-%d-%d", &dd, &mm, &yyyy);

    x = (yyyy * 10000) + (mm * 100) + dd;
    return x;
}





bool Old_by_Date(node* file, long date)
{

    if (new_date(file) < date)
    {
        return true;
    }
    else return false;
}




bool File_Empty(node* file)
{

    if (file->size_file == 0) return true;

    return false;
}




bool File_Accessed(node* file, int acc)
{

    if (file->Accessed < acc) return true;

    return false;
}




bool IsValid(node* file, int acc, long date)
{
    if (Old_by_Date(file, date))return false;

    else
    {
        if (File_Empty(file)) return false;

        else
        {
            if (File_Accessed(file, acc)) return false;

            else
            {
                return true;
            }
        }
    }
}






void File_seprate(const string& file_path, Linkedlist* valid, Linkedlist* delete_list, int min_acc, int min_date)
{

    int filenumber = 0;


    ifstream file(file_path);
    if (!file.is_open())
    {
        const string msg = "Failed to open file: " + file_path + "\n";
        string description = "File not found.";
        //displayErrorMessage(msg, &description);
        return;
    }

    string line;
    getline(file, line);


    while (getline(file, line))
    {

        filenumber++;
        stringstream ss(line);
        string name, access_count_str, date_created, size_str, URL;


        getline(ss, name, ',');
        getline(ss, access_count_str, ',');
        getline(ss, date_created, ',');
        getline(ss, size_str, ',');
        getline(ss, URL);

        int access_count = stoi(access_count_str);
        long size__ = stoi(size_str);


        node* file_element = new node(name, access_count, date_created, size__, URL);
        if (!IsValid(file_element, min_acc, min_date)) {
            delete_list->Insertion(file_element);
        }
        else {
            valid->Insertion(file_element);
        }
    }

    file.close();
}






void File_empty(const string& file_path, Linkedlist* validfiles, Linkedlist* binfiles)
{

    int filenumber = 0;


    ifstream file(file_path);
    if (!file.is_open())
    {
        const string msg = "Failed to open file: " + file_path + "\n";
        string description = "File not found.";
        // displayErrorMessage(msg, &description);
        return;
    }

    string line;
    getline(file, line);


    while (getline(file, line))
    {

        filenumber++;
        stringstream ss(line);
        string name, access_count_str, date_created, size_str, URL;


        getline(ss, name, ',');
        getline(ss, access_count_str, ',');
        getline(ss, date_created, ',');
        getline(ss, size_str, ',');
        getline(ss, URL);

        int access_count = stoi(access_count_str);
        long size__ = stoi(size_str);

        node* file_element = new node(name, access_count, date_created, size__, URL);
        if (File_Empty(file_element)) {
            binfiles->Insertion(file_element);
        }
        else {
            validfiles->Insertion(file_element);
        }
    }

    file.close();
}





void File_Date(const string& file_path, Linkedlist* validfiles, Linkedlist* binfiles, long date)
{

    int filenumber = 0;


    ifstream file(file_path);
    if (!file.is_open())
    {
        const string msg = "Failed to open file: " + file_path + "\n";
        string description = "File not found.";
        // displayErrorMessage(msg, &description);
        return;
    }

    string line;
    getline(file, line);


    while (getline(file, line))
    {

        filenumber++;
        stringstream ss(line);
        string name, access_count_str, date_created, size_str, URL;


        getline(ss, name, ',');
        getline(ss, access_count_str, ',');
        getline(ss, date_created, ',');
        getline(ss, size_str, ',');
        getline(ss, URL);

        int access_count = stoi(access_count_str);
        long size__ = stoi(size_str);

        node* file_element = new node(name, access_count, date_created, size__, URL);
        if (Old_by_Date(file_element, date)) {
            binfiles->Insertion(file_element);
        }
        else {
            validfiles->Insertion(file_element);
        }
    }

    file.close();
}




void File_Accessed(const string& file_path, Linkedlist* validfiles, Linkedlist* binfiles, int min_acc) {

    int filenumber = 0;


    ifstream file(file_path);
    if (!file.is_open()) {
        const string msg = "Failed to open file: " + file_path + "\n";
        string description = "File not found.";
        // displayErrorMessage(msg, &description);
        return;
    }

    string line;
    getline(file, line);


    while (getline(file, line)) {

        filenumber++;
        stringstream ss(line);
        string name, access_count_str, date_created, size_str, URL;


        getline(ss, name, ',');
        getline(ss, access_count_str, ',');
        getline(ss, date_created, ',');
        getline(ss, size_str, ',');
        getline(ss, URL);

        int access_count = stoi(access_count_str);
        long size__ = stoi(size_str);

        node* file_element = new node(name, access_count, date_created, size__, URL);
        if (File_Accessed(file_element, min_acc)) {
            binfiles->Insertion(file_element);
        }
        else {
            validfiles->Insertion(file_element);
        }
    }

    file.close();
}




void get_saved_memory() {

    cout << "Memory saved in KB " << memory_saved << endl;

}




void Checking(string file_name, Linkedlist* bin, Linkedlist* valid) {
    if (bin->search(file_name)) {
        valid->Insertion(bin->Remove_Node(file_name));
    }
}


void remove_file(Linkedlist* List_Delete) {
    node* temp = List_Delete->gethead();
    while (temp != nullptr) {
        memory_saved += temp->size_file;
        string element = *temp->File_Name;
        cout << element;
        remove(element.c_str());
        temp = temp->next;
    }
    cout << "\nFile Successfully deleted" << endl;
}


int main() {
    Linkedlist List, List_Delete;
    string File_URL;
    cout << "Please Enter the file url having the details of the folder" << endl;

    cin >> File_URL;
    ifstream file(File_URL);

start:

    cout << "Enter a number between 1 and 5 to implement the following operations in the folder:\n";
    cout << " To remove the redundant files, type 1. \n";
    cout << " To remove the old files, type 2 \n";
    cout << " To remove empty files from the folder, type 3 \n";
    cout << " To Remove the files accessed less number of times than you want, type 4 \n";
    cout << " To According to all of the above, type 5  \n";
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

        sscanf(date_str.c_str(), "%d-%d-%d", &dd, &mm, &yyyy);

        date = (yyyy * 10000) + (mm * 100) + dd;
        File_seprate(File_URL, &List, &List_Delete, min_acc, date);
        break;
    }


    case 2: {
        cout << "Plese enter the date from before you want to delete files(in dd-mm-yyyy) : ";
        cin >> date_str;
        int dd, mm, yyyy;
        long date;

        sscanf(date_str.c_str(), "%d-%d-%d", &dd, &mm, &yyyy);

        date = (yyyy * 10000) + (mm * 100) + dd;
        File_seprate(File_URL, &List, &List_Delete, date, 100);
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
    //List.Display_Linkedlist();
    List_Delete.Display_Linkedlist();


    remove_file(&List_Delete);
    get_saved_memory();



    return 0;
}