#pragma once

#include <vector>
#include <array>
#include <cassert>
#include <bitset>
#include <iostream>

// element = 
// 511 = 0B111111111
using Sudoku = std::array<std::array<int,9>, 9>;
std::array<int, 11> masks = { 511, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };
constexpr int size = 9;

int CountOne(int x) {
    assert(x >= 0);
    int count = 0;
    while (x != 0) {
        x = x & (x - 1);
        ++count;
    }
    return count;
}

class SudokuSolver {
public:
    SudokuSolver(const Sudoku& sudoku) : m_sudoku{0} {
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                assert(sudoku[row][col] >= 0 && sudoku[row][col] <= 9);
                m_sudoku[row][col] = masks[sudoku[row][col]];
            }
        }
    }

    void PrintBinary() {
        for (int row = 0; row < 9; ++row) {
            if (row != 0 && row % 3 == 0) {
                std::cout <<
                    "---------------+"
                    "---------------+"
                    "---------------\n";
            }
            for (int col = 0; col < 9; ++col) {
                if (col != 0 && col % 3 == 0) std::cout << "| ";
                std::cout << std::bitset<10>(m_sudoku[row][col]) << ' ';
            }
            std::cout << std::endl;
        }
    }

    void Set(int row, int col, int mask) {
        assert(row >= 0 && row < 9);
        assert(col >= 0 && col < 9);
        assert(mask > 0 && mask < 512 && CountOne(mask) == 1);
        assert((m_sudoku[row][col] & mask) != 0);
        for (int r = 0; r < 9; ++r) if (r != row) m_sudoku[r][col] &= ~mask;
        for (int c = 0; c < 9; ++c) if (c != col) m_sudoku[row][c] &= ~mask;
        int subgridRow = row / 3;
        int subgridCol = col / 3;
        for (int r = subgridRow * 3; r < (subgridRow + 1) * 3; ++r) {
            for (int c = subgridCol * 3; c < (subgridCol + 1) * 3; ++c) {
                if (r != row && c != col) m_sudoku[r][c] &= ~mask;
            }
        }
        m_sudoku[row][col] |= masks[10];
    }

    bool Solve() {
        PrintBinary();
        std::cout << std::endl;

        int minOptRow = -1;
        int minOptCol = -1;
        int minOptCnt = INT_MAX;
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if ((m_sudoku[row][col] & masks[10]) == 0) {
                    int cnt = CountOne(m_sudoku[row][col]);
                    if (cnt < minOptCnt) {
                        minOptCnt = cnt;
                        minOptRow = row;
                        minOptCol = col;
                    }
                    if (minOptCnt == 1) break;
                }
            }
            if (minOptCnt == 1) break;
        }
        std::cout << "row: " << minOptRow << ", col: " << minOptCol << ", cnt: " << minOptCnt << std::endl;
        if (minOptCnt == INT_MAX) return true;
        else if (minOptCnt == 0) return false;
        else if (minOptCnt == 1) {
            int value = 0;
            for (value = 1; value <= 9; ++value) {
                if ((m_sudoku[minOptRow][minOptCol] & masks[value]) != 0) break;
            }
            assert(value >= 1 && value <= 9);
            assert(m_sudoku[minOptRow][minOptCol] == masks[value]);
            Set(minOptRow, minOptCol, masks[value]);
            return Solve();
        }
        else {
            std::vector<int> opts;
            for (int value = 1; value <= 9; ++value) {
                if ((m_sudoku[minOptRow][minOptCol] & masks[value]) != 0) opts.push_back(value);
            }
            assert(opts.size() != 0);
            Sudoku cache = m_sudoku;
            for (int value : opts) {
                Set(minOptRow, minOptCol, masks[value]);
                bool ret = Solve();
                if (ret == true) return true;
                else
                    m_sudoku = cache;
            }
            return false;
        }
        return false;
    }

    Sudoku GetSudoku() {
        Sudoku sudoku = { 0 };
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                int mask = m_sudoku[row][col] & ~masks[10];
                int value = 1;
                for (; value <= 9; ++value) if ((mask & masks[value]) != 0) break;
                sudoku[row][col] = value;
            }
        }
        return sudoku;

    }

private:
    Sudoku m_sudoku;
};

std::ostream& operator<<(std::ostream& ost, const Sudoku& sudoku) {
    for (int row = 0; row < 9; ++row) {
        if (row != 0 && row % 3 == 0) {
            ost <<
                "------+"
                "-------+"
                "------\n";
        }
        for (int col = 0; col < 9; ++col) {
            if (col != 0 && col % 3 == 0) ost << "| ";
            if (sudoku[row][col] >= 1 && sudoku[row][col] <= 9)
                ost << sudoku[row][col] << ' ';
            else
                ost << "* ";
        }
        ost << std::endl;
    }
    return ost;
}