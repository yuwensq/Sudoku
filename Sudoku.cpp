#include "Sudoku.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdlib.h>
#include <time.h> 

#define SOV_TARGET_PATH "sudoku.txt"
#define GEN_OVER_TARGET_PATH "gened_game.txt"
#define GEN_GAME_TARGET_PATH "gen_game.txt"
//#define DEBUG_SUDOKU

void Sudoku::print_chess_borad(int chess_board[9][9], std::ofstream& output) {
	std::string s = "";
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (chess_board[i][j] != 0)
				s += (char)('0' + chess_board[i][j]);
			else
				s += '$';
		}
		s += '\n';
	}
	s += '\n';
	output << s;
}
bool Sudoku::is_legal(int chess_board[9][9], int i, int j, int k) {

	assert(k >= 1 && k <= 9);
	int i_start = i - i % 3;
	int j_start = j - j % 3; // 所处的九宫格的左上方的坐标
	for (int o = 0; o < 9; o++)
		if (chess_board[i][o] == k || chess_board[o][j] == k || chess_board[i_start + o / 3][j_start + o % 3] == k)
			return false;
	return true;
}

bool Sudoku::solve(int chess_board[9][9], std::vector<std::pair<int, int>>& zeros, int pos) {
	if (pos == zeros.size())
		return true;
	bool res = false;
	int i = zeros[pos].first;
	int j = zeros[pos].second;
	for (int k = 1; k <= 9; k++) {
		if (!is_legal(chess_board, i, j, k))
			continue;
		chess_board[i][j] = k;
		res = solve(chess_board, zeros, pos + 1);
		if (res == true) // 找到力
			break;
		chess_board[i][j] = 0; // 没找到就清零，这样的话最终如果没有解，也不会被填数字
	}
	return res;
}

bool Sudoku::solve_single_game(int chess_board[9][9], bool change_chess) {
	int(*chess_b)[9] = chess_board;
	bool res = false;
	if (change_chess == false) {
		int chess_size = 81 * sizeof(int);
		chess_b = (int(*)[9])malloc(chess_size);
		memcpy(chess_b, chess_board, chess_size);
#ifdef DEBUG_SUDOKU
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				if (chess_b[i][j] != chess_board[i][j])
					std::cout << "复制错误" << std::endl;
#endif
	}
	std::vector<std::pair<int, int>> zeros; // 记录棋盘中空格的位置
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (chess_b[i][j] == 0)
				zeros.push_back(std::make_pair(i, j));
	res = solve(chess_b, zeros, 0);
	if (change_chess == false) {
		free(chess_b);
	}
	return res;
}

void Sudoku::gen_single_over(int chess_board[9][9]) {
	static int offset[] = { 0, 3, 6, 1, 7, 4, 2, 5, 8 }; // 这个是不是定义成全局变量比较好？
	static int first_row[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	static int bunch[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			chess_board[i][j] = first_row[(j + offset[bunch[i]]) % 9];

	int start = 1, end = 2;
	bool no_need_carry = true;
	no_need_carry = std::next_permutation(bunch + 1, bunch + 3);
	if (no_need_carry)
		goto END;
	no_need_carry = std::next_permutation(bunch + 3, bunch + 6);
	if (no_need_carry)
		goto RESET;
	end += 3;
	no_need_carry = std::next_permutation(bunch + 6, bunch + 9);
	if (no_need_carry)
		goto RESET;
	end += 3;
	no_need_carry = std::next_permutation(first_row, first_row + 9); // 这个要是再进位就没办法了
	assert(no_need_carry);

RESET:
	for (int i = start; i <= end; i++)
		bunch[i] = i;
END:
	return;
}

void Sudoku::solve_game(std::string source_path) {
	std::cout << "开始求解数独，文件路径: " << source_path << std::endl;
	std::ifstream input;
	input.open(source_path);
	char c;
	int chess_num = 0;
	int game_no = 0;
	while (input >> c) {
		chess_num++;
		if (chess_num < 81)
			continue;
		chess_num = 0;
		game_no++;
	}
	input.close();
	std::cout << "文件中共有" << game_no << "个数独游戏" << std::endl;
	int game_nums = game_no;
	int step = game_nums / 10;

	input.open(source_path);
	chess_num = 0;
	game_no = 1;
	int chess_board[9][9] = {};
	std::ofstream output;
	output.open(SOV_TARGET_PATH);

	while (input >> c) {
		chess_board[chess_num / 9][chess_num % 9] = (c == '$') ? 0 : c - '0';
		chess_num++;
		if (chess_num < 81)
			continue;
		if (solve_single_game(chess_board)) {
			print_chess_borad(chess_board, output);
			chess_num = 0;
		}
		else {
			std::cout << "第" << game_no << "个游戏无解" << std::endl;
			// input.close();
			// output.close();
			// exit(0);
		}
		if (game_no % step == 0) {
			std::cout << "已求解" << game_no << "个数独游戏" << "(" << 100.0 * game_no / game_nums << "%)" << std::endl;
		}
		game_no++;
	}
	input.close();
	output.close();
	std::cout << "数独求解完毕" << std::endl;
}

void Sudoku::gen_over(int game_nums) {
	int step =  game_nums / 10;
	std::cout << "开始生成" << game_nums << "个数独终局" << std::endl;

	int chess_board[9][9];
	std::ofstream output;
	output.open(GEN_OVER_TARGET_PATH);
	for (int i = 0; i < game_nums; i++) {
		gen_single_over(chess_board);
		print_chess_borad(chess_board, output);
		if ((i + 1) % step == 0) {
			std::cout << "已生成" << i + 1 << "个数独终局" << "(" << 100.0 * (i + 1) / game_nums << "%)" << std::endl;
		}
	}
	output.close();

	std::cout << "终局生成完毕" << std::endl;
}

void printcb(int chess_board[9][9]) {
	for (int ci = 0; ci < 9; ci++) {
		for (int ri = 0; ri < 9; ri++) {
			std::cout << chess_board[ci][ri] << ' ';
		}
		std::cout << std::endl;
	}
}
void Sudoku::gen_single_game(int chess_board[9][9], int diffculty, int lattice_num, bool only_one_res) {
	srand((unsigned)time(NULL));
	//lattice_num按-r、-m的优先级计算
	if (lattice_num == 0) {
		if (diffculty != 0) lattice_num = (rand() % 15) + diffculty * 15 - 4;
		else lattice_num = (rand() % 36) + 20;
	}
	//printcb(chess_board);
	bool f_chess_board[9][9] = {0};
	for (int i = 0; i < lattice_num; i++) {
RANDCR:
		bool full = true;
		for (int ci = 0; ci < 9; ci++) {
			for (int ri = 0; ri < 9; ri++) {
				full &= f_chess_board[ci][ri];
			}
		}
		if (full) {
			std::cout << "无法生成"<< lattice_num << "个空的唯一的数独" << std::endl;
			break;
		}

		int col, row ;
		do {
			col = rand() % 9;
			row = rand() % 9;
		} while (f_chess_board[row][col]);

		if (only_one_res) {
			int ori = chess_board[row][col];
			bool f = true;
			for (int j = 1; j <= 9; j++) {
				if (j == ori) continue;
				if (is_legal(chess_board, row, col, j)) {
					chess_board[row][col] = j;
					if(solve_single_game(chess_board, false)){
						f_chess_board[row][col] = true;
						f = false;
						break;
					}
				}
			}
			chess_board[row][col] = ori;
			if (!f) {
				goto RANDCR;
			}
		}
		chess_board[row][col] = 0;
		f_chess_board[row][col] = true;
	}
}

void Sudoku::gen_game(int game_nums, int diffculty, int lattice_num, bool only_one_res) {
	int step =  game_nums / 10;
	std::cout << "开始生成" << game_nums << "个数独游戏" << std::endl;

	int chess_board[9][9];
	std::ofstream output;
	output.open(GEN_GAME_TARGET_PATH);
	for (int i = 0; i < game_nums; i++) {
		gen_single_over(chess_board);
		gen_single_game(chess_board, diffculty, lattice_num, only_one_res);
		print_chess_borad(chess_board, output);
		if ((i + 1) % step == 0) {
			std::cout << "已生成" << i + 1 << "个数独游戏" << "(" << 100.0 * (i + 1) / game_nums << "%)" << std::endl;
		}
	}
	output.close();

	std::cout << "数独游戏生成完毕" << std::endl;
}