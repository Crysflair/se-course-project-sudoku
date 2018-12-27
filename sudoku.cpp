// sudoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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

//void cheater()
//{
//	int colswap_test[3][9] = {
//	0,1,2,3,4,5,6,7,8,
//	0,2,1,3,4,5,6,8,7,
//	3,4,5,6,7,8,0,1,2
//	};
//	int rowswap_test[3][9] = {
//		0,1,2,3,4,5,6,7,8,
//		0,2,1,3,4,5,6,8,7,
//		3,4,5,6,7,8,0,1,2
//	};
//	char permutation_test[3][9] = {
//		'1','2','3','4','5','6','9','8','7',
//		'9','5','6','3','2','1','4','7','8',
//		'4','5','6','7','8','1','2','9','3'
//	};
//	for (int i = 0; i < 3; i++)
//	{
//		clear_out_array();
//		append_to_outarray(0, colswap_test[i], rowswap_test[i], permutation_test[i]);
//		cout << outarray;
//	}
//}

int main(int argc, char* argv[])
{
	//cheater();

	if (argc != 3)
	{
		cout << "Input cnt error. please enter '-c integer' or '-s absolute_path'\n";
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
			if (out_puzzles > 10000000)
			{
				cout << "too many sudoku creation! please enter a number smaller than 10000000!\n";
				return 0;
			}
			cout << "generating " << out_puzzles << " sudokus.\n";
			generate_sudoku(out_puzzles);
		}
		else
			cout << "invalid input! please enter an integer smaller than 10000000!\n";

		return 0;
	}
	
	if (strcmp(argv[1], "-s") == 0)
	{
		ifstream puzzles(argv[2]);
		if (puzzles)
		{
			cout << "solving " << argv[2] << endl;
			solve_sudoku_wrapper(puzzles);
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


