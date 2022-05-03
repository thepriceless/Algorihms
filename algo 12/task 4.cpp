#include<iostream>
#include<fstream>
#include<vector>
 
struct Pair {
    int row;
    int column;
 
    int Sum_of_indexes() {
        return row + column;
    }
};
 
int main() {
    int height, width;
    std::ifstream fin;
    std::ofstream fout;
    fin.open("knight2.in");
    fin >> height >> width;
    std::vector<int> current_row;
    std::vector<std::vector<int>> dp; // dp[i][j] ������ ���������� ��������� �����, �������� ����� ������� � ������ (i, j)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            current_row.push_back(0);
        }
        dp.push_back(current_row);
        current_row.clear();
    }
    dp[0][0] = 1;
 
    Pair temp;
    std::vector<Pair> coords_sequence;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            temp.row = i;
            temp.column = j;
            coords_sequence.push_back(temp);
            int now_ind = coords_sequence.size() - 1;
            while (now_ind > 0) {
                if (coords_sequence[now_ind].Sum_of_indexes() < coords_sequence[now_ind - 1].Sum_of_indexes()) {
                    std::swap(coords_sequence[now_ind], coords_sequence[now_ind - 1]);
                }
                else if (coords_sequence[now_ind].Sum_of_indexes() == coords_sequence[now_ind - 1].Sum_of_indexes() && coords_sequence[now_ind].row < coords_sequence[now_ind - 1].row) {
                    std::swap(coords_sequence[now_ind], coords_sequence[now_ind - 1]);
                }
                else {
                    break;
                }
                --now_ind;
            }
        }
    }
 
    int row = 0, column = 0;
    for (int i = 0; i < height * width; ++i) {
        row = coords_sequence[i].row;
        column = coords_sequence[i].column;
        if (row - 2 >= 0 && column - 1 >= 0) {
            dp[row][column] += dp[row - 2][column - 1];
        }
        if (row - 2 >= 0 && column + 1 < width) {
            dp[row][column] += dp[row - 2][column + 1];
        }
        if (row - 1 >= 0 && column - 2 >= 0) {
            dp[row][column] += dp[row - 1][column - 2];
        }
        if (row + 1 < height && column - 2 >= 0) {
            dp[row][column] += dp[row + 1][column - 2];
        }
    }
 
    fout.open("knight2.out");
    fout << dp[height - 1][width - 1];
}
