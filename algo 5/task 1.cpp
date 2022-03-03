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
};
 
int main() {
    ifstream fin;
    ofstream fout;
    fin.open("height.in");
    fout.open("height.out");
    long n, key, left, right, j;
    int current_height, max_height = 0;
    fin >> n;
    struct Dot* tree = (struct Dot*)malloc((n + 1) * sizeof(struct Dot));
    if (n >= 1) {
        tree[1].parent = 0;
    }
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
        /*for (int p = 1; p <= i; p++) {
            cout << "key: " << tree[p].key << " left-c: " << tree[p].left << " right-c: " << tree[p].right << " parent: " << tree[p].parent << "\n";
        }
        cout << '\n';*/
        if ((!left) && (!right)) {
            current_height = 1;
            j = i;
            while (tree[j].parent) {
                current_height++;
                j = tree[j].parent;
            }
            max_height = max(max_height, current_height);
        }
    }
    fout << max_height;
    fin.close();
    fout.close();
}
