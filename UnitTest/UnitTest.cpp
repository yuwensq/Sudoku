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
			//�����վ�
			Sudoku::gen_over(10); 
			std::ifstream gen;
			gen.open("gened_game.txt");
			Assert::AreEqual(!gen, false);
		}
		TEST_METHOD(gen_over2)
		{
			//�����վ�
			Sudoku::gen_over(1000000);
			std::ifstream gen;
			gen.open("gened_game.txt");
			Assert::AreEqual(!gen, false);
		}
		TEST_METHOD(gen_over3)
		{
			//�����վ� ��������
			Sudoku::gen_over(-1);
			std::ifstream gen;
			gen.open("gened_game.txt");
			Assert::AreEqual(!gen, false);
		}
		TEST_METHOD(gen_game1)
		{
			//������Ϸ -r
			Sudoku::gen_game(10, 3, 55, 55, 1);
			std::ifstream gen;
			gen.open("gen_game.txt");
			Assert::AreEqual(!gen, false);
		}
		TEST_METHOD(gen_game2)
		{
			//������Ϸ -m
			Sudoku::gen_game(10, 3, 0, 0, 1);
			std::ifstream gen;
			gen.open("gen_game.txt");
			Assert::AreEqual(!gen, false);
		}
		TEST_METHOD(gen_game3)
		{
			//������Ϸ -r �������� max<min
			Sudoku::gen_game(10, 3, 55, 45, 1);
			std::ifstream gen;
			gen.open("gen_game.txt");
			Assert::AreEqual(!gen, false);
		}
		TEST_METHOD(gen_game4)
		{
			//������Ϸ ��ָ��
			Sudoku::gen_game(10, 0, 0, 0, 0);
			std::ifstream gen;
			gen.open("gen_game.txt");
			Assert::AreEqual(!gen, false);
		}
		TEST_METHOD(gen_game5)
		{
			//������Ϸ
			Sudoku::gen_game(10000, 0, 0, 0, 0);
			std::ifstream gen;
			gen.open("gen_game.txt");
			Assert::AreEqual(!gen, false);
		}
		TEST_METHOD(solve_game1)
		{
			//�����Ϸ �ļ�������
			Sudoku::solve_game("123");
		}
		TEST_METHOD(solve_game2)
		{
			//�����Ϸ ���ļ����
			Sudoku::solve_game("game.txt");
			std::ifstream gen;
			gen.open("sudoku.txt");
			Assert::AreEqual(gen.is_open(), true);
		}
	};
}
