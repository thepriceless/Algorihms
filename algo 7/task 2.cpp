#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
 
using namespace std;
 
struct Dot {
    long key;
    long depth;
    long left_height = 0;
    long right_height = 0;
    long order = 0;
    Dot* left = nullptr;
    Dot* right = nullptr;
    Dot* parent = nullptr;
};
 
struct Binary_tree {
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
 
    void left_turn(Dot* disbalanced) {
        Dot* parent_dot = disbalanced->parent;
        bool right, headd = false;
        if (parent_dot) {
            if (parent_dot->right == disbalanced) { right = true; }
            else { right = false; }
        }
        else { headd = true; }
        if (disbalanced->right->right_height - disbalanced->right->left_height != -1) {
            Dot* temp = disbalanced;
            disbalanced = disbalanced->right;
            temp->right = disbalanced->left;
            if (temp->right) { temp->right->parent = temp; }
            disbalanced->left = temp;
            disbalanced->left->parent = disbalanced;
            disbalanced->parent = parent_dot;
            if (disbalanced->left->right) { disbalanced->left->right_height = max(disbalanced->left->right->right_height, disbalanced->left->right->left_height) + 1; }
            else { disbalanced->left->right_height = 0; }
            if (disbalanced->left->left) { disbalanced->left->left_height = max(disbalanced->left->left->right_height, disbalanced->left->left->left_height) + 1; }
            else { disbalanced->left->left_height = 0; }
        }
        else {
            Dot* tempA = disbalanced;
            Dot* tempC = disbalanced->right->left;
            disbalanced->right->left = tempC->right;
            tempC->right = disbalanced->right;
            tempA->right = tempC->left;
            tempC->left = tempA;
            disbalanced = tempC;
            if (tempA->right) { tempA->right->parent = tempA; }
            if (disbalanced->right->left) { disbalanced->right->left->parent = disbalanced->right; }
            tempA->parent = disbalanced;
            if (disbalanced->right) { disbalanced->right->parent = disbalanced; }
            disbalanced->parent = parent_dot;
            if (disbalanced->right->right) { disbalanced->right->right_height = max(disbalanced->right->right->right_height, disbalanced->right->right->left_height) + 1; }
            else { disbalanced->right->right_height = 0; }
            if (disbalanced->right->left) { disbalanced->right->left_height = max(disbalanced->right->left->right_height, disbalanced->right->left->left_height) + 1; }
            else { disbalanced->right->left_height = 0; }
            if (disbalanced->left->right) { disbalanced->left->right_height = max(disbalanced->left->right->right_height, disbalanced->left->right->left_height) + 1; }
            else { disbalanced->left->right_height = 0; }
            if (disbalanced->left->left) { disbalanced->left->left_height = max(disbalanced->left->left->right_height, disbalanced->left->left->left_height) + 1; }
            else { disbalanced->left->left_height = 0; }
        }
        if (headd) { head = disbalanced; }
        else {
            if (right) { parent_dot->right = disbalanced; }
            else { parent_dot->left = disbalanced; }
        }
        disbalanced->right_height = max(disbalanced->right->right_height, disbalanced->right->left_height) + 1;
        disbalanced->left_height = max(disbalanced->left->right_height, disbalanced->left->left_height) + 1;
        if (!headd) {
            if (disbalanced->parent->right == disbalanced) { disbalanced->parent->right_height = max(disbalanced->right_height, disbalanced->left_height) + 1; }
            else { disbalanced->parent->left_height = max(disbalanced->right_height, disbalanced->left_height) + 1; }
        }
    }
 
    void right_turn(Dot* disbalanced) {
        Dot* parent_dot = disbalanced->parent;
        bool right, headd = false;
        if (parent_dot) {
            if (parent_dot->right == disbalanced) { right = true; }
            else { right = false; }
        }
        else { headd = true; }
        if (disbalanced->left->right_height - disbalanced->left->left_height != 1) {
            Dot* temp = disbalanced;
            disbalanced = disbalanced->left;
            temp->left = disbalanced->right;
            if (temp->left) { temp->left->parent = temp; }
            disbalanced->right = temp;
            disbalanced->right->parent = disbalanced;
            disbalanced->parent = parent_dot;
            if (disbalanced->right->right) { disbalanced->right->right_height = max(disbalanced->right->right->right_height, disbalanced->right->right->left_height) + 1; }
            else { disbalanced->right->right_height = 0; }
            if (disbalanced->right->left) { disbalanced->right->left_height = max(disbalanced->right->left->right_height, disbalanced->right->left->left_height) + 1; }
            else { disbalanced->right->left_height = 0; }
        }
        else {
            Dot* tempA = disbalanced;
            Dot* tempC = disbalanced->left->right;
            disbalanced->left->right = tempC->left;
            tempC->left = disbalanced->left;
            tempA->left = tempC->right;
            tempC->right = tempA;
            disbalanced = tempC;
            if (tempA->left) { tempA->right->parent = tempA; }
            if (disbalanced->left->right) { disbalanced->left->right->parent = disbalanced->left; }
            tempA->parent = disbalanced;
            if (disbalanced->left) { disbalanced->left->parent = disbalanced; }
            disbalanced->parent = nullptr;
            if (disbalanced->right->right) { disbalanced->right->right_height = max(disbalanced->right->right->right_height, disbalanced->right->right->left_height) + 1; }
            else { disbalanced->right->right_height = 0; }
            if (disbalanced->right->left) { disbalanced->right->left_height = max(disbalanced->right->left->right_height, disbalanced->right->left->left_height) + 1; }
            else { disbalanced->right->left_height = 0; }
            if (disbalanced->left->right) { disbalanced->left->right_height = max(disbalanced->left->right->right_height, disbalanced->left->right->left_height) + 1; }
            else { disbalanced->left->right_height = 0; }
            if (disbalanced->left->left) { disbalanced->left->left_height = max(disbalanced->left->left->right_height, disbalanced->left->left->left_height) + 1; }
            else { disbalanced->left->left_height = 0; }
        }
        if (headd) { head = disbalanced; }
        else {
            if (right) { parent_dot->right = disbalanced; }
            else { parent_dot->left = disbalanced; }
        }
        disbalanced->right_height = max(disbalanced->right->right_height, disbalanced->right->left_height) + 1;
        disbalanced->left_height = max(disbalanced->left->right_height, disbalanced->left->left_height) + 1;
        if (!headd) {
            if (disbalanced->parent->right == disbalanced) { disbalanced->parent->right_height = max(disbalanced->right_height, disbalanced->left_height) + 1; }
            else { disbalanced->parent->left_height = max(disbalanced->right_height, disbalanced->left_height) + 1; }
        }
    }
 
    int cycle = 1;
    void left_sided_depth_first_search_w(Dot* now) {
        now->order = cycle;
        cycle++;
        if (now->left) {
            left_sided_depth_first_search_w(now->left);
        }
        if (now->right) {
            left_sided_depth_first_search_w(now->right);
        }
    }
 
    void left_sided_dfs_depth_change(Dot* now) {
        if (now->left) {
            now->left->depth = now->depth + 1;
            left_sided_depth_first_search_w(now->left);
        }
        if (now->right) {
            now->right->depth = now->depth + 1;
            left_sided_depth_first_search_w(now->right);
        }
    }
};
 
void left_sided_depth_first_search_fout(Dot* now, ofstream &output) {
    output << now->key << " ";
    if (now->left) { output << now->left->order << " "; }
    else { output << 0 << " "; }
    if (now->right) { output << now->right->order << "\n"; }
    else { output << 0 << "\n"; }
    if (now->left) {
        left_sided_depth_first_search_fout(now->left, output);
    }
    if (now->right) {
        left_sided_depth_first_search_fout(now->right, output);
    }
}
 
void height_count(vector<Dot*> &numbers, int amount) {
    Dot* g;
    for (int i = 0; i < amount; i++) {
        if (numbers[i]->right == nullptr && numbers[i]->left == nullptr) {
            g = numbers[i];
            while (g->parent) {
                if (g->parent->right == g) { g->parent->right_height = max(numbers[i]->depth - g->parent->depth, g->parent->right_height); }
                else { g->parent->left_height = max(numbers[i]->depth - g->parent->depth, g->parent->left_height); }
                g = g->parent;
            }
        }
    }
}
 
int main() {
    ifstream fin;
    ofstream fout;
    fin.open("rotation.in");
    fout.open("rotation.out");
    Binary_tree tree;
    Dot* parent_return;
    Dot* ins;
    long number, n, in, left_child, right_child;
    fin >> n;
    Dot** parents = new Dot*[n];
    vector<Dot*> numbers;
    for (int i = 0; i < n; i++) {
        fin >> number >> left_child >> right_child;
        if (i == 0) { tree.insertion(tree.head, number, &parent_return); }
        else {
            tree.insertion(parents[i], number, &parent_return);
        }
        if (left_child) { parents[left_child - 1] = parent_return; }
        if (right_child) { parents[right_child - 1] = parent_return; }
        numbers.push_back(parent_return);
    }
    height_count(numbers, n);
    fout << n << "\n";
    tree.left_turn(tree.head);
    tree.left_sided_depth_first_search_w(tree.head);
    left_sided_depth_first_search_fout(tree.head, fout);
    fin.close();
    fout.close();
}
