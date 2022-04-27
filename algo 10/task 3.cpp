#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cmath>
#include<queue>
 
 
struct Element {
    int number;
    long long weight;
    Element* next = nullptr;
};
 
struct List {
    Element* head = nullptr;
};
 
struct PK {
    int parent;
    double key;
    bool used;
 
    void set_defaults() {
        parent = -1;
        key = LONG_MAX;
        used = false;
    }
};
 
struct Weighted_Vertex {
    int num;
    long long weight;
};
 
class Binary_Heap {
private:
    std::vector<Weighted_Vertex> vertices;
 
    int Left_Child(int parent) const { return 2 * parent + 1; }
 
    int Right_Child(int parent) const { return 2 * parent + 2; }
 
    int Parent(int child) const { return (child - 1) / 2; }
 
    void Heapify(int index) {
        int Smallest_Weight_Index, lc = Left_Child(index), rc = Right_Child(index);
        if ((lc < vertices.size()) && (vertices[lc].weight < vertices[index].weight)) { Smallest_Weight_Index = lc; }
        else { Smallest_Weight_Index = index; }
        if ((rc < vertices.size()) && (vertices[rc].weight < vertices[Smallest_Weight_Index].weight)) { Smallest_Weight_Index = rc; }
 
        if (Smallest_Weight_Index != index) {
            std::swap(vertices[Smallest_Weight_Index], vertices[index]);
            Heapify(Smallest_Weight_Index);
        }
    }
 
public:
    Binary_Heap(int size) {
        Weighted_Vertex temp;
        temp.num = 0;
        temp.weight = 0;
        vertices.push_back(temp);
        temp.weight = LONG_MAX;
        for (int i = 1; i < size; i++) {
            temp.num = i;
            vertices.push_back(temp);
        }
    }
 
    void Add_Vertex(Weighted_Vertex v) {
        vertices.push_back(v);
        int index = vertices.size() - 1;
        int parent = Parent(index);
 
        while (index > 0 && vertices[parent].weight > vertices[index].weight) {
            std::swap(vertices[parent], vertices[index]);
            index = parent;
            parent = Parent(index);
        }
    }
 
    Weighted_Vertex Extract() {
        Weighted_Vertex result = vertices[0];
        std::swap(vertices[0], vertices[vertices.size() - 1]);
        vertices.pop_back();
        Heapify(0);
        return result;
    }
 
    bool Is_Empty() const {
        return vertices.empty();
    }
 
};
 
 
class Graph {
private:
    List* table;
 
public:
    int dots, sticks;
    std::ifstream fin;
 
    Graph() {
        fin.open("spantree3.in");
        fin >> dots >> sticks;
        table = new List[dots];
    }
 
    void Read_stick_data() {
        long long start, end, weight;
        for (int i = 0; i < sticks; i++) {
            fin >> start >> end >> weight;
            if (table[start - 1].head) {
                Element* temp = table[start - 1].head;
                Element* dot = new Element;
                dot->number = end - 1;
                dot->next = temp;
                dot->weight = weight;
                table[start - 1].head = dot;
            }
            else {
                table[start - 1].head = new Element;
                table[start - 1].head->number = end - 1;
                table[start - 1].head->weight = weight;
                table[start - 1].head->next = nullptr;
            }
            if (table[end - 1].head) {
                Element* temp = table[end - 1].head;
                Element* dot = new Element;
                dot->number = start - 1;
                dot->next = temp;
                dot->weight = weight;
                table[end - 1].head = dot;
            }
            else {
                table[end - 1].head = new Element;
                table[end - 1].head->number = start - 1;
                table[end - 1].head->weight = weight;
                table[end - 1].head->next = nullptr;
            }
        }
    }
 
 
    long long MST_Prim() {
        long long total_weight = 0;        
        Binary_Heap queue(dots);
        std::vector<PK> vertices;
        vertices.resize(dots);
 
        for (int i = 0; i < dots; i++) { vertices[i].set_defaults(); }
        vertices[0].key = 0;
 
        while (!queue.Is_Empty()) {
            Weighted_Vertex temp_to_add, extracted_temp = queue.Extract();
            if ((extracted_temp.weight == vertices[extracted_temp.num].key) && (!vertices[extracted_temp.num].used)) {
                total_weight += extracted_temp.weight;
                vertices[extracted_temp.num].used = true;
                Element* adjacent = table[extracted_temp.num].head;
                while (adjacent) {
                    if ((adjacent->weight < vertices[adjacent->number].key) && (!vertices[adjacent->number].used)) {
                        vertices[adjacent->number].key = adjacent->weight;
                        temp_to_add.num = adjacent->number;
                        temp_to_add.weight = adjacent->weight;
                        queue.Add_Vertex(temp_to_add);
                    }
                    adjacent = adjacent->next;
                }
            }
        }
        return total_weight;
    }
 
    ~Graph() {
        delete table;
 
    }
};
 
 
int main() {
    Graph graph;
    std::ofstream fout;
    graph.Read_stick_data();
    fout.open("spantree3.out");
    fout << graph.MST_Prim();
}
