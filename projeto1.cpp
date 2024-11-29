#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

char FILENAME[13] = "filename.txt";
int BUFFER = 256;

int main(){
    int intended_result, matrix_size, puzzle_size; /* vão ser definidos no input */
    FILE *file;
    char line[BUFFER];
    char* ptr;
    bool output = false;

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


    /* A tabela do puzzle tem 3 dimensões, duas de posição, uma para guardar os valores possíveis */
    vector<vector<vector<int>>> values_table(puzzle_size, vector<vector<int>>(puzzle_size));

    /* Preenche os valores da maior diagonal com o próprio número */
    for(int i=0; i < puzzle_size; i++) values_table[i][i].push_back(puzzle[i]);

    /* Preenche os valores da segunda diagonal com os valores da tabela */
    for(int i=0; i < puzzle_size -1; i++) values_table[i][i+1].push_back(matrix[puzzle[i]-1][puzzle[i+1]-1]);

    /* Loop grande que preenche o resto dos valores */

    /* itera a diagonal da matriz do puzzle */
    for(int diagonal = 2; diagonal < puzzle_size; diagonal ++){

        /* itera a linha na diagonal */
        for(int line = 0; line + diagonal < puzzle_size; line ++){

            /* vai buscar a celula para ser preenchida */
            int column = diagonal + line;
            vector<int> cell = values_table[line][column];

            /* itera sobre as linhas e colunas para calcular o resultado da celula */
            for(int table_searcher = 1; table_searcher < diagonal; table_searcher++){

                /* vão ser cada célula das linhas e colunas da célula que queremos calcular */
                vector<int> celula_coluna = values_table[column-table_searcher][column];
                vector<int> celula_linha = values_table[line][column-table_searcher];

                /* itera sobre os valores contidos na célula da mesma linha */
                for(int line_values_iterator = 0; line_values_iterator < celula_linha.size() && cell.size() <= matrix_size; line_values_iterator++){

                    /* itera sobre os valores contidos na célula da mesma coluna */
                    for(int col_values_iterator = 0; col_values_iterator < celula_linha.size() && cell.size() <= matrix_size; col_values_iterator++){
                        /* calcula o novo valor da célula */
                        int value = matrix[celula_linha[line_values_iterator]-1][celula_coluna[col_values_iterator]-1];
                        
                        /* verifica se o valor já está contido no vetor de soluções da célula */
                        if(!any_of(cell.begin(), cell.end(), [value](int x){ return x == value;})){
                            cell.push_back(value);
                        }
                        /* verifica se o resultado final é sasfeito*/
                        if(diagonal == puzzle_size-1 && value == intended_result){
                            printf("YAY, chegaste ao resultado");
                            output = true;
                        }
                    }
                }
            }
        }
    }

    // guardar a posição do parentesis e os valores obtidos as sub operações, ex: (2 2)3 -> guardar valor de 2+2, 3 e a posição do parentesis (2)

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