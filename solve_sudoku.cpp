#include "pch.h"
#include <iostream>
#include <cstring>
#include <fstream>


using namespace std;

bool rows_available[9][10] = { true };
bool cols_available[9][10] = { true };
bool block_available[9][10] = { true };
int ans[9][9] = { 0 };


void refresh_everything()
{
	memset(rows_available, true, 90);
	memset(cols_available, true, 90);
	memset(block_available, true, 90);
	memset(ans, 0, 81);
}

void set_number(int row, int col, int num)
{
	ans[row][col] = num;
	rows_available[row][num] = false;
	cols_available[col][num] = false;
	block_available[row / 3 * 3 + col / 3][num] = false;
}

void get_next_to_fill(int row, int col, int& nextrow, int& nextcol)
{
	for (int i = row; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			if (ans[i][j] == 0)
			{
				nextrow = i; nextcol = j;
				return;
			}
		}
	nextrow = 9; return;
}

bool if_valid(int row, int col, int num)
{
	if (rows_available[row][num] == false || cols_available[col][num] == false || block_available[row / 3 * 3 + col / 3][num] == false)
		return false;
	else return true;
}

void revert_number(int row, int col, int num)
{
	ans[row][col] = 0;
	rows_available[row][num] = true;
	cols_available[col][num] = true;
	block_available[row / 3 * 3 + col / 3][num] = true;
}

void output_ans(ofstream & solutions)
{
	char buffer[200];
	int buffer_cur = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			buffer[buffer_cur++] = ans[i][j] + '0';
			buffer[buffer_cur++] = ' ';
		}
		buffer_cur--;
		buffer[buffer_cur++] = '\n';
	}
	buffer_cur--;
	buffer[buffer_cur] = '\0';

	solutions << buffer;

}

bool solve_sudoku(int row, int col)
{
	if (row == 9)
	{// finish back tracking! 
		return true;
	}

	for (int num = 1; num < 10; num++)
	{
		if (if_valid(row, col, num))
		{
			set_number(row, col, num);
			int nextrow, nextcol; get_next_to_fill(row, col, nextrow, nextcol);
			if (solve_sudoku(nextrow, nextcol))
				return true;
			else
			{
				revert_number(row, col, num);
			}
		}
	}
	return false;
}


void solve_sudoku_wrapper()
{
	ifstream puzzles("puzzles.txt");
	char line_buffer[20] = { 0 };


	ofstream solutions("solutions.txt");

	bool is_first_puzzle = true;
	long puzzles_cnt = 0;
	while (puzzles)
	{
		// read a puzzle
		puzzles_cnt++;
		refresh_everything();
		for (int i = 0; i < 9; i++)
		{
			puzzles.getline(line_buffer, 20);
			for (int j = 0; j < 9; j++)
			{
				if (line_buffer[2 * j] - '0' > 0)
					set_number(i, j, line_buffer[2 * j] - '0');
			}
		}

		// get blank line, or sense eof.
		puzzles.getline(line_buffer, 20);

		// solve it!
		int row, col;
		get_next_to_fill(0, 0, row, col);
		if (solve_sudoku(row, col))
		{
			if (is_first_puzzle)
			{
				output_ans(solutions);
				is_first_puzzle = false;
			}
			else {
				solutions << "\n\n";
				output_ans(solutions);
			}
		}
		else
			cout << "error";
	}
	puzzles.close();
	solutions.close();

	cout << "solved " << puzzles_cnt << " puzzles." << endl;
}

