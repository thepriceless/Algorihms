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
    int* degree;
    int* colors;
    int* parents;
public:
    int dots, edges;
    std::ifstream fin;
    std::ofstream fout;
 
    Graph() {
        fin.open("input.txt");
        fin >> dots >> edges;
        table = new List[dots];
        colors = new int[dots];
        degree = new int[dots];
        for (int i = 0; i < dots; i++) { degree[i] = 0; }
        parents = new int[dots];
    }
 
    void Read_stick_data() {
        int start, end;
        for (int i = 0; i < edges; i++) {
            fin >> start >> end;
            degree[start - 1]++;
            degree[end - 1]++;
            /*if (table[start - 1].head) {
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
            }*/
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
            if (!degree[temp->number]) {
                found_losing = true;
            }
            temp = temp->next;
        }
        degree[start_point] = found_losing;
        delete temp;
    }
 
    ~Graph() {
        fout.open("output.txt");
        for (int i = 0; i < dots; i++) { fout << degree[i] << " "; }
 
        delete table;
        delete colors;
        delete degree;
        delete parents;
    }
};
 
 
int main() {
    Graph graph;
    graph.Read_stick_data();
}
