#include<iostream>
#include<fstream>
#include<vector>
 
struct Element {
    int number;
    Element* next = nullptr;
};
 
 
struct list {
    Element* head = nullptr;
};
 
struct Pair {
    int including_root = 0;
    int excluding_root = 0;
};
 
 
 
class Graph {
private:
    list* table;
    int* colors;
    int root;
    std::vector<Pair> dp; // dp[i] ������ 2 �����.
    // including_root - ������������ ��������� ����� ���� ������ � ���������������� ��������� ������ �� ��������� � ������ � i, ����������� ������� i.
    // excludint_root - ������������ ��������� ����� ���� ������ � ���������������� ��������� ������ �� ��������� � ������ � i, ����������� �� ������� i.
    std::vector<int> parents_;
    std::vector<int> masses;
 
    void DFS_visit(int start_point) {
        colors[start_point] = 1;
        Element* temp = new Element;
        temp = table[start_point].head;
        while (temp) {
            if (colors[temp->number] == 0) {
                DFS_visit(temp->number);
            }
            temp = temp->next;
        }
        temp = table[start_point].head;
        while (temp) {
            dp[start_point].including_root += dp[temp->number].excluding_root;
            dp[start_point].excluding_root += std::max(dp[temp->number].excluding_root, dp[temp->number].including_root);
            temp = temp->next;
        }
        dp[start_point].including_root += masses[start_point];
    }
 
public:
    int n, vertex, mass, start, end;
 
    std::ifstream fin;
    std::ofstream fout;
 
    Graph() {
        fin.open("selectw.in");
        fin >> n;
        table = new list[n + 1];
        colors = new int[n + 1];
        dp.resize(n + 1);
        parents_.push_back(-1);
        masses.push_back(-1);
    }
 
    void Read_Data() {
        for (int i = 0; i < n; ++i) {
            fin >> vertex >> mass;
            parents_.push_back(vertex);
            masses.push_back(mass);
            if (!vertex) {
                root = i + 1;
            }
        }
        for (int i = 1; i <= n; i++) {
            start = parents_[i];
            end = i;
            if (table[start].head) {
                Element* temp = table[start].head;
                Element* dot = new Element;
                dot->number = end;
                dot->next = temp;
                table[start].head = dot;
            }
            else {
                table[start].head = new Element;
                table[start].head->number = end;
                table[start].head->next = nullptr;
            }
        }
    }
 
    void DFS() {
        for (int i = 0; i < n + 1; i++) {
            colors[i] = 0;
        }
        DFS_visit(root);
    }
 
    ~Graph() {
        fout.open("selectw.out");
        fout << std::max(dp[root].excluding_root, dp[root].including_root);
    }
};
 
int main() {
    Graph graph;
    graph.Read_Data();
    graph.DFS();
}
