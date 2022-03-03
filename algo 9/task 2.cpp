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
    int* components;
    int* times_out;
    bool cycle = false;
    std::vector<int> vertices;
public:
    int dots, edges, start, end;
    std::ifstream fin;
    std::ofstream fout;
    int current_time = 0;
 
    Graph() {
        fin.open("cycle.in");
        fin >> dots >> edges;
        table = new List[dots];
        colors = new int[dots];
        parents = new int[dots];
        times_out = new int[dots];
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
            else if (colors[temp->number] == 1 && parents[temp->number] != start_point) {
                if (!cycle) { Cycle_observer(temp->number); }
                cycle = true;
            }
            temp = temp->next;
        }
        colors[start_point] = 2;
    }
 
    void Cycle_observer(int start_point) {
        Element* temp = new Element;
        temp = table[start_point].head;
        while (temp) {
            if (colors[temp->number] == 1) {
                vertices.push_back(temp->number);
                if (temp->number == start_point) { 
                    break;
                }
                temp = table[temp->number].head;
            }
            else { temp = temp->next; }      
        }
    }
 
    ~Graph() {
        fout.open("cycle.out");
        if (cycle) {
            fout << "YES\n";
            for (int i = 0; i < vertices.size(); i++) {
                fout << vertices[i] + 1 << " ";
            }
        }
        else {
            fout << "NO\n";
        }
 
        delete table;
        delete colors;
        delete parents;
        delete times_out;
    }
};
 
 
int main() {
    Graph graph;
    graph.Read_stick_data();
    graph.DFS();
}
