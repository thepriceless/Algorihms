#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
 
using namespace std;
 
struct Dot {
    long key;
    long left;
    long right;
    long parent;
    long lowest;
    long largest;
};
 
int main() {
    ifstream fin;
    ofstream fout;
    fin.open("check.in");
    fout.open("check.out");
    long n, key, left, right, j;
    int current_height, max_height = 0;
    string answer = "YES";
    fin >> n;
    struct Dot* tree = (Dot*)malloc((n + 1) * sizeof(Dot));
    if (n >= 1) {
        tree[1].parent = 0;
        tree[0].lowest = LONG_MIN;
        tree[0].largest = LONG_MAX;
    }
    long parent_ind;
    for (long i = 1; i < n + 1; i++) {
        fin >> key >> left >> right;
        tree[i].key = key;
        tree[i].right = right;
        tree[i].left = left;
        if (right) {
            tree[right].parent = i;
        }
        if (left) {
            tree[left].parent = i;
        }
        parent_ind = tree[i].parent;
        tree[i].lowest = tree[parent_ind].lowest;
        tree[i].largest = tree[parent_ind].largest;
        if (tree[parent_ind].right == i) {
            tree[i].lowest = tree[parent_ind].key;
        }
        if (tree[parent_ind].left == i) {
            tree[i].largest = tree[parent_ind].key;
        }
        if (tree[i].key <= tree[i].lowest || tree[i].key >= tree[i].largest) { answer = "NO"; }
        /*for (int p = 1; p <= i; p++) {
            cout << "key: " << tree[p].key << " left-c: " << tree[p].left << " right-c: " << tree[p].right << " parent: " << tree[p].parent << " lowest: " << tree[p].lowest << " largest: " << tree[p].largest << "\n";
        }
        cout << '\n';*/
 
 
    }
    /*for (int p = 1; p <= n; p++) {
        cout << "key: " << tree[p].key << " left-c: " << tree[p].left << " right-c: " << tree[p].right << " parent: " << tree[p].parent << " lowest: " << tree[p].lowest << " largest: " << tree[p].largest << "\n";
    }*/
    fout << answer;
    fin.close();
    fout.close();
}
