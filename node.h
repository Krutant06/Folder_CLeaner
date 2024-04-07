#pragma once

#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include<ctime>

using namespace std;

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