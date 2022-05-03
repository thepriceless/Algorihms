#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
 
int main() {
    int length;
    long long color;
    std::cin >> length;
    std::vector<long long> colors;
    for (int i = 0; i < length; ++i) {
        std::cin >> color;
        colors.push_back(color);
    }
    std::vector<std::vector<long long>> dp; // dp[i][j] ������ ���-�� ����������� ����� ��������� i � j ������������; ��� i > j dp[i][j] = 0;
    dp.resize(length);
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            dp[i].push_back(0);
        }
    }
 
    for (int gap = 0; gap < length; ++gap) {
        for (int start = 0; start < length - gap; ++start) {
            if (colors[start] == colors[start + gap]) {
                if (start + 1 < length) {
                    dp[start][start + gap] += (dp[start + 1][start + gap] % 1000000000);
                }
                if (start + gap - 1 >= 0) {
                    dp[start][start + gap] += (dp[start][start + gap - 1] % 1000000000);
                }
                dp[start][start + gap]++;
            }
            else {
                if (start + 1 < length && start + gap - 1 >= 0) {
                    dp[start][start + gap] += (dp[start][start + gap - 1] % 1000000000);
                    dp[start][start + gap] += (dp[start + 1][start + gap] % 1000000000);
                    dp[start][start + gap] -= (dp[start + 1][start + gap - 1] % 1000000000);
                }
                else if (start + 1 < length) {
                    dp[start][start + gap] += (dp[start + 1][start + gap] % 1000000000);
                }
                else if (start + gap - 1 >= 0) {
                    dp[start][start + gap] += (dp[start][start + gap - 1] % 1000000000);
                }         
            }
            dp[start][start + gap] %= 1000000000;
        }
    }
    if (dp[0][length - 1] < 0) { std::cout << dp[0][length - 1] + 1000000000; }
    else { std::cout << dp[0][length - 1] % 1000000000; }
}
