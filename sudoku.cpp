// sudoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// tags:
//		RUN: mute debug or checking
//		TODO: things to debug or note

#include "pch.h"
#include <iostream>
#include <ctime>
#include "generate_sudoku.h"

using namespace std;

void generate_sudoku() {
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
}

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

}


