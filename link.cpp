#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include<ctime>
#include "node.h"
#include "link.h"


Linkedlist::Linkedlist() {
    size = 0;
    Head = NULL;
}

Linkedlist::~Linkedlist() {
    node* current = Head;
    while (current != nullptr) {
        node* temp = current;
        current = current->next;
        delete temp;
    }
}

void Linkedlist::Display_Linkedlist() {
    node* currant = Head;
    if (currant == nullptr) {
        return;
    }
    while (currant != nullptr) {
        cout << "\nName of the file                  : " << *currant->File_Name << "\n";
        cout << "number of Times accessed          : " << currant->Accessed << "\n";
        cout << "created file on                   : " << *currant->date_of_creation << "\n";
        cout << "size of the file                  : " << currant->size_file << "\n";
        cout << "file location                     : " << *currant->URL_File << "\n\n";
        cout << "----------------------------------------" << "\n\n";
        currant = currant->next;
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