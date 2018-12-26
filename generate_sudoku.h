#pragma once

#ifndef GENERATE_SUDOKU_H
#define GENERATE_SUDOKU_H

#include <fstream>
using namespace std;

extern const long OUTARRSIZE;
extern char outarray[];
extern int outarray_cur;
extern int out_puzzle_remain;
extern ofstream outarray_file;

extern char permutation[9];
extern int colswap[9];
extern int rowswap[9];
extern int combination_345[6][3];
extern int combination_678[6][3];

extern int seed_cur;
extern char seeds[][9][9];

void append_to_outarray(int seed_num, int colswap[9], int rowswap[9], char permutation[9]);
void write_outputarray();
void write_outputarray_no_newline();
int update_combination();
void next_swap();

#endif

