#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

char FILENAME[13] = "filename.txt";
int BUFFER = 256;

string trc(const vector<vector<vector<vector<int>>>>& matrix,
            int value, string ans, int i, int j, 
            bool left, vector<int>& seq) {
    if (i==j) {
        if (left) {return to_string(seq[j-1]);}
        else {return to_string(seq[j-1]);}
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
    return "(" + trc(matrix, left_value, ans, i, bracket, true, seq) + " " + 
        trc(matrix, right_value, ans, bracket+1, j, false, seq) + ")";

}

int main(){

    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int intended_result, matrix_size, puzzle_size; /* vão ser definidos no input */
    bool output = false;

    cin >> matrix_size;
    cin >> puzzle_size;

    /* preenche o vetor com vetores de tamanho matrix_size */
    vector<vector<int>> matrix(matrix_size, vector<int>(matrix_size)); 

    vector<int> puzzle(puzzle_size);

    bool has_num_in_cell[matrix_size+1];
    fill_n(has_num_in_cell, matrix_size+1, false);

    /* preenche a matriz com os valores dados no input */
    for(int i = 0; i < matrix_size; i++){
        int j = 0;
        for(; j < matrix_size; j++){
            cin >> matrix[i][j];
        }
    }

    /* preenche os valores do puzzle */
    
    for(int i = 0; i < puzzle_size; i++){
        cin >> puzzle[i];
    } 

    cin >> intended_result; /* o resultado pretendido no puzzle */
    auto start = std::chrono::high_resolution_clock::now();

    /* A tabela do puzzle tem 3 dimensões, duas de posição, uma para guardar os valores possíveis */
    vector<vector<vector<vector<int>>>> values_table(
        puzzle_size, vector<vector<vector<int>>>(
        puzzle_size, vector<vector<int>>(
        2, vector<int>())));

    /* Preenche os valores da maior diagonal com o próprio número */
    for(int i=0; i < puzzle_size; i++) values_table[i][i][0].push_back(puzzle[i]);

    /* Preenche os valores da segunda diagonal com os valores da tabela */
    for(int i=0; i < puzzle_size -1; i++) {
        values_table[i][i+1][0].push_back(matrix[puzzle[i]-1][puzzle[i+1]-1]);
        values_table[i][i+1][1].push_back(puzzle[i]);
        values_table[i][i+1][1].push_back(puzzle[i+1]);
        values_table[i][i+1][1].push_back(i+1);
    }

    /* Loop grande que preenche o resto dos valores */

    /* itera a diagonal da matriz do puzzle */
    for(int diagonal = 2; diagonal < puzzle_size; diagonal ++){

        /* itera a linha na diagonal */
        for(int line = 0; line + diagonal < puzzle_size; line ++){

            /* vai buscar a celula para ser preenchida */
            int column = diagonal + line;

            vector<vector<int>> &current_cell = values_table[line][column];
            vector<int> &current_values = current_cell[0];
            vector<int> &current_info = current_cell[1];

            /* itera sobre as linhas e colunas para calcular o resultado da celula */
            for(int table_searcher = 1; table_searcher <= diagonal && (int) values_table[line][column][0].size() <= matrix_size; table_searcher++){

                /* vão ser cada célula das linhas e colunas da célula que queremos calcular */
                vector<int> line_cell = values_table[line][column-table_searcher][0];
                vector<int> column_cell = values_table[column-table_searcher+1][column][0];
                int line_cell_size = (int)line_cell.size();
                int column_cell_size = (int)column_cell.size();
                

                /* itera sobre os valores contidos na célula da mesma linha */
                for(int line_values_iterator = 0; line_values_iterator < line_cell_size && (int) current_values.size() <= matrix_size && !output; line_values_iterator++){

                    /* itera sobre os valores contidos na célula da mesma coluna */
                    for(int col_values_iterator = 0; col_values_iterator < column_cell_size && (int) current_values.size() <= matrix_size && !output; col_values_iterator++){
                        /* calcula o novo valor da célula */
                        int left_value = line_cell[line_values_iterator];
                        int right_value = column_cell[col_values_iterator];
                        int value = matrix[left_value-1][right_value-1];
                        
                        /* verifica se o valor já está contido no vetor de soluções da célula */
                        if(!has_num_in_cell[value]){
                            current_values.push_back(value);
                            has_num_in_cell[value] = true;

                            current_info.push_back(left_value);
                            current_info.push_back(right_value);
                            current_info.push_back(column - table_searcher + 1);
                        }
                        /* verifica se o resultado final é sasfeito*/
                        if(diagonal == puzzle_size-1 && value == intended_result){
                            //printf("YAY, chegaste ao resultado:\n");
                            output = true;
                        }
                    }
                }
                for(int v : current_values) has_num_in_cell[v] = false;
            }
        }
    }

    if (!output) {
        cout << 0 << endl; 
        return 0;}
    cout << 1 << endl;
    cout << trc(values_table, intended_result, "", 1, puzzle_size, true, puzzle) << endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    return 0;
}
//blablabla