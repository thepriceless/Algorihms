#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
 
using namespace std;
 
struct stack {
    long line[2000];
    long top_free = 0;
    void push(long elem) {
        line[top_free++] = elem;
    }
    long extract() {
        return line[--top_free];
    }
};
 
int main() {
    ifstream fin;
    ofstream fout;
    fin.open("postfix.in");
    fout.open("postfix.out");
    stack number_stack;
    string command;
    long a, b;
    while (fin >> command) {
        switch (command[0]) {
        case '*':
            a = number_stack.extract();
            b = number_stack.extract();
            number_stack.push(a * b);
            break;
        case '+':
            a = number_stack.extract();
            b = number_stack.extract();
            number_stack.push(a + b);
            break;
        case '-':
            if (command.length() == 1) {
                a = number_stack.extract();
                b = number_stack.extract();
                number_stack.push(b - a);
                break;
            }
        default:
            number_stack.push((long)stoi(command));
            break;
        }
    }
    fout << number_stack.extract();
    fin.close();
    fout.close();   
}
