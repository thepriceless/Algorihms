#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
 
using namespace std;
 
struct stack {
    char line[10000];
    long top_free = 0;
    void push(long elem) {
        line[top_free++] = elem;
    }
    long extract() {
        return line[--top_free];
    }
};
 
enum brackets{
    open_bracket = 1,
    close_bracket = -4,
    open_square_bracket = 2,
    close_square_bracket = -2,
};
 
brackets from_bracket_to_name(char bracket) {
    switch (bracket) {
    case '(':
        return open_bracket;
        break;
    case ')':
        return close_bracket;
        break;
    case '[':
        return open_square_bracket;
        break;
    case ']':
        return close_square_bracket;
        break;
    }
}
 
int main() {
    ifstream fin;
    ofstream fout;
    fin.open("brackets.in");
    fout.open("brackets.out");
    stack bracket_stack;
    long num;
    string bracket_line, answer;
    bool first_writing = true, correct_bracket_row;
    brackets num1, num2;
    while (fin >> bracket_line) {
        bracket_stack.top_free = 0;
        correct_bracket_row = true;
        for (int i = 0; i < bracket_line.size(); i++) {
            if (bracket_stack.top_free > 0) {
                num1 = from_bracket_to_name(bracket_stack.line[bracket_stack.top_free - 1]);
                num2 = from_bracket_to_name(bracket_line[i]);
                if ((num1 * num2 == -4) && (num2 < 0)) {
                    bracket_stack.extract();
                }
                else {
                    bracket_stack.push(bracket_line[i]);
                }
            }
            else {
                bracket_stack.push(bracket_line[i]);
            }
        }
        if (bracket_stack.top_free == 0) {
            answer = "YES";
        }
        else {
            answer = "NO";
        }
        if (first_writing) {
            fout << answer;
            first_writing = false;
        }
        else {
            fout << endl << answer;
        }
    }
    fin.close();
    fout.close();   
}
