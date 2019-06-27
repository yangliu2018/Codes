#include "Sudoku.h"
#include <iostream>

using namespace std;

int main() {
    string str = "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";
    Sudoku sudoku;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int idx = row * 9 + col;
            if (str[idx] >= '1' && str[idx] <= '9') sudoku[row][col] = str[idx] - '0';
            else sudoku[row][col] = 0;
        }
    }
    cout << sudoku << endl;
    cout << endl;
    SudokuSolver solver(sudoku);
    solver.Solve();
    auto ret = solver.GetSudoku();
    cout << ret << endl;
    return 0;
}