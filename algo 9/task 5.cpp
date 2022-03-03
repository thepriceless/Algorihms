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
    int* colors;
    int* parents;
    std::vector<int> vertices;
public:
    int dots, edges, start, end;
    std::ifstream fin;
    std::ofstream fout;
 
    Graph() {
        fin.open("hamiltonian.in");
        fin >> dots >> edges;
        table = new List[dots];
        colors = new int[dots];
        parents = new int[dots];
    }
 
    void Read_stick_data() {
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
        vertices.push_back(start_point);
        delete temp;
    }
 
    ~Graph() {
        fout.open("hamiltonian.out");
        Element* temp = new Element;
        bool found = true;
        for (int i = dots - 2; i >= 0; i--) {
            found = false;
            temp = table[vertices[i + 1]].head;
            while (temp) {
                if (temp->number == vertices[i]) {
                    found = true;
                    break;
                }
                temp = temp->next;
            }
            if (!found) {
                fout << "NO";
                break;
            }
        }
        if (found) { fout << "YES"; }
        delete temp;
        delete table;
        delete colors;
        delete parents;
    }
};
 
 
int main() {
    Graph graph;
    graph.Read_stick_data();
    graph.DFS();
}
