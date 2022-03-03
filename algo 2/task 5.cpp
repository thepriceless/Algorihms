#include <iostream>
#include <fstream>
#include <string>
#include <vector>
 
using namespace std;
 
int32_t quick_sort(vector<int32_t>& A, int left, int right, int k) {
    int key, i = left, j = right;
    key = A[(left + right) / 2];
    do {
        while (A[i] < key) {
            i++;
        }
        while (A[j] > key) {
            j--;
        }
        if (i <= j) {
            swap(A[i], A[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (k <= j) {
        return quick_sort(A, left, j, k);
    }
    if (k >= i) {
        return quick_sort(A, i, right, k);
    }
    return key;
}
 
int main() {
    ofstream fout;
    ifstream fin;
    fout.open("kth.out");
    fin.open("kth.in");
    int n, k, a, b, c, first, second;
    fin >> n >> k;
    k--;
    fin >> a >> b >> c >> first >> second;
    vector<int32_t> numbers;
    numbers.push_back(first);
    numbers.push_back(second);
    for (int i = 2; i < n; i++) {
        numbers.push_back((int32_t)(a * numbers[i - 2] + b * numbers[i - 1] + c));
    }
    fout << quick_sort(numbers, 0, n - 1, k);
    fout.close();
    fin.close();
}
