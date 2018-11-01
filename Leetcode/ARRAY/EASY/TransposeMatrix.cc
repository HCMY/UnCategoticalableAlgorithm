class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& A) {
        auto const rows = A.size(), cols = A[0].size(); 
        auto const minmax = std::minmax(rows, cols);
        //first is minimum number, second is the bigger one
        if (minmax.first == rows) A.resize(minmax.second, std::vector<int>(minmax.first));
        else for (auto &row : A) row.resize(minmax.second);
        
        for (int i = 0; i < A.size(); ++i) {
            for (int j = i + 1; j < A[0].size(); ++j) {
                std::swap(A[i][j], A[j][i]);
            }
        }
        
        if (minmax.first == rows) for (auto &row : A) row.resize(minmax.first);
        else A.resize(minmax.first);

        return A;
    }
};
