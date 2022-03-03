#include <iostream>
#include <fstream>
#include <string>
#include <vector>
 
using namespace std;
 
int main() {
    ofstream fout;
    ifstream fin;
    fout.open("sortland.out");
    fin.open("sortland.in");
    string n, str, a;
    fin >> n;
    int amount = stoi(n);
    int start = 0;
    vector<float> numbers;
    vector<int> index;
    for (int i = 0; i < amount; i++) {
        fin >> a;
        numbers.push_back(stof(a));
        index.push_back(i + 1);
    }
    for (int i = 0; i < amount; i++) {
        for (int j = 0; j < amount - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                swap(numbers[j], numbers[j + 1]);
                swap(index[j], index[j + 1]);
            }
        }
    }
    fout << index[0] << ' ' << index[amount / 2] << ' ' << index[amount - 1];
    fout.close();
    fin.close();
}
