#include <iostream>
#include <string>
#include <chrono>
#include <vector>

using namespace std;

string trc(const vector<vector<vector<vector<int>>>>& matrix,
            int value, string ans, int i, int j, 
            bool left, vector<int>& seq) {
    if (i==j) {
        if (left) {return "(" + to_string(seq[j-1]);}
        else {return to_string(seq[j-1]) + ")";}
    }
    vector<int> values = matrix[i-1][j-1][0];
    vector<int> b = matrix[i-1][j-1][1];
    int x = 1;
    while (values[x-1]!=value) {
        x++;
    }
    int left_value = b[3*(x-1)];
    int right_value = b[3*(x-1)+1];
    int bracket = b[3*(x-1)+2];
    return trc(matrix, left_value, ans, i, bracket, true, seq) + " " + 
        trc(matrix, right_value, ans, bracket+1, j, false, seq);

}

int main() {

    auto start = std::chrono::high_resolution_clock::now();
    
    vector<vector<vector<vector<int>>>> matrix(
        4, vector<vector<vector<int>>>(
               4, vector<vector<int>>(
                      2, vector<int>())));

    // Assign values to the matrix
    
    
    matrix[0][0][0] = {1};
    matrix[0][1][0] = {2};
    matrix[0][2][0] = {1};
    matrix[0][3][0] = {1};
    matrix[1][1][0] = {2};
    matrix[1][2][0] = {1};
    matrix[1][3][0] = {1};
    matrix[2][2][0] = {2};
    matrix[2][3][0] = {2};
    matrix[3][3][0] = {1};

    matrix[0][1][1] = {1, 2, 1};
    matrix[0][2][1] = {2, 2, 2};
    matrix[0][3][1] = {1, 1, 3};
    matrix[1][2][1] = {2, 2, 2};
    matrix[1][3][1] = {1, 1, 3};
    matrix[2][3][1] = {2, 1, 3};
    
   


    vector<int> problem = {1, 2, 2, 1};
    cout << 1 << endl;
    cout << trc(matrix, 1, "", 1, 4, true, problem) << endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    return 0;
}

