#include<fstream>
 
struct List {
    int dot_number;
    List* next = nullptr;
};
 
 
struct Element {
    int number;
    int distance = 0;
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
 
 
class Graph {
private:
    Element* table;
    Queue queue;
public:
    int dots, sticks, start, end, extracted;
    std::ifstream fin;
    std::ofstream fout;
    Graph() {
        fin.open("pathbge1.in");
        fin >> dots >> sticks;
        table = new Element[dots];
        queue.numbers = new int[dots];
    }
    void read_stick_data() {
        for (int i = 0; i < sticks; i++) {
            fin >> start >> end;
            if (table[start - 1].head) {
                List* temp = table[start - 1].head;
                List* dot = new List;
                dot->next = temp;
                dot->dot_number = end - 1;
                table[start - 1].head = dot;
            }
            else {
                table[start - 1].head = new List;
                table[start - 1].head->dot_number = end - 1;
                table[start - 1].head->next = nullptr;
            }
            if (table[end - 1].head) {
                List* temp = table[end - 1].head;
                List* dot = new List;
                dot->dot_number = start - 1;
                dot->next = temp;
                table[end - 1].head = dot;
            }
            else {
                table[end - 1].head = new List;
                table[end - 1].head->dot_number = start - 1;
                table[end - 1].head->next = nullptr;
            }
        }
    }
 
    void BFS(int start_point) {
        queue.push(start_point);
        table[start_point].white = false;
        while (queue.last_free != queue.next) {
            extracted = queue.extract();
            List* temp = new List;
            temp = table[extracted].head;
            while (temp) {
                if (table[temp->dot_number].white) {
                    table[temp->dot_number].white = false;
                    table[temp->dot_number].distance = table[extracted].distance + 1;
                    queue.push(temp->dot_number);
                }
                temp = temp->next;
            }
            table[extracted].white = false;
        }
    }
 
    ~Graph() {
        fout.open("pathbge1.out");
        for (int i = 0; i < dots; i++) {
            fout << table[i].distance << " ";
        }
    }
};
 
 
int main() {
    Graph graph;
    graph.read_stick_data();       
    graph.BFS(0);
}
