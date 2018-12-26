// sudoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// tags:
//		RUN: mute debug or checking
//		TODO: things to debug or note

#include "pch.h"
#include <iostream>
#include <ctime>
#include <cstring>
#include "generate_sudoku.h"
using namespace std;

char map[9][10] = { 0 };
char map_ans[200] = { 0 };

bool valid[9][9][10] = { 0 }; //row, column, number(1~9)

int check_if_determined(bool valid_x_y[10])
{
	int result = -1;
	int hitcnt = 0;

	for (int num = 1; num <= 9; num++)
	{
		if (valid_x_y[num] == true)
		{
			result = num;
			hitcnt++;
			if (hitcnt > 1)
			{
				return -1;
			}
		}
	}

	if (hitcnt == 1)
		return result;

	// checking
	if (hitcnt == 0)
	{
		cout << "empty possibility for gird" << endl;
	}
	else
	{
		cout << "too many hits"<<hitcnt<< endl;
	}

	// default -1 or a value.
	return -1;
}
void visualize_valid_for_grid(bool valid[9][9][10], int row, int col)
{
	cout << "visualize validarray for grid (" << row << ", " << col << ")\n";
	for (int num = 1; num <= 9; num++)
	{
		if (valid[row][col][num] == true)
			cout << "O ";
		else
			cout << "_ ";
	}
	cout << endl;
}
void visualize_valid_for_num(bool valid[9][9][10], int num)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (valid[i][j][num] == true)
				cout << "O ";
			else
				cout << "_ ";
		}
		cout << endl;
	}
}

void valid_deduction(bool valid[9][9][10], int row, int col, int eliminated_number)
{
	// usage assumption: (i,j) is currently determined as a number.

	// testing:
	if (eliminated_number != check_if_determined(valid[row][col]))
		cout << "elimination uniqueness error!" << endl;
	
	// debug{
	cout << "deduction called. map(" << row << "," << col << ") = " << eliminated_number << endl;
	cout << "before elimination:" << endl;
	visualize_valid_for_num(valid, eliminated_number);
	// debug}


	int tmp = -1;
	// same row elimination
	for (int j = 0; j < 9; j++)
	{
		if (j == col)
			continue;
		valid[row][j][eliminated_number] = false;
		tmp = check_if_determined(valid[row][j]);
		if (tmp > 0)
			valid_deduction(valid, row, j, tmp);
		else if (tmp == 0) {
			visualize_valid_for_grid(valid, row, j);
		}
		
	}
	// same colomn elimination
	for (int i = 0; i < 9; i++)
	{
		if (i == row)
			continue;
		valid[i][col][eliminated_number] = false;
		tmp = check_if_determined(valid[i][col]);
		if (tmp > -1)
			valid_deduction(valid, i, col, tmp);
		else if (tmp == 0) {
			visualize_valid_for_grid(valid, i, col);
		}
	}
	// same block elimination
	for (int i = (row / 3) * 3; i < (row / 3) * 3 + 3; i++)
	{
		for (int j = (col / 3) * 3; j < (col / 3) * 3 + 3; j++)
		{
			if (i == row && j == col)
				continue;
			valid[i][j][eliminated_number] = 0;
			tmp = check_if_determined(valid[i][j]);
			if (tmp > -1)
				valid_deduction(valid, i, j, tmp);
			else if (tmp==0) {
				visualize_valid_for_grid(valid, i, j);
			}
		}
	}

	// debug{
	cout << "after elimination:" << endl;
	visualize_valid_for_num(valid, eliminated_number);
	cout << "--------------------" << endl;
	return;
	// debug}
}

void determine_num(bool valid_x_y[10], int eliminated_number)
{
	memset(valid_x_y, false, 10);
	valid_x_y[eliminated_number] = true;
}

void map_to_valid()
{
	// description:
	// 1. this function generate a 'valid' bool matrix for a 'map' char matrix.
	// 2. this 'valid' boolean matrix is deducted.
	
	// at first, every place is possible
	memset(valid, true, sizeof(valid));

	// if reward testing variable
	int root_deduction_cnt = 0;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (map[i][j] != '0')
			{
				determine_num(valid[i][j], map[i][j]-'0');
				valid_deduction(valid, i, j, map[i][j] - '0');
				root_deduction_cnt++;
			}
		}
	}

	cout << "among all deductions," << root_deduction_cnt << " is trivial" << endl;
}

void restore_number(bool valid_x_y[10], bool myvalid_x_y[10])
{
	// only for readability.
	memcpy(myvalid_x_y, valid_x_y, 10);
}

void valid_to_map_ans(bool valid[9][9][10])
{
	// description:
	// 1. write to map_ans from the begining
	// 2. with a blank line!
	// 3. end with '\0'.

	// TODO delete the line in ifstream.

	int map_ans_cur = 0;
	int tmp;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			tmp = check_if_determined(valid[i][j]);
			if (tmp == -1)
				cout << "error!\n";

			map_ans[map_ans_cur++] = '0' + tmp;
			map_ans[map_ans_cur++] = ' ';
		}
		map_ans_cur--;
		map_ans[map_ans_cur++] = '\n';
	}
	map_ans[map_ans_cur++] = '\n';
	map_ans[map_ans_cur++] = '\0';
}

bool back_track(bool valid[9][9][10], int row, int col)
{
	if (row == 9)
	{
		// finish working!
		valid_to_map_ans(valid);
		return true;
	}

	// start back tracking
	bool myvalid[9][9][10]; memcpy(myvalid, valid, 810);
	
	int nextrow, nextcol;
	if (col < 9)
	{
		nextrow = row;
		nextcol = col + 1;
	}
	else
	{
		nextrow = row + 1;
		nextcol = 0;
	}

	for (int num = 1; num <= 9; num++)
	{
		if (valid[row][col][num] == true)
		{
			//explore that value
			determine_num(myvalid[row][col], num);
			if (back_track(myvalid, nextrow, nextcol))
				return true;
			else {
				restore_number(valid[row][col], myvalid[row][col]);
				continue;
			}
		}
		else
			continue;
	}
	return false;
}

bool solve_sudoku()
{
	map_to_valid();

	bool is_succeed = back_track(valid, 0, 0);

	// some boring prints
	if (!is_succeed)
		cout << "no solution!" << endl;
	else
		cout << "good, now you can write the output interpreter!" << endl;

	return is_succeed;
}


int main()
{
	//timing
	/*
	clock_t start, end;
	start = clock();

	out_puzzle_remain = 100;
	generate_sudoku();

	//timing
	end = clock();	
	double endtime=(double)(end-start)/CLOCKS_PER_SEC;	cout<<"Total time:"<<endtime<<endl;		
	cout<<"Total time:"<<endtime*1000<<"ms"<<endl;	
	system("pause");
	*/

	// START SOLVING
	ifstream puzzles("test_sudoku.txt");
	ofstream answers("answers_of_test_sudoku.txt");
	char line_buffer[20] = { 0 };
	

	while (puzzles)
	{
		// read a puzzle
		for (int i = 0; i < 9; i++)
		{
			puzzles.getline(line_buffer, 20);
			
			map[i][0] = line_buffer[0];
			map[i][1] = line_buffer[2];
			map[i][2] = line_buffer[4];
			map[i][3] = line_buffer[6];
			map[i][4] = line_buffer[8];
			map[i][5] = line_buffer[10];
			map[i][6] = line_buffer[12];
			map[i][7] = line_buffer[14];
			map[i][8] = line_buffer[16];
		}
		puzzles.getline(line_buffer, 20);
		
		// solve map
		if (solve_sudoku())
			answers << map_ans;
		else
			cout << "no solution!" << endl;


	}
	










}


