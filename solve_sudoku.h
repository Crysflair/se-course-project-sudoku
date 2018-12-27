#pragma once
#ifndef SOLVE_SUDOKU_H
#define SOLVE_SUDOKU_H

using namespace std;

//extern bool rows_available[9][10];
//extern bool cols_available[9][10];
//extern bool block_available[9][10];
//extern int ans[9][9];
//
//
//void refresh_everything();
//void set_number(int row, int col, int num);
//void get_next_to_fill(int row, int col, int& nextrow, int& nextcol);
//bool if_valid(int row, int col, int num);
//void revert_number(int row, int col, int num);
//void output_ans();
//bool solve_sudoku(int row, int col);

void solve_sudoku_wrapper(ifstream &puzzles);

#endif
