#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
 
using namespace std;
 
struct stack {
    long *numbers = (long*) malloc(1000000 * sizeof(long));
    long top_free = 0;
    void push(long elem) {
        numbers[top_free++] = elem;
    }
    long extract() {
        return numbers[--top_free];
    }
};
 
int main() {
    ofstream fout;
    ifstream fin;
    fin.open("stack.in");
    fout.open("stack.out");
    stack number_stack;
    int n;
    long num;
    char command;
    bool first_writing = true;
    fin >> n;
    for (long i = 0; i < n; i++) {
        fin >> command;
        if (command == '+') {
            fin >> num;
            number_stack.push(num);
        }
        else {
            if (first_writing) {
                fout << number_stack.extract();
                first_writing = false;
            }
            else {
                fout << endl << number_stack.extract();
            }
        }
    }
    fout.close();
    fin.close();
}
