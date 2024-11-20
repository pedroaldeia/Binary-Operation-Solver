#include <iostream>
#include <vector>
using namespace std;

int main(){
    int intended_result, matrix_size, puzzle_size; /* vão ser definidos no input */

    scanf("%d %d", &matrix_size, &puzzle_size);

    /* preenche o vetor com vetores de tamanho matrix_size */
    vector<vector<int>> matrix(matrix_size, vector<int>(matrix_size)); 

    vector<int> puzzle(puzzle_size);

    /* preenche a matriz com os valores dados no input */
    for(int i = 0; i < matrix_size; i++){
        for(int j = 0; j < matrix_size; j++)
            scanf("%d", &matrix[i][j]);
    }

    /* preenche os valores do puzzle */
    for(int i = 0; i < puzzle_size; i++) scanf("%d", &puzzle[i]);

    scanf("%d", &intended_result); /* o resultado pretendido no puzzle */

    /* Abaixo são só testes para verificar o output */

    cout << "The entered matrix size: " << matrix_size << endl;
    cout << "The entered puzzle size: " << puzzle_size << endl;

    cout << "The entered matrix is:\n";
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << "\n";
    }

    cout << "The entered puzzle is:" << endl;
    for (const auto& i : puzzle) {
        cout << puzzle[i] << " ";
    }

    cout << endl << "The entered puzzle result: " << intended_result << endl;
    

    return 0;
}