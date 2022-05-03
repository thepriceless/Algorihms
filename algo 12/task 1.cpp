#include<iostream>
#include<fstream>
#include<vector>
 
struct Number_and_Parent {
    int num;
    int par;
};
 
struct Number_and_Index {
    int number;
    int ind;
};
 
template<typename T>
int Binary_Search(std::vector<T>& Array, int start, int end, int elem) {
    while (start != end - 1) {
        int mid = (start + end) / 2;
        if (elem > Array[mid].number) { start = mid; }
        else { end = mid; }
    }
    return end;
}
 
int main() {
    int n, number, sequence_max_length = 1;
    std::vector<Number_and_Parent> sequence;
    std::vector<Number_and_Index> dp; // dp[�] = ���������� �������, �� ������� ����� ������������� ������������������ ����� �
    std::cin >> n;
    Number_and_Parent temp_np;
    Number_and_Index temp_ni;
    for (int i = 0; i < n; ++i) {
        std::cin >> number;
        temp_np.num = number;
        temp_np.par = -1;
        sequence.push_back(temp_np);
        temp_ni.ind = -1;
        temp_ni.number = LONG_MAX;
        dp.push_back(temp_ni);
    }
    dp[0].number = LONG_MIN;
    dp.push_back(temp_ni);
    for (int i = 1; i <= n; ++i) {
        int index = Binary_Search(dp, -1, i + 1, sequence[i - 1].num);
        dp[index].number = sequence[i - 1].num;
        dp[index].ind = i - 1;
        sequence[i - 1].par = dp[index - 1].ind;
        sequence_max_length = std::max(sequence_max_length, index);
    }
    int index_last_elem = dp[sequence_max_length].ind;
    std::vector<int> answer;
    while (index_last_elem >= 0) {
        answer.push_back(sequence[index_last_elem].num);
        index_last_elem = sequence[index_last_elem].par;
    }
    std::cout << sequence_max_length << std::endl;
    for (int i = answer.size() - 1; i >= 0; --i) { std::cout << answer[i] << ' '; }
}
