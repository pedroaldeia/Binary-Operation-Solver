#include <iostream>
#include <vector>
using namespace std;

char FILENAME[13] = "filename.txt";
int BUFFER = 256;

int main(){
    int intended_result, matrix_size, puzzle_size; /* vão ser definidos no input */
    FILE *file;
    char line[BUFFER];
    char* ptr;

    file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Unable to open file");
        return 1;
    }
    
    fgets(line, sizeof(line), file);
    sscanf(line, "%d %d", &matrix_size, &puzzle_size);

    /* preenche o vetor com vetores de tamanho matrix_size */
    vector<vector<int>> matrix(matrix_size, vector<int>(matrix_size)); 

    vector<int> puzzle(puzzle_size);

    /* preenche a matriz com os valores dados no input */
    for(int i = 0; i < matrix_size; i++){
        fgets(line, sizeof(line), file);
        ptr = line;
        int j = 0;
        for(; j < matrix_size; j++){
            sscanf(ptr, "%d", &matrix[i][j]);
            while(*ptr != ' ' && *ptr != '\0') ptr++; 
            ptr++;
        }
    }

    /* preenche os valores do puzzle */
    fgets(line, sizeof(line), file);
    ptr = line;
    for(int i = 0; i < puzzle_size; i++){
        sscanf(ptr, "%d", &puzzle[i]);
        cout << puzzle[i];
        while(*ptr != ' ' && *ptr != '\0') ptr++;
        ptr++;
    } 

    fgets(line, sizeof(line), file);
    sscanf(line, "%d", &intended_result); /* o resultado pretendido no puzzle */


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
    for(int i = 0; i< puzzle_size; i++) cout << puzzle[i] << " ";
    

    cout << endl << "The entered puzzle result: " << intended_result << endl;
    

    return 0;
}