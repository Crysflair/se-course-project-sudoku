
#include "pch.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

extern const int SEED_CNT = 5;
extern const long OUTARRSIZE = 1000;

char outarray[OUTARRSIZE] = { 0 };
int outarray_cur = 0;
int out_puzzle_remain = 0;
ofstream outarray_file;

char permutation[9] = { '1','2','3','4','5','6','9','8', '7' };
int colswap[9] = { 0,1,2,3,4,5,6,7,8 };
int rowswap[9] = { 0,1,2,3,4,5,6,7,8 };
int combination_345[6][3] = {
	3,4,5,
	5,4,3,
	5,3,4,
	3,5,4,
	4,3,5,
	4,5,3
};
int combination_678[6][3] = {
	6,7,8,
	8,7,6,
	8,6,7,
	6,8,7,
	7,6,8,
	7,8,6,
};

int seed_cur = 0;
char seeds[SEED_CNT][9][9] = {
'7', '6', '1', '5', '9', '3', '4', '8', '2',
'8', '3', '4', '6', '2', '7', '9', '1', '5',
'2', '5', '9', '1', '4', '8', '3', '7', '6',
'5', '8', '3', '7', '6', '4', '2', '9', '1',
'9', '2', '7', '8', '3', '1', '6', '5', '4',
'1', '4', '6', '2', '5', '9', '7', '3', '8',
'3', '9', '5', '4', '8', '2', '1', '6', '7',
'6', '7', '2', '9', '1', '5', '8', '4', '3',
'4', '1', '8', '3', '7', '6', '5', '2', '9',

'7', '3', '9', '8', '1', '6', '5', '2', '4',
'5', '6', '1', '4', '9', '2', '7', '8', '3',
'2', '8', '4', '3', '7', '5', '1', '6', '9',
'8', '1', '7', '6', '3', '9', '4', '5', '2',
'3', '4', '5', '2', '8', '7', '9', '1', '6',
'6', '9', '2', '5', '4', '1', '3', '7', '8',
'4', '5', '3', '7', '2', '8', '6', '9', '1',
'1', '7', '8', '9', '6', '3', '2', '4', '5',
'9', '2', '6', '1', '5', '4', '8', '3', '7',

'7', '8', '5', '4', '9', '2', '3', '6', '1',
'1', '6', '3', '8', '7', '5', '4', '9', '2',
'4', '2', '9', '3', '6', '1', '8', '7', '5',
'8', '5', '7', '2', '1', '6', '9', '4', '3',
'6', '3', '1', '9', '4', '7', '5', '2', '8',
'2', '9', '4', '5', '3', '8', '7', '1', '6',
'9', '4', '2', '6', '8', '3', '1', '5', '7',
'3', '1', '6', '7', '5', '9', '2', '8', '4',
'5', '7', '8', '1', '2', '4', '6', '3', '9',

'7', '8', '6', '4', '2', '1', '9', '3', '5',
'4', '3', '9', '7', '5', '8', '6', '2', '1',
'2', '5', '1', '9', '3', '6', '7', '4', '8',
'5', '1', '8', '2', '6', '3', '4', '9', '7',
'3', '2', '4', '5', '7', '9', '8', '1', '6',
'9', '6', '7', '1', '8', '4', '3', '5', '2',
'6', '7', '2', '3', '9', '5', '1', '8', '4',
'1', '9', '5', '8', '4', '7', '2', '6', '3',
'8', '4', '3', '6', '1', '2', '5', '7', '9',

'7', '2', '9', '8', '6', '3', '5', '1', '4',
'4', '6', '1', '2', '9', '5', '3', '8', '7',
'3', '8', '5', '4', '1', '7', '9', '6', '2',
'9', '3', '4', '1', '8', '6', '7', '2', '5',
'6', '7', '2', '5', '3', '9', '1', '4', '8',
'1', '5', '8', '7', '4', '2', '6', '9', '3',
'8', '4', '3', '6', '7', '1', '2', '5', '9',
'5', '1', '7', '9', '2', '4', '8', '3', '6',
'2', '9', '6', '3', '5', '8', '4', '7', '1'


};

void append_to_outarray(int seed_num, int colswap[9], int rowswap[9], char permutation[9])
{
	// usage assumption: 
	// 1. colswap, rowswap, and permutation are valid:
	//		colswap and rowswap: avoid swapping the first number.
	//		permutation: **** **^* 7.
	// 2. outarray has enough space.
	// description:
	// 1. append a sudoku question filled to outarray.

	// global: outarray, outarray_cur, seeds

	// warning: this function always end with a blank line.

	// checking
	if (seed_num > SEED_CNT || outarray_cur > OUTARRSIZE - 200)
		cout << "error!" << endl;

	// TODO: if std or self actualization is faster?
	swap(permutation[6], permutation[8]);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			char number_origin = seeds[seed_num][rowswap[i]][colswap[j]];
			int number_permu = permutation[number_origin - '1'];
			outarray[outarray_cur++] = number_permu;
			outarray[outarray_cur++] = ' ';
		}
		outarray_cur--;
		outarray[outarray_cur++] = '\n';
	}
	outarray[outarray_cur++] = '\n';

	swap(permutation[6], permutation[8]);
}

void write_outputarray()
{
	// usage assumption: 
	// 1. outarray not empty
	// 2. this is not the last puzzle. NOTE

	// description: 
	// 1. called when outarray runs out of space
	// 2. output it and reset outarray.

	// TODO : test output to file

	// global: outarray, outarray_cur

	// RUN
	// checking
	//if (outarray_cur < 50 || out_puzzle_remain < 1)
	//	cout << "error!" << endl;
	//else
	//	cout << "clear space with new line" << endl;

	outarray[outarray_cur] = '\0';
	outarray_file << outarray;
	outarray_cur = 0;
}

void write_outputarray_no_newline()
{
	// usage assumption: 
	// 1. outarray not empty
	// 2. this is the last puzzle.
	// description: 
	// 1. called when outarray runs out of space, output it and reset outarray.

	// TODO : test output to file

	// global: outarray, outarray_cur

	// checking
	if (outarray_cur < 50 || out_puzzle_remain != 0)
		cout << "error!" << endl;
	else
		cout << "write no new line" << endl;

	outarray_cur -= 2; // TODO: is a '\n' needed?
	outarray[outarray_cur] = '\0';
	outarray_file << outarray;
	outarray_cur = 0;
}

int update_combination()
{
	//description: 
	//1. update col/row's cur/array
	//2. return 1 when succeed.
	//3. if exhausted, reset everything and return 0;

	//global: rowswap, colswap;

	static int col12_cur = 0, col345_cur = 0, col678_cur = 0;
	static int row12_cur = 0, row345_cur = 0, row678_cur = 0;

	if (row678_cur < 5)
	{
		row678_cur++;
		rowswap[6] = combination_678[row678_cur][0];
		rowswap[7] = combination_678[row678_cur][1];
		rowswap[8] = combination_678[row678_cur][2];
		return 1;
	}
	else {
		row678_cur = 0;
		rowswap[6] = combination_678[row678_cur][0];
		rowswap[7] = combination_678[row678_cur][1];
		rowswap[8] = combination_678[row678_cur][2];
	}


	if (row345_cur < 5)
	{
		row345_cur++;
		rowswap[3] = combination_345[row345_cur][0];
		rowswap[4] = combination_345[row345_cur][1];
		rowswap[5] = combination_345[row345_cur][2];
		return 1;
	}
	else {
		row345_cur = 0;
		rowswap[3] = combination_345[row345_cur][0];
		rowswap[4] = combination_345[row345_cur][1];
		rowswap[5] = combination_345[row345_cur][2];
	}

	if (col678_cur < 5)
	{
		col678_cur++;
		colswap[6] = combination_678[col678_cur][0];
		colswap[7] = combination_678[col678_cur][1];
		colswap[8] = combination_678[col678_cur][2];
		return 1;
	}
	else {
		col678_cur = 0;
		colswap[6] = combination_678[col678_cur][0];
		colswap[7] = combination_678[col678_cur][1];
		colswap[8] = combination_678[col678_cur][2];
	}

	if (col345_cur < 5)
	{
		col345_cur++;
		colswap[3] = combination_345[col345_cur][0];
		colswap[4] = combination_345[col345_cur][1];
		colswap[5] = combination_345[col345_cur][2];
		return 1;
	}
	else {
		col345_cur = 0;
		colswap[3] = combination_345[col345_cur][0];
		colswap[4] = combination_345[col345_cur][1];
		colswap[5] = combination_345[col345_cur][2];
	}

	if (col12_cur == 0)
	{
		col12_cur++;
		colswap[2] = 1;
		colswap[1] = 2;
		return 1;
	}
	else {
		col12_cur = 0;
		colswap[1] = 1;
		colswap[2] = 2;
	}

	if (row12_cur == 0)
	{
		row12_cur++;
		rowswap[2] = 1;
		rowswap[1] = 2;
		return 1;
	}
	else {
		row12_cur = 0;
		rowswap[2] = 2;
		rowswap[1] = 1;
	}

	cout << "combination exhausted!" << endl;

	col12_cur = 0, col345_cur = 0, col678_cur = 0;
	row12_cur = 0, row345_cur = 0, row678_cur = 0;
	for (int i = 0; i < 9; i++)
	{
		colswap[i] = i;
		rowswap[i] = i;
	}
	return 0;
}

void next_swap()
{
	// description: 
	// 1. aim: get next sudoku
	// 2. if exhausted: reset and start at the beginning.
	// 3. method: permutation -> col/row's combination -> change seed.

	if (next_permutation(permutation, permutation + 8))
		return;

	// if fails, reset permutation and update combination
	sort(permutation, permutation + 8);
	if (update_combination())
		return;

	// if fails, reset combination(done in update_combination()) and update seeds in a circle.
	seed_cur += 1;
	seed_cur = seed_cur % SEED_CNT;
}

void generate_sudoku() {

	ofstream outarray_file("sudoku.txt");

	while (out_puzzle_remain > 0)
	{
		append_to_outarray(seed_cur, colswap, rowswap, permutation);
		out_puzzle_remain--;

		if (out_puzzle_remain == 0)
		{
			write_outputarray_no_newline();
			break;
		}
		else if (outarray_cur > OUTARRSIZE - 200)
			write_outputarray();

		next_swap();
	}
	outarray_file.flush();
	outarray_file.close();

	return;
}