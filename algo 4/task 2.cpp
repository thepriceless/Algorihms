#include <fstream>
#include <cstdlib>
#include <string>
 
using namespace std;
 
struct queue {
    long* numbers = (long*) malloc(1000000 * sizeof(long));
    long next = 0, last_free = 0;
    void push(long elem) {
        numbers[last_free++] = elem;
    }
    long extract() {
        return numbers[next++];
    }
};
 
int main() {
    ifstream fin;
    ofstream fout;
    fin.open("queue.in");
    fout.open("queue.out");
    queue number_queue;
    long n, num;
    char command;
    bool first_writing = true;
    fin >> n;
    for (long i = 0; i < n; i++) {
        fin >> command;
        if (command == '+') {
            fin >> num;
            number_queue.push(num);
        }
        else {
            if (first_writing) {
                fout << number_queue.extract();
                first_writing = false;
            }
            else {
                fout << endl << number_queue.extract();
            }
        }
    }
    fin.close();
    fout.close();
}
