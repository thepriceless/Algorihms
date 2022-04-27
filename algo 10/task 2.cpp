#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cmath>
#include<iomanip>
#include<queue>
 
 
struct Element {
    int number;
    long double weight;
    Element* next = nullptr;
};
 
struct List {
    Element* head = nullptr;
};
 
struct PK {
    int parent;
    float key;
    bool used;
 
    void set_defaults() {
        parent = -1;
        key = LONG_MAX;
        used = false;
    }
};
 
struct Point {
    int x;
    int y;
    bool used = false;
};
 
struct Weighted_Vertex {
    int num;
    long double weight;
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
    //List* table;
    std::vector<long double> min_lengths;
    std::vector<Point> points;
 
    long double Edge_Length(Point p1, Point p2) {
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    }
 
public:
    int dots;
    std::ifstream fin;
 
    Graph() {
        fin.open("spantree.in");
        fin >> dots;
        min_lengths.push_back(0);
        for (int i = 1; i < dots; i++) { min_lengths.push_back(LONG_MAX); }
    }
 
    void Read_stick_data() {
        int x, y;
        long double weight;
        Point point;
        for (int i = 0; i < dots; i++) {
            fin >> x >> y;
            point.x = x;
            point.y = y;
            points.push_back(point);
        }
    }
 
    long double MST_Prim() {
        int next_minimum_point, current_point = 0;
        long double temp_minimum_length, total_weight = 0;
        for (int i = 1; i < dots; i++) {
            points[current_point].used = true;
            temp_minimum_length = LONG_MAX;
            for (int j = 0; j < dots; j++) {
                if (!points[j].used) {
                    min_lengths[j] = std::min(Edge_Length(points[current_point], points[j]), min_lengths[j]);
                    if (min_lengths[j] < temp_minimum_length) {
                        temp_minimum_length = min_lengths[j];
                        next_minimum_point = j;
                    }
                }
            }
            current_point = next_minimum_point;
            total_weight += temp_minimum_length;
        }
        return total_weight;
    }
 
    ~Graph() {
    }
};
 
 
int main() {
    Graph graph;
    std::ofstream fout;
    graph.Read_stick_data();
    fout.open("spantree.out");
    fout << std::setprecision(10) << graph.MST_Prim();
}
