#include <iostream>
#include <fstream>
#include <string>
#include <vector>
 
using namespace std;
 
int main() {
    ofstream fout;
    ifstream fin;
    fout.open("smallsort.out");
    fin.open("smallsort.in");
    string n, str, a;
    fin >> n;
    int amount = stoi(n);
    int start = 0;
    vector<int> numbers;
    for (int i = 0; i < amount; i++) {
        fin >> a;
        numbers.push_back(stoi(a));
    }
    for (int i = 0; i < amount; i++) {
        for (int j = 0; j < amount - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                swap(numbers[j], numbers[j + 1]);
            }
        }
    }
    for (int i = 0; i < amount - 1; i++) {
        fout << numbers[i] << ' ';
    }
    fout << numbers[amount - 1];
    fout.close();
    fin.close();
}
