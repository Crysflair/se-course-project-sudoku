#pragma once

#ifndef GENERATE_SUDOKU_H
#define GENERATE_SUDOKU_H

<<<<<<< HEAD
=======
extern int out_puzzle_remain;
void generate_sudoku();
>>>>>>> parent of 1984df4... finish performance optimization

extern char outarray[];
extern int outarray_cur;
//extern long int out_puzzle_remain;
//
//
//extern char permutation[9];
//extern int colswap[9];
//extern int rowswap[9];
//
void clear_out_array();
void append_to_outarray(int seed_num, int colswap[9], int rowswap[9], char permutation[9]);
//int update_combination();
//
//extern int seed_cur;
//// void my_swap(char &a, char &b); 
//// TODO : see if need to include sub function in header.
//
//void clear_out_array();
//void write_outputarray();
//void write_outputarray_no_newline();
//int update_combination();
//void next_swap();

void generate_sudoku(long int);
#endif

