#include<iostream>
#include<fstream>
#include<string>
 
int main() {
    std::ifstream fin;
    std::ofstream fout;
    fin.open("input.txt");
    fout.open("output.txt");
    int size, num;
    bool nice = true;
    fin >> size;
    int** table = new int* [size];
    for (int i = 0; i < size; i++) {
        table[i] = new int[size];
    }
    for(int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fin >> num;
            table[i][j] = num;
        }
    }
    for (int i = 0; i < size; i++) {
        if (table[i][i] != 0) { nice = false; }
        for (int j = i; j < size; j++) {
            if ((table[i][j] != table[j][i]) || (table[i][j] > 1)) { nice = false; }
        }       
    }
    if (nice) { fout << "YES"; }
    else { fout << "NO"; }
}
