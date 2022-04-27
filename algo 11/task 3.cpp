#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
 
 
struct Element {
    int number;
    long long weight;
    Element* next = nullptr;
};
 
struct List {
    Element* head = nullptr;
};
 
struct PD {
    int parent;
    long long distance;
    bool used;
 
    void set_defaults() {
        parent = -1;
        distance = pow(10, 15);
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
    Binary_Heap(int size, int start) {
        Weighted_Vertex temp;
        temp.num = start;
        temp.weight = 0;
        vertices.push_back(temp);
        temp.weight = pow(10, 15);
        for (int i = 0; i < size; i++) {
            if (i != start) {
                temp.num = i;
                vertices.push_back(temp);
            }
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
    std::vector<PD> vertices;
 
    void Initialize_Single_Source(int start) {
        vertices.clear();
        vertices.resize(dots);
        for (int i = 0; i < dots; ++i) { vertices[i].set_defaults(); }
        vertices[start].distance = 0;
    }
 
public:
    int dots, edges;
    std::ifstream fin;
 
    Graph() {
        fin.open("pathbgep.in");
        fin >> dots >> edges;
        table = new List[dots];
    }
 
    void Read_Data() {
        int start, end;
        long long weight;
        for (int i = 0; i < edges; ++i) {
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
 
    void Dijkstra(int begin) {
        Initialize_Single_Source(begin);
        Binary_Heap queue(dots, begin);
        while (!queue.Is_Empty()) {
            Weighted_Vertex temp_to_add, extracted_temp = queue.Extract();
            if ((extracted_temp.weight == vertices[extracted_temp.num].distance) && (!vertices[extracted_temp.num].used)) {
                vertices[extracted_temp.num].used = true;
                Element* adjacent = table[extracted_temp.num].head;
                while (adjacent) {
                    if ((adjacent->weight + vertices[extracted_temp.num].distance < vertices[adjacent->number].distance) && (!vertices[adjacent->number].used)) {
                        vertices[adjacent->number].distance = adjacent->weight + vertices[extracted_temp.num].distance;
                        temp_to_add.num = adjacent->number;
                        temp_to_add.weight = vertices[adjacent->number].distance;
                        queue.Add_Vertex(temp_to_add);
                    }
                    adjacent = adjacent->next;
                }
            }
        }
    }
 
    long long Single_Shortest_Path(int en) {
        return vertices[en].distance;
    }
 
    ~Graph() {
        delete table;
        vertices.clear();
    }
};
 
 
int main() {
    Graph graph;
    std::ofstream fout;
    fout.open("pathbgep.out");
    graph.Read_Data();
    graph.Dijkstra(0);
    for (int j = 0; j < graph.dots; ++j) {
        fout << graph.Single_Shortest_Path(j) << ' ';
    }
}
