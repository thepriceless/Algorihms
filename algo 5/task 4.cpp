#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <string>
 
using namespace std;
 
struct queue_struct {
    vector <uint16_t> line;
    uint16_t registers[26];
    map <string, int> labels;
    int first = 0, last = -1;
    bool stopper = false;
 
    void put(uint16_t z) {
        last++;
        line.push_back(z);
    }
 
    uint16_t get() {
        uint16_t temp = line[first];
        first++;
        return temp;
    }
 
    void add() {
        uint16_t tmp1 = get();
        uint16_t tmp2 = get();
        uint16_t result = tmp1 + tmp2;
        put(result);
    }
 
    void sub() {
        uint16_t tmp1 = get();
        uint16_t tmp2 = get();
        uint16_t result = tmp1 - tmp2;
        put(result);
    }
 
    void mul() {
        uint16_t tmp1 = get();
        uint16_t tmp2 = get();
        uint16_t result = tmp1 * tmp2;
        put(result);
    }
 
    void div() {
        uint16_t tmp1 = get();
        uint16_t tmp2 = get();
        uint16_t result;
        if (tmp2 != 0) {
            result = tmp1 / tmp2;
        }
        else {
            result = 0;
        }
        put(result);
    }
 
    void mod() {
        uint16_t tmp1 = get();
        uint16_t tmp2 = get();
        uint16_t result;
        if (tmp2 != 0) {
            result = tmp1 % tmp2;
        }
        else {
            result = 0;
        }
        put(result);
    }
 
    void set_reg(char a) {
        uint16_t tmp1 = get();
        int reg = a;
        registers[reg - 97] = tmp1;
    }
 
    void from_reg_to_queue(char a) {
        int reg = a;
        put(registers[reg - 97]);
    }
 
    uint16_t get_reg(char a) {
        int reg = a;
        return registers[reg - 97];
    }
 
    void add_label(string s, int command_number) {
        labels[s] = command_number;
    }
 
    int change_command_by_label(string s) {
        map <string, int> ::iterator it;
        it = labels.find(s);
        int tmp1 = it->second;
        return tmp1;
    }   
};
 
int main() {
    ifstream fin;
    ofstream fout;
    fin.open("quack.in");
    fout.open("quack.out");
    queue_struct queue;
    int now_com = 0;
    string command;
    vector <string> commands;
    while (fin >> command) {
        commands.push_back(command);
        if (command[0] == ':') {
            int length = command.length();
            string label_name = command.substr(1, length - 1);
            queue.add_label(label_name, now_com);
        }
        now_com++;
    }
    now_com = 0;
    while (now_com < commands.size() && !queue.stopper) {
        command = commands[now_com];
        //fout << command << " result ";
        switch (command[0])
        {
        case '+':
            queue.add();
            now_com++;
            break;
        case '-':
            queue.sub();
            now_com++;
            break;
        case '*':
            queue.mul();
            now_com++;
            break;
        case '/':
            queue.div();
            now_com++;
            break;
        case '%':
            queue.mod();
            now_com++;
            break;
        case '>':
            queue.set_reg(command[1]);
            now_com++;
            break;
        case '<':
            queue.from_reg_to_queue(command[1]);
            now_com++;
            break;
        case 'P':
        {
            uint16_t temp;
            if (command.length() == 1) {
                temp = queue.get();
            }
            else {
                temp = queue.get_reg(command[1]);
            }
            fout << temp << '\n';
            now_com++;
        }
            break;
        case ':':
            now_com++;
            break;
        case 'J':
        {
            int length = command.length();
            string label_name = command.substr(1, length - 1);
            now_com = queue.change_command_by_label(label_name);
        }
            break;
        case 'C':
        {
            uint16_t temp;
            if (command.length() == 1) {
                temp = queue.get();
            }
            else {
                char reg = command[1];
                temp = queue.get_reg(reg);
            }
            char sym = (temp % 256);
            fout << sym;
            now_com++;
        }
            break;
        case 'Z':
        {
            char reg = command[1];
            if (queue.get_reg(reg) == 0) {
                int length = command.length();
                string label_name = command.substr(2, length - 2);
                now_com = queue.change_command_by_label(label_name);
            }
            else {
                now_com++;
            }
        }
            break;
        case 'E':
        {
            char reg1 = command[1];
            char reg2 = command[2];
            uint16_t temp1 = queue.get_reg(reg1);
            uint16_t temp2 = queue.get_reg(reg2);
            if (temp1 == temp2) {
                int length = command.length();
                string label_name = command.substr(3, length - 3);
                now_com = queue.change_command_by_label(label_name);
            }
            else {
                now_com++;
            }
        }
            break;
        case 'G':
        {
            char reg1 = command[1];
            char reg2 = command[2];
            uint16_t temp1 = queue.get_reg(reg1);
            uint16_t temp2 = queue.get_reg(reg2);
            if (temp1 > temp2) {
                int length = command.length();
                string label_name = command.substr(3, length - 3);
                now_com = queue.change_command_by_label(label_name);
            }
            else {
                now_com++;
            }
        }
            break;
        case 'Q':
            queue.stopper = true;
            break;
        default:
        {
            uint16_t temp = stoi(command);
            queue.put(temp);
            now_com++;
        }
            break;
        }
    }
    fin.close();
    fout.close();
}
