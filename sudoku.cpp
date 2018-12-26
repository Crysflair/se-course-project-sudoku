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
		return result; //1~9

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
void visualize_determined_from_valid(bool valid[9][9][10])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int num = check_if_determined(valid[i][j]);
			if (num > 0)
				cout << num << " ";
			else
				cout << "_ ";
		}
		cout << endl;
	}
	cout << endl;
}
void valid_deduction(bool valid[9][9][10], int row, int col, int eliminated_number)
{
	// description: this is a shalow deduction.
	// usage assumption: (i,j) is currently determined as a number.

	// testing:
	if (eliminated_number != check_if_determined(valid[row][col]))
		cout << "elimination uniqueness error!" << endl;
	
	// debug{
	//cout << "deduction called. map(" << row << "," << col << ") = " << eliminated_number << endl;
	//cout << "before elimination:" << endl;
	//visualize_valid_for_num(valid, eliminated_number);
	// debug}

	
	// same row elimination
	for (int j = 0; j < 9; j++)
	{
		if (j == col)
			continue;
		valid[row][j][eliminated_number] = false;		
	}
	// same colomn elimination
	for (int i = 0; i < 9; i++)
	{
		if (i == row)
			continue;
		valid[i][col][eliminated_number] = false;
	}
	// same block elimination
	for (int i = (row / 3) * 3; i < (row / 3) * 3 + 3; i++)
	{
		for (int j = (col / 3) * 3; j < (col / 3) * 3 + 3; j++)
		{
			if (i == row && j == col)
				continue;
			valid[i][j][eliminated_number] = 0;
		}
	}
	// debug{
	//cout << "after elimination:" << endl;
	//visualize_valid_for_num(valid, eliminated_number);
	//cout << "--------------------" << endl;
	return;
	// debug}
}

bool check_no_empty(bool valid[9][9][10])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int tmp = check_if_determined(valid[i][j]);
			if (tmp == 0)
			{
				return false;
			}
		}
	}
	return true;
}

bool determine_num(bool valid[9][9][10],int row,int col, int eliminated_number)
{
	memset(valid[row][col], false, 10);
	valid[row][col][eliminated_number] = true;
	valid_deduction(valid, row, col, eliminated_number);
	return check_no_empty(valid);
}

void second_sweep(bool valid[9][9][10])
{
	int deduction_cnt = 0; 
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int tmp = check_if_determined(valid[i][j]);
			if (tmp > 0)
			{
				determine_num(valid, i, j, tmp);
				deduction_cnt++;
			}
		}
	}cout << "second deduction cnt: " << deduction_cnt << endl;
}

void map_to_valid(bool valid[9][9][10])
{
	// description:
	// 1. this function generate a 'valid' bool matrix for a 'map' char matrix.
	// 2. this 'valid' boolean matrix is deducted.
	
	// at first, every place is possible
	memset(valid, true, sizeof(valid));

	int deduction_cnt = 0;

	// map deduction
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (map[i][j] != '0')
			{
				determine_num(valid, i, j, map[i][j]-'0'); // TODO :check if all single eliminate functions are merged with determine_num.
				deduction_cnt++;
			}
		}
	}cout << "map deduction cnt: " << deduction_cnt << endl;

	// a second sweep
	second_sweep(valid);

}

void restore_matrix(bool valid[9][9][10], bool myvalid[9][9][10])
{
	// only for readability.
	memcpy(myvalid, valid, 810);
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

void find_next_not_determined(bool valid[9][9][10], int row, int col, int& nextrow, int& nextcol)
{
	for (int i = row; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (check_if_determined(valid[i][j]) < 0)
			{
				nextrow = i;
				nextcol = j;
				return;
			}
		}
	}
	nextrow = 9; nextcol = 0;
	return;
}

bool back_track(bool valid[9][9][10], int row, int col)
{
	if (row == 9)
		return true;



	for (int blank = 0; blank < row * 9 + col; blank++) cout << " ";
	cout << "start back track. row,col = " << row << ", " << col << endl;

	int nextrow, nextcol;
	bool myvalid[9][9][10]; memcpy(myvalid, valid, 810);

	for (int num = 1; num <= 9; num++)
	{
		if (valid[row][col][num] == true)
		{
			//set this value
			for (int blank = 0; blank < row * 9 + col; blank++) cout << " ";
			cout << "explore number:" << num << endl;

			if (determine_num(myvalid, row, col, num))
			{

				// print current assumption
				visualize_determined_from_valid(myvalid);

				//explore that value
				find_next_not_determined(myvalid, row, col, nextrow, nextcol);

				if (back_track(myvalid, nextrow, nextcol))
					return true;
				else {
					restore_matrix(valid, myvalid);
					cout << "a failed expand!" << endl;
				}
			}
			else
			{
				restore_matrix(valid, myvalid);
				cout << "a failed determine!" << endl;
			}
		}
		else
			continue;
	}
	return false;
}

bool solve_sudoku()
{
	

	bool valid[9][9][10] = { 0 };
	map_to_valid(valid);

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


