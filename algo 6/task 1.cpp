#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <string>
 
using namespace std;
 
const int SIZE = 100003;
 
struct Element {
    Element* prev = nullptr;
    Element* next = nullptr;
    int key;
};
 
struct Hash_table {
    Element* array[SIZE];
 
    void set_nullptr(Element* *data) {
        for (int i = 0; i < SIZE; i++) {
            data[i] = nullptr;
        }
    }
 
    int hash_func(int key) {
        return (key + 1000030000) % SIZE;
    }
     
    Element* search(int key) {
        int hash_result = hash_func(key);
        Element* temp = array[hash_result];
        while (temp != nullptr && temp->key != key) {
            temp = temp->next;
        }
        return temp;
    }
 
    void insert(int key) {
        if (search(key) == nullptr) {
            int hash_result = hash_func(key);
            if (array[hash_result] == nullptr) {
                array[hash_result] = new Element;
                array[hash_result]->key = key;
            }
            else {
                Element* number = new Element;
                number->next = array[hash_result];
                number->key = key;
                array[hash_result] = number;
                number->next->prev = number;
            }
        }
    }
 
    void del(int key) {
        Element* temp = search(key);
        if (temp != nullptr) {
            int hash_result = hash_func(key);
            if (temp->prev != nullptr) {
                if (temp->next != nullptr) { temp->next->prev = temp->prev; }
                temp->prev->next = temp->next;
            }
            else if (temp->next != nullptr) {
                temp->next->prev = nullptr;
                array[hash_result] = temp->next;
            }
            else {
                array[hash_result] = nullptr;
            }
        }
    }
};
 
int main() {
    ifstream fin;
    ofstream fout;
    fin.open("set.in");
    fout.open("set.out");
    Hash_table hash_table;
    hash_table.set_nullptr(hash_table.array);
    string command;
    int number;
    while (fin >> command >> number) {
        switch (command[0]) {
        case 'e':
            if (hash_table.search(number) == nullptr) { fout << "false\n"; }
            else { fout << "true\n"; }
            break;
        case 'i':
            hash_table.insert(number);
            break;
        case 'd':
            hash_table.del(number);
            break;
        }
    }
    fin.close();
    fout.close();
}
