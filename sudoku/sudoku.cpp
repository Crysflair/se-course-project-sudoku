﻿// sudoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// tags:
//		RUN: mute debug or checking
//		TODO: things to debug or note

#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include "generate_sudoku.h"
#include "solve_sudoku.h"

using namespace std;


int main(int argc, char* argv[])
{

	if (argc != 3)
	{
		cout << "Input cnt error. please enter '-c integer' or '-s absolute_path'\n";
		return 0;
	}
	if (strcmp(argv[1], "-c") == 0)
	{
		long int out_puzzles = 0;

		int len = strlen(argv[2]);
		bool is_integer = true;

		if (len > 9) is_integer = false;
		else {
			for (int i = 0; i < len; i++)
			{
				if (argv[2][i] >= '0' && argv[2][i] <= '9')
					continue;
				else {
					is_integer = false;
					break;
				}
			}
		}

		if (is_integer)
		{
			sscanf_s(argv[2], "%ld", &out_puzzles);
			if (out_puzzles > 10000000 || out_puzzles < 1)
			{
				cout << "please enter a number smaller among 1 to 10000000!\n";
				return 0;
			}
			cout << "generating " << out_puzzles << " sudokus.\n";
			generate_sudoku(out_puzzles);
		}
		else
			cout << "invalid input! please enter an integer among 1 to 10000000!\n";

		return 0;
	}
	
	if (strcmp(argv[1], "-s") == 0)
	{
		ifstream puzzles(argv[2]);
		if (puzzles)
		{
			cout << "solving " << argv[2] << endl;
			solve_sudoku_wrapper(puzzles);
			return 0;
		}
		else
			cout << "unable to open the file. please enter a valid file path.\n";

		return 0;
	}

	else { // not -s nor -c
		cout << "Input error(2). please enter '-c integer' or '-s absolute_path'\n";
	}

	return 0;
}


