#include<fstream>
#include<iostream>
#include<vector>
 
struct List {
    int dot_number;
    List* next = nullptr;
};
 
 
struct Element {
    int number;
    int distance = 0;
    int parent = LONG_MIN;
    bool white = true;
    List* head = nullptr;
};
 
 
struct Queue {
    int* numbers;
    int next = 0, last_free = 0;
    void push(int elem) {
        numbers[last_free++] = elem;
    }
    int extract() {
        return numbers[next++];
    }
};
 
 
struct Neighbours {
    int left, right, up, down;
    void set_defaults() {
        left = -1;
        right = -1;
        down = -1;
        up = -1;
    }
};
 
 
class Graph {
private:
    Element* table;
    Queue queue;
    int full_size;
public:
    int height, width, starting_point, finishing_point, start, end, extracted;
    char elem;
    Neighbours neighbours;
    int** field;
    std::ifstream fin;
    std::ofstream fout;
    Graph() {
        fin.open("input.txt");
        fout.open("output.txt");
        fin >> height >> width;
        full_size = height * width;
        table = new Element[full_size];
        queue.numbers = new int[full_size];
        field = new int* [height];
        for (int i = 0; i < height; i++) { field[i] = new int[width]; }
    }
 
    void read_stick_data() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                fin >> elem;
                if (elem == '#') { field[i][j] = 0; }
                else {
                    field[i][j] = 1;
                    if (elem == 'S') { starting_point = i * width + j; }
                    if (elem == 'T') { finishing_point = i * width + j; }
                }    
            }
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (field[i][j]) {
                    neighbours.set_defaults();
                    if (height != 1) {
                        if (i != 0) {
                            if (field[i - 1][j]) { neighbours.up = (i - 1) * width + j; }
                        }
                        if (i != height - 1) {
                            if (field[i + 1][j]) { neighbours.down = (i + 1) * width + j; }
                        }
                    }
                    if (width != 1) {
                        if (j != width - 1) {
                            if (field[i][j + 1]) { neighbours.right = i * width + j + 1; }
                        }
                        if (j != 0) {
                            if (field[i][j - 1]) { neighbours.left = i * width + j - 1; }
                        }
                    }
                    if (neighbours.right != -1) { distributor(i * width + j, neighbours.right); }
                    if (neighbours.left != -1) { distributor(i * width + j, neighbours.left); }
                    if (neighbours.up != -1) { distributor(i * width + j, neighbours.up); }
                    if (neighbours.down != -1) { distributor(i * width + j, neighbours.down); }
                }
            }
        }
    }
 
    void distributor(int start, int end) {
        table[start].number = start;
        if (table[start].head) {
            List* temp = table[start].head;
            List* dot = new List;
            dot->next = temp;
            dot->dot_number = end;
            table[start].head = dot;
        }
        else {
            table[start].head = new List;
            table[start].head->dot_number = end;
            table[start].head->next = nullptr;
        }
    }
 
    void BFS(int start_point) {
        queue.push(start_point);
        table[start_point].white = false;
        table[start_point].parent = -1;
        while (queue.last_free != queue.next) {
            extracted = queue.extract();
            List* temp = new List;
            temp = table[extracted].head;
            while (temp) {
                if (table[temp->dot_number].white) {
                    table[temp->dot_number].white = false;
                    table[temp->dot_number].distance = table[extracted].distance + 1;
                    table[temp->dot_number].parent = extracted;
                    queue.push(temp->dot_number);
                }
                temp = temp->next;
            }
            table[extracted].white = false;
        }
    }
 
    void create_road() {
        int cycle_num = table[finishing_point].distance;
        char* reversed_road = new char[cycle_num];
        Element finish = table[finishing_point];
        while (finish.parent != -1) {
            if (finish.parent == finish.number + width) { reversed_road[cycle_num - 1] = 'U'; }
            else if (finish.parent == finish.number - width) { reversed_road[cycle_num - 1] = 'D'; }
            else if (finish.parent == finish.number - 1) { reversed_road[cycle_num - 1] = 'R'; }
            else if (finish.parent == finish.number + 1) { reversed_road[cycle_num - 1] = 'L'; }
            finish = table[finish.parent];
            cycle_num--;
        }
        for (int i = 0; i < table[finishing_point].distance; i++) { fout << reversed_road[i]; }
    }
 
    ~Graph() {
        if (table[finishing_point].distance == 0) { fout << -1; }
        else {
            fout << table[finishing_point].distance << '\n';
            create_road();
        }
    }
};
 
 
int main() {
    Graph graph;
    graph.read_stick_data(); 
    graph.BFS(graph.starting_point);
}
