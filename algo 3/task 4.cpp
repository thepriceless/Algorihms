#include <iostream>
#include <fstream>
#include <string>
#include <vector>
 
using namespace std;
 
long heap_size;
 
long left_child(long k) {
    return 2 * k + 1;
}
 
long right_child(long k) {
    return 2 * k + 2;
}
 
long parent(long k) {
    return (k - 1) / 2;
}
 
void min_heapify(vector<long>& A, long i) {
    long smallest;
    long left = left_child(i), right = right_child(i);
    if ((left < heap_size) && (A[left] < A[i])) {
        smallest = left;
    }
    else {
        smallest = i;
    }
    if ((right < heap_size) && (A[right] < A[smallest])) {
        smallest = right;
    }
    if (smallest != i) {
        swap(A[smallest], A[i]);
        min_heapify(A, smallest);
    }
}
 
void build_heap(vector<long>& A) {
    heap_size = A.size();
    for (long i = heap_size / 2 - 1; i > -1; -1) {
        min_heapify(A, i);
    }
}
 
string heap_extract_min(vector<long>& A) {
    long min_elem;
    if (heap_size < 1) {
        return "*";
    }
    min_elem = A[0];
    A[0] = A[heap_size - 1];
    heap_size--;
    min_heapify(A, 0);
    return to_string(min_elem);
}
 
void decrease_key(vector<long>& A, long ind, long key) {
    if (key <= A[ind]) {
        A[ind] = key;
        while ((ind > 0) && (A[parent(ind)] > A[ind])) {
            swap(A[parent(ind)], A[ind]);
            ind = parent(ind);
        }
    }
}
 
void insert_key(vector<long>& A, long key) {
    heap_size++;
    if (heap_size - 1 < A.size()) {
        A[heap_size - 1] = LONG_MAX;
    }
    else {
        A.push_back(LONG_MAX);
    }
    decrease_key(A, heap_size - 1, key);
}
 
int main() {
    ofstream fout;
    ifstream fin;
    fout.open("priorityqueue.out");
    fin.open("priorityqueue.in");
    string command;
    int number, index;
    vector<long> queue;
    vector<long> log;
    log.push_back(LONG_MIN);
    int already_written = 0;
    build_heap(queue);
    while (fin >> command) {
        if (command[0] == 'p') {
            fin >> number;
            insert_key(queue, number);
            log.push_back(number);
        }
        else {
            if (command[0] == 'e') {
                log.push_back(LONG_MAX);
                if (already_written) {
                    fout << '\n' << heap_extract_min(queue);
                }
                else {
                    fout << heap_extract_min(queue);
                    already_written = 1;
                }
            }
            else {
                fin >> index >> number;
                log.push_back(LONG_MAX);
                for (long j = 0; j < queue.size(); j++) {
                    if (queue[j] == log[index]) {
                        decrease_key(queue, j, number);
                        break;
                    }
                }
                log[index] = number;
            }
        }
        /*cout << queue.size() << endl;
        fout << "start" << heap_size << ' ';
        for (long p = 0; p < queue.size(); p++) {
            fout << queue[p] << ' ';
        }
        fout << endl;*/
    }
    fout.close();
    fin.close();
}
