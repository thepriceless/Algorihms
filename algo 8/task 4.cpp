#include<iostream>
#include<fstream>
#include<vector>
#include<string>
 
struct Element {
    int number;
    Element* next = nullptr;
};
 
 
struct list {
    Element* head = nullptr;
};
 
 
 
class Graph {
private:
    list* table;
    int* colors;
    int* parents;
    int* components;
    int current_component_number;
public:
    int dots, sticks, start, end;
    std::ifstream fin;
    std::ofstream fout;
    Graph() {
        fin.open("components.in");
        fin >> dots >> sticks;
        table = new list[dots];
        colors = new int[dots];
        parents = new int[dots];
        components = new int[dots];
        current_component_number = 1;
    }
    void read_stick_data() {
        for (int i = 0; i < sticks; i++) {
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
                current_component_number++;
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
        components[start_point] = current_component_number;
    }
 
    void printer() {
        std::cout << std::endl;
        for (int i = 0; i < dots; i++) {
            Element* tmp = new Element;
            tmp = table[i].head;
            while (tmp) {
                std::cout << tmp->number;
                tmp = tmp->next;
            }
            std::cout << std::endl;
        }
    }
 
    ~Graph() {
        fout.open("components.out");
        fout << current_component_number - 1 << std::endl;
        for (int i = 0; i < dots; i++) {
            fout << components[i] << " ";
        }
    }
};
 
 
int main() {
    Graph graph;
    graph.read_stick_data();       
    graph.DFS();
}
