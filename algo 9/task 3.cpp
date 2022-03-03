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
    int* bp_colors;
    int* parents;
    int* times_out;
    bool cycle = false, bipartite = true;
    std::vector<int> vertices;
public:
    int dots, edges, start, end;
    std::ifstream fin;
    std::ofstream fout;
    //int to_draw;
 
    Graph() {
        fin.open("bipartite.in");
        fin >> dots >> edges;
        table = new List[dots];
        colors = new int[dots];
        bp_colors = new int[dots];
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
            if (table[end - 1].head) {
                Element* temp = table[end - 1].head;
                Element* dot = new Element;
                dot->number = start - 1;
                dot->next = temp;
                table[end - 1].head = dot;
            }
            else {
                table[end - 1].head = new Element;
                table[end - 1].head->number = start - 1;
                table[end - 1].head->next = nullptr;
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
        if (bp_colors[parents[start_point]] == 1) {
            if (bp_colors[start_point] == 1) { bipartite = false; }
            else { bp_colors[start_point] = 2; }
        }
        else {
            if (bp_colors[start_point] == 2) { bipartite = false; }
            else { bp_colors[start_point] = 1; }
        }
        Element* temp = new Element;
        temp = table[start_point].head;
        while (temp) {
            if (colors[temp->number] == 0) {
                parents[temp->number] = start_point;
                DFS_visit(temp->number);
            }
            else if (colors[temp->number] == 1) {
                if (bp_colors[start_point] == bp_colors[temp->number]) { bipartite = false; }
            }
            temp = temp->next;
        }
        colors[start_point] = 2;
    }
 
    ~Graph() {
        fout.open("bipartite.out");
        if (bipartite) {
            fout << "YES\n";
        }
        else {
            fout << "NO\n";
        }
 
        delete table;
        delete colors;
        delete bp_colors;
        delete parents;
        delete times_out;
    }
};
 
 
int main() {
    Graph graph;
    graph.Read_stick_data();
    graph.DFS();
}
