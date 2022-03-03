#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
 
using namespace std;
 
const int SIZE = 100003;
 
struct Element {
    Element* prev_in_arr = nullptr;
    Element* next_in_arr = nullptr;
    Element* prev_key = nullptr;
    Element* next_key = nullptr;
    string key;
    string value;
};
 
struct Hash_table {
    Element* array[SIZE];
    Element* tail_for_keys = nullptr;
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
            temp = temp->next_in_arr;
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
                if (tail_for_keys == nullptr) {
                    tail_for_keys = array[hash_result];
                }
                else {
                    array[hash_result]->prev_key = tail_for_keys;
                    tail_for_keys = array[hash_result];
                    array[hash_result]->prev_key->next_key = array[hash_result];
                }
            }
            else {
                Element* number = new Element;
                number->next_in_arr = array[hash_result];
                number->key = key;
                number->value = value;
                array[hash_result] = number;
                number->next_in_arr->prev_in_arr = number;
                if (tail_for_keys == nullptr) {
                    tail_for_keys = number;
                }
                else {
                    number->prev_key = tail_for_keys;
                    tail_for_keys = number;
                    number->prev_key->next_key = number;
                }
            }
        }
        else { temp->value = value; }
    }
 
    void del(string key) {
        Element* temp = search(key);
        if (temp != nullptr) {
            int hash_result = hash_func(key);
            if (temp->prev_in_arr != nullptr) {
                if (temp->next_in_arr != nullptr) { temp->next_in_arr->prev_in_arr = temp->prev_in_arr; }
                temp->prev_in_arr->next_in_arr = temp->next_in_arr;
            }
            else if (temp->next_in_arr != nullptr) {
                temp->next_in_arr->prev_in_arr = nullptr;
                array[hash_result] = temp->next_in_arr;
            }
            else {
                array[hash_result] = nullptr;
            }
            if (temp->prev_key != nullptr) {
                temp->prev_key->next_key = temp->next_key;
            }
            if (temp->next_key != nullptr) {
                temp->next_key->prev_key = temp->prev_key;
            }
            else { tail_for_keys = temp->prev_key; }
        }
    }
};
 
int main() {
    ifstream fin;
    ofstream fout;
    fin.open("linkedmap.in");
    fout.open("linkedmap.out");
    Hash_table map;
    map.set_nullptr(map.array);
    string command, key, value;
    int number;
    Element* temp;
    while (fin >> command) {
        if (command == "put") {
            fin >> key >> value;
            map.insert(key, value);
        }
        else if (command == "get") {
            fin >> key;
            temp = map.search(key);
            if (temp != nullptr) { fout << temp->value << '\n'; }
            else { fout << "none\n"; }
        }
        else if (command == "delete") {
            fin >> key;
            map.del(key);
        }
        else if (command == "prev") {
            fin >> key;
            temp = map.search(key);
            if (temp == nullptr) { fout << "none\n"; }
            else if (temp->prev_key == nullptr) { fout << "none\n"; }
            else { fout << temp->prev_key->value << "\n"; }
        }
        else if (command == "next") {
            fin >> key;
            temp = map.search(key);
            if (temp == nullptr) { fout << "none\n"; }
            else if (temp->next_key == nullptr) { fout << "none\n"; }
            else { fout << temp->next_key->value << "\n"; }
        }
    }
    fin.close();
    fout.close();
}
