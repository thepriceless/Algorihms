#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
 
using namespace std;
 
long n;
 
long binary_search(long* a, long left, long right, long to_find, bool first) {
    long middle_index = (left + right) / 2;
    if (left + 1 < right) {
        if (a[middle_index] > to_find) {
            return binary_search(a, left, middle_index, to_find, first);
        }
        if (a[middle_index] < to_find) {
            return binary_search(a, middle_index, right, to_find, first);
        }
        if (first) {
            if ((middle_index > 0) && (a[middle_index - 1] == to_find)) {
                return binary_search(a, left, middle_index, to_find, first);
            }
            return middle_index + 1;
        }
        else {
            if ((middle_index < n) && (a[middle_index + 1] == to_find)) {
                return binary_search(a, middle_index, right, to_find, first);
            }
            return middle_index + 1;
        }
    }
    return -1;
}
 
int main() {
    ifstream fin;
    ofstream fout;
    fin.open("binsearch.in");
    fout.open("binsearch.out");
    long call;
    int num;
    fin >> n;
    long *numbers = new long [n];
    for (long i = 0; i < n; i++) {
        fin >> num;
        numbers[i] = num;
    }
    fin >> call;
    for (long i = 0; i < call; i++) {
        fin >> num;
        fout << binary_search(numbers, -1, n, num, true) << ' ';
        fout << binary_search(numbers, -1, n, num, false);
        if (i != call - 1) {
            fout << endl;
        }
    }
    fin.close();
    fout.close();
}
