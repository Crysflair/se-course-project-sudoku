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
//#include "solve_sudoku.h"

using namespace std;

<<<<<<< HEAD
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
=======
int main()
{
	//timing
	clock_t start, end;
>>>>>>> parent of 1984df4... finish performance optimization

	//solving
	
	start = clock();

	out_puzzle_remain = 10000;
	generate_sudoku();

	//solve_sudoku_wrapper();


	end = clock();	
	double endtime=(double)(end-start)/CLOCKS_PER_SEC;	cout<<"Total time:"<<endtime<<endl;		
	cout<<"Total time:"<<endtime*1000<<"ms"<<endl;	
	system("pause");
	return 0;
}


