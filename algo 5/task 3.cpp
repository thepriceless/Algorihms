#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
 
using namespace std;
 
struct Dot {
    long key;
    Dot* left = nullptr;
    Dot* right = nullptr;
    Dot* parent = nullptr;
};
 
struct binary_tree {
    Dot* head = nullptr;
 
    void insertion(Dot* x, long z) {
        if (head == nullptr) {
            head = new Dot;
            head->key = z;
            return;
        }
        if (x->key <= z) {
            if (x->right) {
                insertion(x->right, z);
            }
            else {
                x->right = new Dot;
                x->right->key = z;
                x->right->parent = x;
            }
        }
        else {
            if (x->left) {
                insertion(x->left, z);
            }
            else {
                x->left = new Dot;
                x->left->key = z;
                x->left->parent = x;
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
    fin.open("bstsimple.in");
    fout.open("bstsimple.out");
    binary_tree tree;
    string command;
    long number;
    Dot* extra_dot, tmp1, tmp2;
    bool flag;
    while (fin >> command && fin >> number) {
        if (command == "insert") {
            if (tree.search(tree.head, number) == nullptr) {
                tree.insertion(tree.head, number);
            }
        }
        else if (command == "delete") {
            if (tree.search(tree.head, number) != nullptr) {
                tree.deletion(number);
            }
        }
        else if (command == "exists") {
            if (tree.search(tree.head, number) != nullptr) {
                fout << "true\n";
            }
            else {
                fout << "false\n";
            }
        }
        else if (command == "prev") {
            flag = false;
            if (tree.search(tree.head, number) == nullptr) {
                tree.insertion(tree.head, number);
                flag = true;
            }
            Dot* tmp1 = tree.search(tree.head, number);
            Dot* tmp2 = tree.minimum(tree.head);
            if (tmp1 == tmp2) {
                fout << "none\n";
            }
            else {
                extra_dot = tree.prev(number);
                fout << extra_dot->key << '\n';
            }
            if (flag) {
                tree.deletion(number);
            }
        }
        else {
            flag = false;
            if (tree.search(tree.head, number) == nullptr) {
                tree.insertion(tree.head, number);
                flag = true;
            }
            Dot* tmp1 = tree.search(tree.head, number);
            Dot* tmp2 = tree.maximum(tree.head);
            if (tmp1 == tmp2) {
                fout << "none\n";
            }
            else {
                extra_dot = tree.next(number);
                fout << extra_dot->key << '\n';
            }
            if (flag) {
                tree.deletion(number);
            }
        }
    }
    fin.close();
    fout.close();
}
