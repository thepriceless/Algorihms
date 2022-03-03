#include<iostream>
#include<fstream>
#include<string>
 
int main() {
    std::ifstream fin;
    std::ofstream fout;
    fin.open("input.txt");
    fout.open("output.txt");
    int dots, sticks, start, end;
    bool nice = true;
    fin >> dots >> sticks;
    int** table = new int* [dots];
    for (int i = 0; i < dots; i++) {
        table[i] = new int[dots];
        for (int j = 0; j < dots; j++) { table[i][j] = 0; }
    }
    for (int i = 0; i < sticks; i++) {
        fin >> start >> end;
        table[start - 1][end - 1]++;
        table[end - 1][start - 1]++;
        if ((table[start - 1][end - 1] > 1) || (table[end - 1][start - 1] > 1)) { nice = false; }
    }
    if (nice) { fout << "NO"; }
    else { fout << "YES"; }
}
