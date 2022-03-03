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
public:
    List* table;
    List* reversed_table;
    int* colors;
    int* comp_colors;
    int* parents;
    int* times_out;
    bool cycle = false;
    std::vector<int> vertices;
    int dots, edges, start, end, component = 1;
    std::ifstream fin;
    std::ofstream fout;
 
    Graph() {
        fin.open("cond.in");
        fin >> dots >> edges;
        table = new List[dots];
        reversed_table = new List[dots];
        colors = new int[dots];
        comp_colors = new int[dots];
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
            if (reversed_table[end - 1].head) {
                Element* temp = reversed_table[end - 1].head;
                Element* dot = new Element;
                dot->number = start - 1;
                dot->next = temp;
                reversed_table[end - 1].head = dot;
            }
            else {
                reversed_table[end - 1].head = new Element;
                reversed_table[end - 1].head->number = start - 1;
                reversed_table[end - 1].head->next = nullptr;
            }
        }
    }
 
    void DFS(int start, const List* table) {
        for (int i = start; i < dots; i++) {
            colors[i] = 0;
            parents[i] = -1;
        }
        for (int i = start; i < dots; i++) {
            if (colors[i] == 0) {
                DFS_visit(i, table);
            }
        }
    }
 
    void DFS_visit(int start_point, const List* table, bool condencation = false) {
        if (condencation) { comp_colors[start_point] = component; }
        colors[start_point] = 1;
        Element* temp = new Element;
        temp = table[start_point].head;
        while (temp) {
            if (colors[temp->number] == 0) {
                parents[temp->number] = start_point;
                DFS_visit(temp->number, table, condencation);
            }
            temp = temp->next;
        }
        colors[start_point] = 2;
        vertices.push_back(start_point);
    }
 
    void Clear_DFS_results() {
        for (int i = 0; i < dots; i++) {
            colors[i] = 0;
            comp_colors[i] = -1;
            parents[i] = -1;
        }
    }
 
    void Condensation() {
        for (int i = dots - 1; i >= 0; i--) {
            if (comp_colors[vertices[i]] == -1) {
                DFS_visit(vertices[i], reversed_table, true);
                component++;
            }
        }
    }
 
    ~Graph() {
        fout.open("cond.out");
        fout << component - 1 << '\n';
        for (int i = 0; i < dots; i++) {
            fout << comp_colors[i] << " ";
        }
        delete table;
        delete reversed_table;
        delete colors;
        delete comp_colors;
        delete parents;
        delete times_out;
    }
};
 
 
int main() {
    Graph graph;
    graph.Read_stick_data();
    graph.DFS(0, graph.table);
    graph.Clear_DFS_results();
    graph.Condensation();
}
