#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
 
using namespace std;
 
struct Dot {
    long key;
    long left_height = 0;
    long right_height = 0;
    long depth;
    Dot* left = nullptr;
    Dot* right = nullptr;
    Dot* parent = nullptr;
};
 
struct Number_and_Pointer {
    long c;
    Dot* ptr;
};
 
struct binary_tree {
    Dot* head = nullptr;
    void insertion(Dot* x, long z, Dot** p) {
        if (head == nullptr) {
            head = new Dot;
            head->key = z;
            head->depth = 0;
            *p = head;
            return;
        }
        if (x->key <= z) {
            if (x->right) {
                insertion(x->right, z, p);
            }
            else {
                x->right = new Dot;
                x->right->key = z;
                x->right->parent = x;
                x->right->depth = x->depth + 1;
                *p = x->right;
                /*Dot* temp = x->right;
                if (temp->parent->left == nullptr) {
                    while (temp->parent) {
                        if (temp->parent->right == temp) {
                            temp->parent->right_height = max(temp->left_height, temp->right_height) + 1;
                        }
                        else {
                            temp->parent->left_height = max(temp->left_height, temp->right_height) + 1;
                        }
                        temp = temp->parent;
                    }
                }
                else { temp->parent->right_height++; }*/
            }
        }
        else {
            if (x->left) {
                insertion(x->left, z, p);
            }
            else {
                x->left = new Dot;
                x->left->key = z;
                x->left->parent = x;
                x->left->depth = x->depth + 1;
                *p = x->left;
                /*Dot* temp = x->left;
                if (temp->parent->right == nullptr) {
                    while (temp->parent) {
                        if (temp->parent->right == temp) {
                            temp->parent->right_height = max(temp->left_height, temp->right_height) + 1;
                        }
                        else {
                            temp->parent->left_height = max(temp->left_height, temp->right_height) + 1;
                        }
                        temp = temp->parent;
                    }
                }
                else { temp->parent->left_height++; }*/
            }
        }
    }
 
    Dot* search(Dot* x, long z) {
        while (x != nullptr && x->key != z) {
            if (x->key <= z) {
                x = x->right;
            }
            else {
                x = x->left;
            }
        }
        return x;
    }
 
    Dot* minimum(Dot* x) {
        while (x->left != nullptr) {
            x = x->left;
        }
        return x;
    }
 
    Dot* maximum(Dot* x) {
        while (x->right != nullptr) {
            x = x->right;
        }
        return x;
    }
 
    Dot* next(long z) {
        Dot* temp = search(head, z);
        if (temp->right != nullptr) {
            return minimum(temp->right);
        }
        while (temp->parent->right == temp && temp->parent != nullptr) {
            temp = temp->parent;
        }
        return temp->parent;
    }
 
    Dot* prev(long z) {
        Dot* temp = search(head, z);
        if (temp->left != nullptr) {
            return maximum(temp->left);
        }
        while (temp->parent->left == temp && temp->parent != nullptr) {
            temp = temp->parent;
        }
        return temp->parent;
    }
 
    void deletion(long z) {
        Dot* temp = search(head, z);
        if (!(temp->left) && !(temp->right)) {
            if (temp->parent != nullptr) {
                if (temp->parent->left == temp) {
                    temp->parent->left = nullptr;
                }
                else {
                    temp->parent->right = nullptr;
                }
                temp->parent = nullptr;
            }
            else {
                head = nullptr;
            }
        }
        else if (temp->right == nullptr) {
            if (temp->parent != nullptr) {
                if (temp->parent->left == temp) {
                    temp->parent->left = temp->left;
                }
                else {
                    temp->parent->right = temp->left;
                }
                temp->left->parent = temp->parent;
            }
            else {
                head = temp->left;
                temp->left->parent = nullptr;
            }
        }
        else if (temp->left == nullptr) {
            if (temp->parent != nullptr) {
                if (temp->parent->left == temp) {
                    temp->parent->left = temp->right;
                }
                else {
                    temp->parent->right = temp->right;
                }
                temp->right->parent = temp->parent;
            }
            else {
                head = temp->right;
                temp->right->parent = nullptr;
            }
        }
        else {
            Dot* temp = next(z);
            Dot* to_delete = search(head, z);
            long y = temp->key;
            deletion(temp->key);
            to_delete->key = y;
        }
    }
};
 
int main() {
    ifstream fin;
    ofstream fout;
    fin.open("balance.in");
    fout.open("balance.out");
    binary_tree tree;
    Dot* parent_return;
    Number_and_Pointer rem;
    long number, n, left_child, right_child;
    fin >> n;
    Dot** parents = new Dot*[n];
    vector<Number_and_Pointer> numbers;
    for (int i = 0; i < n; i++) {
        fin >> number >> left_child >> right_child;
        if (i == 0) { tree.insertion(tree.head, number, &parent_return); }
        else {
            tree.insertion(parents[i], number, &parent_return);
        }
        if (left_child) { parents[left_child - 1] = parent_return; }
        if (right_child) { parents[right_child - 1] = parent_return; }
        rem.c = number;
        rem.ptr = parent_return;
        numbers.push_back(rem);
    }
    Dot* g;
    for (int i = 0; i < n; i++) {
        if (numbers[i].ptr->right == nullptr && numbers[i].ptr->left == nullptr) {
            g = numbers[i].ptr;
            while (g->parent) {
                if (g->parent->right == g) { g->parent->right_height = max(numbers[i].ptr->depth - g->parent->depth, g->parent->right_height); }
                else { g->parent->left_height = max(numbers[i].ptr->depth - g->parent->depth, g->parent->left_height); }
                g = g->parent;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        fout << numbers[i].ptr->right_height - numbers[i].ptr->left_height << "\n";
    }
    fin.close();
    fout.close();
}
