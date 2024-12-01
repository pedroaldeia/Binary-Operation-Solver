#include <iostream>
#include <string>
#include <vector>

using namespace std;

string trc(const vector<vector<vector<vector<int>>>>& matrix,
            int value, string ans, int i, int j, 
            bool left, vector<int>& seq) {
    if (i==j) {
        if (left) {return "(" + seq[j-1];}
        else {return seq[j-1] + ")";}
    }

    vector<int> values = matrix[i][j][0];
    vector<int> b = matrix[i][j][1];
    int x = 1;
    while (values[x-1]!=value) {
        x++;
    }
    int left_value = b[3*(x-1)];
    int right_value = b[3*(x-1)+1];
    int bracket = b[3*(x-1)+2];
    return trc(matrix, left_value, ans, i, bracket-1, true, seq) + " " + 
        trc(matrix, right_value, ans, bracket+1, j, false, seq);

}

int main() {
    vector<vector<vector<vector<int>>>> matrix;

    matrix[0][0][0] = {2};
    matrix[0][1][0] = {2};
    matrix[0][2][0] = {1, 2};
    matrix[1][0][0] = {2};
    matrix[1][1][0] = {2};
    matrix[1][2][0] = {1, 2};
    matrix[2][0][0] = {2};
    matrix[2][1][0] = {2};
    matrix[2][2][0] = {1, 2};

    matrix[0][0][1] = {2, 3, 2, 1};
    matrix[0][1][1] = {2, 3, 2, 1};
    matrix[0][2][1] = {2, 3, 2, 1};
    matrix[1][0][1] = {2};
    matrix[1][1][1] = {2};
    matrix[1][2][1] = {1, 2};
    matrix[2][0][1] = {2};
    matrix[2][1][1] = {2};


    vector<int> problem = {2, 2, 2, 2, 1, 3};
 
    cout << trc(matrix, 2, "", 1, 6, true, problem);

    return 0;
}

