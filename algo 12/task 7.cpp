#include<iostream>
#include<fstream>
#include<vector>
 
int main() {
    int capacity, n, mass;
    std::ifstream fin;
    std::ofstream fout;
    fin.open("knapsack.in");
    fin >> capacity >> n;
    std::vector<int> masses;
    std::vector<std::vector<int>> dp;
    dp.resize(n + 1);
    for (int i = 0; i <= capacity; ++i) {
        dp[0].push_back(0);
    }
 
    for (int i = 0; i < n; ++i) {
        fin >> mass;
        masses.push_back(mass);
        std::vector<int> row;
        dp[i + 1].resize(capacity + 1);
    }
 
    for (int units = 1; units <= n; ++units) {
        for (int size = 1; size <= capacity; ++size) {
            if (size - masses[units - 1] < 0) {
                dp[units][size] = dp[units - 1][size];
            }
            else {
                dp[units][size] = std::max(dp[units - 1][size], dp[units - 1][size - masses[units - 1]] + masses[units - 1]);
            }
        }
    }
 
    fout.open("knapsack.out");
    fout << dp[n][capacity];
}
