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

int main()
{
	//timing
	clock_t start, end;

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


