#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
 
using namespace std;
 
const int SIZE = 100003;
 
struct Element {
    Element* prev = nullptr;
    Element* next = nullptr;
    string key;
    string value;
};
 
struct Hash_table {
    Element* array[SIZE];
 
    void set_nullptr(Element* *data) {
        for (int i = 0; i < SIZE; i++) {
            data[i] = nullptr;
        }
    }
 
    int hash_func(string s) {
        int result = 0, power = 1;
        const int MUL = 29;
        int temp = 1;
        for (int i = 0; i < s.length(); i++) {
            result += (int(s[i]) - 'A' + 1) * power;
            result %= SIZE;
            power = (power * MUL) % SIZE;
        }
        return result;
    }
     
    Element* search(string key) {
        int hash_result = hash_func(key);
        Element* temp = array[hash_result];
        while (temp != nullptr && temp->key != key) {
            temp = temp->next;
        }
        return temp;
    }
 
    void insert(string key, string value) {
        Element* temp = search(key);
        if (temp == nullptr) {
            int hash_result = hash_func(key);
            if (array[hash_result] == nullptr) {
                array[hash_result] = new Element;
                array[hash_result]->key = key;
                array[hash_result]->value = value;
            }
            else {
                Element* number = new Element;
                number->next = array[hash_result];
                number->key = key;
                number->value = value;
                array[hash_result] = number;
                number->next->prev = number;
            }
        }
        else { temp->value = value; }
    }
 
    void del(string key) {
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
    fin.open("map.in");
    fout.open("map.out");
    Hash_table map;
    map.set_nullptr(map.array);
    string command, key, value;
    int number;
    while (fin >> command) {
        switch (command[0]) {
        case 'p':
            fin >> key >> value;
            map.insert(key, value);
            break;
        case 'g':
            fin >> key;
            {
                Element* temp = map.search(key);
                if (temp != nullptr) { fout << temp->value << '\n'; }
                else { fout << "none\n"; }
            }
            break;
        case 'd':
            fin >> key;
            map.del(key);
            break;
        }
    }
    fin.close();
    fout.close();
}
