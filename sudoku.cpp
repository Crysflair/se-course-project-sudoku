// sudoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// tags:
//		RUN: mute debug or checking
//		TODO: things to debug or note

#include "pch.h"
#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include "generate_sudoku.h"

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
	for(int i = row; i<9;i++)
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

void visualize_ans()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (ans[i][j] == 0)
				cout << "_ ";
			else
				cout << ans[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void output_ans()
{
	char buffer[200];
	int buffer_cur = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			buffer[buffer_cur++] = ans[i][j];
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

			cout << "set number " << num << " at (" << row << ", " << col << "). after setting:" << endl;
			visualize_ans();

			int nextrow, nextcol; get_next_to_fill(row, col, nextrow, nextcol);
			if (solve_sudoku(nextrow, nextcol))
				return true;
			else
			{	
				cout << "oh, failed expand" << endl;
				revert_number(row, col, num);
			}
		}
	}
	return false;
}

ofstream solutions;

int main()
{
	//timing
	clock_t start, end;
	start = clock();

	out_puzzle_remain = 100;
	//generate_sudoku();

	//timing
	end = clock();	
	double endtime=(double)(end-start)/CLOCKS_PER_SEC;	cout<<"Total time:"<<endtime<<endl;		
	cout<<"Total time:"<<endtime*1000<<"ms"<<endl;	
	system("pause");

	//solving
	ifstream puzzles("puzzles.txt");
	char line_buffer[20] = { 0 };

	
	ofstream solutions("solutions.txt");

	bool is_first_puzzle = true;
	while (puzzles)
	{
		// read a puzzle
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
			if (!is_first_puzzle)
				solutions << "\n\n";
			output_ans();
		}
		else
			cout << "error";
	}
	puzzles.close();


}


