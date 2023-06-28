#include "pch.h"
#include "CppUnitTest.h"
#include "../Sudoku/Sudoku.h"
#include <fstream>
#include <iostream>
#include <assert.h>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		TEST_METHOD(gen_over1)
		{
			//生成终局
			Sudoku::gen_over(10); 
			std::ifstream gen;
			gen.open("gened_game.txt");
			Assert::AreEqual(!gen, false);
		}
		TEST_METHOD(gen_over2)
		{
			//生成终局
			Sudoku::gen_over(1000000);
			std::ifstream gen;
			gen.open("gened_game.txt");
			Assert::AreEqual(!gen, false);
		}
		TEST_METHOD(gen_over3)
		{
			//生成终局 参数错误
			Sudoku::gen_over(-1);
			std::ifstream gen;
			gen.open("gened_game.txt");
			Assert::AreEqual(!gen, false);
		}
		TEST_METHOD(gen_game1)
		{
			//生成游戏 -r
			Sudoku::gen_game(10, 3, 55, 55, 1);
			std::ifstream gen;
			gen.open("gen_game.txt");
			Assert::AreEqual(!gen, false);
		}
		TEST_METHOD(gen_game2)
		{
			//生成游戏 -m
			Sudoku::gen_game(10, 3, 0, 0, 1);
			std::ifstream gen;
			gen.open("gen_game.txt");
			Assert::AreEqual(!gen, false);
		}
		TEST_METHOD(gen_game3)
		{
			//生成游戏 -r 参数错误 max<min
			Sudoku::gen_game(10, 3, 55, 45, 1);
			std::ifstream gen;
			gen.open("gen_game.txt");
			Assert::AreEqual(!gen, false);
		}
		TEST_METHOD(gen_game4)
		{
			//生成游戏 无指定
			Sudoku::gen_game(10, 0, 0, 0, 0);
			std::ifstream gen;
			gen.open("gen_game.txt");
			Assert::AreEqual(!gen, false);
		}
		TEST_METHOD(gen_game5)
		{
			//生成游戏
			Sudoku::gen_game(10000, 0, 0, 0, 0);
			std::ifstream gen;
			gen.open("gen_game.txt");
			Assert::AreEqual(!gen, false);
		}
		TEST_METHOD(solve_game1)
		{
			//求解游戏 文件名错误
			Sudoku::solve_game("123");
		}
		TEST_METHOD(solve_game2)
		{
			//求解游戏 按文件求解
			Sudoku::solve_game("game.txt");
			std::ifstream gen;
			gen.open("sudoku.txt");
			Assert::AreEqual(gen.is_open(), true);
		}
	};
}
