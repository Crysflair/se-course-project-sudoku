#include "stdafx.h"
#include "CppUnitTest.h"
#include "../sudoku/generate_sudoku.h"
#include "../sudoku/solve_sudoku.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{		
	TEST_CLASS(Generate_Test)
	{
	public:
		TEST_METHOD(Test_clear_out_array)
		{
			strcpy(outarray, "123412341234");
			clear_out_array();
			Assert::IsTrue(strcmp(outarray, "") == 0);
		}
		TEST_METHOD(Test_append_to_outarray)
		{
			
			int colswap_test[3][9] = {
				0,1,2,3,4,5,6,7,8,
				0,2,1,3,4,5,6,8,7,
				3,4,5,6,7,8,0,1,2
			};
			int rowswap_test[3][9] = {
				0,1,2,3,4,5,6,7,8,
				0,2,1,3,4,5,6,8,7,
				3,4,5,6,7,8,0,1,2
			};
			char permutation_test[3][9] = {
				'1','2','3','4','5','6','9','8','7',
				'9','5','6','3','2','1','4','7','8',
				'4','5','6','7','8','1','2','9','3'
			};
			char answers[3][200] = { 0 };

			strcat(answers[0], "7 6 1 5 9 3 4 8 2\n8 3 4 6 2 7 9 1 5\n2 5 9 1 4 8 3 7 6\n5 8 3 7 6 4 2 9 1\n9 2 7 8 3 1 6 5 4\n1 4 6 2 5 9 7 3 8\n3 9 5 4 8 2 1 6 7\n6 7 2 9 1 5 8 4 3\n4 1 8 3 7 6 5 2 9\n\n");
			strcat(answers[1], "8 9 1 2 4 6 3 5 7\n5 4 2 9 3 7 6 1 8\n7 3 6 1 5 8 4 2 9\n2 6 7 8 1 3 5 9 4\n4 8 5 7 6 9 1 3 2\n9 1 3 5 2 4 8 7 6\n6 2 4 3 7 5 9 8 1\n3 7 9 6 8 1 2 4 5\n1 5 8 4 9 2 7 6 3\n\n");
			strcat(answers[2], "3 1 7 5 2 4 8 9 6\n9 6 4 1 8 7 2 5 3\n5 8 2 3 6 9 4 7 1\n7 9 5 4 1 3 6 2 8\n2 4 8 9 7 6 1 3 5\n6 3 1 8 5 2 7 4 9\n8 2 6 7 9 5 3 1 4\n1 5 3 2 4 8 9 6 7\n4 7 9 6 3 1 5 8 2\n\n");

			for (int i = 0; i < 3; i++)
			{
				clear_out_array();
				append_to_outarray(0, colswap_test[i], rowswap_test[i], permutation_test[i]);
				outarray[outarray_cur] = '\0';

				Assert::IsTrue(strcmp(outarray, answers[i])==0);
				
			}
					
		}
		TEST_METHOD(Test_update_combination)
		{
			int rowswap_test[3][9] = {
			{0,1,2,3,4,5,8,7,6},
			{0,1,2,3,4,5,8,6,7},
			{0,1,2,3,4,5,6,8,7}
			};
			for (int i = 0; i < 3; i++)
			{
				update_combination();
				for (int k = 0; k < 9; k++)
				{
					Assert::IsTrue(rowswap[k] == rowswap_test[i][k]);
				}
			}
		}
		TEST_METHOD(Test_my_swap) 
		{
			char test_a[10] = {1,4,3,5,-2,6,4,7,5,8};
			char test_b[10] = { 9,8,2,7,5,6,4,3,1,66};
			for (int i = 0; i < 10; i++)
			{
				char pre_a = test_a[i];
				char pre_b = test_b[i];
				my_swap(test_a[i], test_b[i]);
				Assert::IsTrue(pre_a == test_b[i] && pre_b == test_a[i]);
			}
		}
		TEST_METHOD(Test_generate_sudoku)
		{
			long int gener_num[5] = { 1, 100, 1000, 23223, 666 };
			for (int i = 0; i < 5; i++)
			{
				Assert::IsTrue(generate_sudoku(gener_num[i]) == 0);
			}
		}
	};

	TEST_CLASS(Solve_Test)
	{
	private:
		void set_test_sudoku(int test_sudoku[9][9])
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if(test_sudoku[i][j] > 0)
						set_number(i, j, test_sudoku[i][j]);
				}
			}
		}
	public:
		TEST_METHOD(Test_refresh)
		{
			refresh_everything();
			for (int unit = 0; unit < 9; unit++)
			{
				for (int num = 1; num <= 9; num++)
				{
					Assert::IsTrue(rows_available[unit][num] == true, L"rows refresh error!");
					Assert::IsTrue(cols_available[unit][num] == true, L"cols refresh error!");
					Assert::IsTrue(block_available[unit][num] == true, L"block refresh error!");
				}
			}
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					Assert::IsTrue(ans[i][j] == 0, L"ans refreash error!");
				}
			}
		}
		TEST_METHOD(Test_set_number)
		{
			set_number(3, 3, 3);
			Assert::IsTrue(ans[3][3] == 3);
			Assert::IsTrue(rows_available[3][3] == false);
			Assert::IsTrue(cols_available[3][3] == false);
			Assert::IsTrue(block_available[4][3] == false);

			set_number(0, 8, 3);
			Assert::IsTrue(ans[0][8] == 3);
			Assert::IsTrue(rows_available[0][3] == false);
			Assert::IsTrue(cols_available[8][3] == false);
			Assert::IsTrue(block_available[6][3] == false);
		}
		TEST_METHOD(Test_get_next_to_fill)
		{
			int ans_test[9][9] = {
				7, 6, 1, 5, 9, 3, 4, 8, 2,
				8, 3, 0, 6, 2, 7, 9, 1, 5,
				2, 5, 9, 1, 4, 8, 3, 7, 6,
				5, 8, 3, 0, 6, 0, 2, 9, 1,
				9, 2, 0, 8, 3, 0, 6, 5, 4,
				1, 4, 0, 2, 5, 9, 7, 3, 8,
				3, 9, 5, 4, 8, 2, 1, 6, 7,
				6, 7, 2, 9, 1, 5, 8, 4, 3,
				4, 1, 8, 3, 7, 6, 5, 2, 9
			};
			memcpy(ans, ans_test, sizeof(ans_test[0][0]) * 81);
			int nextrow, nextcol;

			get_next_to_fill(0, 0, nextrow, nextcol);
			Assert::IsTrue(nextrow == 1 && nextcol == 2);
			get_next_to_fill(0, 1, nextrow, nextcol);
			Assert::IsTrue(nextrow == 1 && nextcol == 2);
			get_next_to_fill(3, 3, nextrow, nextcol);
			Assert::IsTrue(nextrow == 3 && nextcol == 3);
			get_next_to_fill(3, 4, nextrow, nextcol);
			Assert::IsTrue(nextrow == 3 && nextcol == 3);
			get_next_to_fill(8, 0, nextrow, nextcol);
			Assert::IsTrue(nextrow == 9 && nextcol == 0);
		}
		TEST_METHOD(Test_if_valid)
		{
			refresh_everything();
			set_number(0, 0, 1);
			set_number(0, 1, 2);

			Assert::IsFalse(if_valid(0, 0, 1));
			Assert::IsFalse(if_valid(1, 1, 2));
			Assert::IsTrue(if_valid(0, 1, 3));
			Assert::IsTrue(if_valid(8, 0, 2));

		}
		TEST_METHOD(Test_revert_number)
		{
			revert_number(3, 4, 5);
			Assert::IsTrue(ans[3][4] == 0);
			Assert::IsTrue(rows_available[3][5]);
			Assert::IsTrue(cols_available[4][5]);
			Assert::IsTrue(block_available[4][5]);

			revert_number(8, 8, 9);
			Assert::IsTrue(ans[8][8] == 0);
			Assert::IsTrue(rows_available[8][9]);
			Assert::IsTrue(cols_available[8][9]);
			Assert::IsTrue(block_available[8][9]);

			revert_number(1, 6, 6);
			Assert::IsTrue(ans[1][6] == 0);
			Assert::IsTrue(rows_available[1][6]);
			Assert::IsTrue(cols_available[6][6]);
			Assert::IsTrue(block_available[2][6]);
		}
		
		TEST_METHOD(Test_solve_sudoku)
		{
			int test_puzzles[3][9][9] = {
					3, 0, 7, 5, 2, 4, 8, 0, 0,
					0, 0, 4, 0, 8, 7, 2, 5, 0,
					5, 8, 2, 0, 0, 0, 4, 7, 0,
					7, 0, 5, 4, 0, 0, 0, 2, 8,
					2, 4, 8, 0, 7, 0, 0, 0, 5,
					0, 0, 0, 8, 5, 2, 7, 4, 0,
					8, 2, 0, 7, 0, 5, 0, 1, 4,
					1, 5, 3, 2, 4, 8, 9, 6, 7,
					4, 7, 9, 6, 3, 1, 5, 8, 2,

					7, 6, 1, 5, 9, 0, 0, 0, 0,
					0, 3, 4, 6, 2, 0, 9, 0, 0,
					0, 5, 9, 1, 4, 0, 0, 0, 6,
					0, 8, 3, 7, 6, 0, 0, 9, 0,
					0, 2, 7, 8, 3, 0, 6, 0, 0,
					0, 4, 6, 2, 5, 9, 0, 0, 0,
					0, 9, 5, 4, 8, 0, 0, 6, 0,
					0, 7, 2, 9, 1, 0, 0, 0, 0,
					0, 1, 8, 3, 7, 6, 0, 0, 9,

					7, 0, 0, 0, 0, 3, 4, 9, 2,
					0, 0, 0, 0, 0, 7, 6, 1, 5,
					0, 0, 0, 0, 0, 9, 3, 7, 8,
					0, 0, 0, 0, 0, 4, 2, 6, 1,
					0, 0, 0, 0, 0, 1, 8, 5, 4,
					1, 4, 8, 2, 5, 6, 7, 3, 9,
					3, 6, 5, 4, 9, 2, 0, 0, 0,
					8, 7, 2, 6, 1, 5, 0, 0, 0,
					4, 1, 9, 3, 7, 8, 0, 0, 6
			};

			for (int test = 0; test < 3; test++)
			{
				refresh_everything();
				this -> set_test_sudoku(test_puzzles[test]);
				int nextrow = 0, nextcol = 0;
				get_next_to_fill(0, 0, nextrow, nextcol);
				Assert::IsTrue(solve_sudoku(nextrow, nextcol));
			}
		}
	};
}