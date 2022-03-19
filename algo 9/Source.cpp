#include<iostream>
#include<fstream>
#include<vector>
#include<string>

struct Element {
    int number;
    Element* next = nullptr;
};


struct List {
    Element* head = nullptr;
};


class Graph {
private:
    List* table;
    bool* winning_vertice;
    int* colors;
    int* parents;
public:
    int dots, edges, game_start_point;
    std::ifstream fin;
    std::ofstream fout;

    Graph() {
        fin.open("game.in");
        fin >> dots >> edges >> game_start_point;
        table = new List[dots];
        colors = new int[dots];
        winning_vertice = new bool[dots];
        parents = new int[dots];
    }

    void Read_stick_data() {
        int start, end;
        for (int i = 0; i < edges; i++) {
            fin >> start >> end;
            if (table[start - 1].head) {
                Element* temp = table[start - 1].head;
                Element* dot = new Element;
                dot->number = end - 1;
                dot->next = temp;
                table[start - 1].head = dot;
            }
            else {
                table[start - 1].head = new Element;
                table[start - 1].head->number = end - 1;
                table[start - 1].head->next = nullptr;
            }
        }
    }

    void DFS() {
        for (int i = 0; i < dots; i++) {
            colors[i] = 0;
            parents[i] = -1;
        }
        for (int i = 0; i < dots; i++) {
            if (colors[i] == 0) {
                DFS_visit(i);
            }
        }
    }

    void DFS_visit(int start_point) {
        colors[start_point] = 1;
        Element* temp = new Element;
        temp = table[start_point].head;
        while (temp) {
            if (colors[temp->number] == 0) {
                parents[temp->number] = start_point;
                DFS_visit(temp->number);
            }
            temp = temp->next;
        }
        colors[start_point] = 2;
        bool found_losing = false;
        temp = table[start_point].head;
        while (!found_losing && temp) {
            if (!winning_vertice[temp->number]) {
                found_losing = true;
            }
            temp = temp->next;
        }
        winning_vertice[start_point] = found_losing;
        delete temp;
    }

    ~Graph() {
        fout.open("game.out");
        if (winning_vertice[game_start_point - 1]) { fout << "First player wins"; }
        else { fout << "Second player wins"; }

        delete table;
        delete colors;
        delete winning_vertice;
        delete parents;
    }
};


int main() {
    Graph graph;
    graph.Read_stick_data();
    graph.DFS();
}