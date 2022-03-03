#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
 
using namespace std;
 
double minimum_B = 10000000;
 
bool garland(double *heights, double zero, double first, int amount) {
    heights[0] = zero;
    heights[1] = first;
    int amount_on_the_floor = 0;
    for (int i = 2; i < amount; i++) {
        heights[i] = 2 + 2 * heights[i - 1] - heights[i - 2];
        if (heights[i] < 0) {
            return false;
        }
        if (heights[i] == 0) {
            if (amount_on_the_floor > 0) {
                return false;
            }
            else {
                amount_on_the_floor++;
            }
        }
    }
    minimum_B = min(minimum_B, heights[amount - 1]);
    return true;
}
 
double binary_search(double* heights, double zero, double first, int amount, double left, double right) {
    double middle_index = (left + right) / 2;
    if (left + 0.0000001 < right) {
        if (garland(heights, zero, middle_index, amount) == true) {
            binary_search(heights, zero, first, amount, left, middle_index);
        }
        else {
            binary_search(heights, zero, first, amount, middle_index, right);
        }
    }
    return middle_index;
}
 
int main() {
    ifstream fin;
    ofstream fout;
    fin.open("garland.in");
    fout.open("garland.out");
    int n;
    double left_highest;
    fin >> n >> left_highest;
    double *lamp_height = new double [n];
    binary_search(lamp_height, left_highest, 0, n, -0.01, left_highest);
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << minimum_B;
    fin.close();
    fout.close();
}
