#include "Sudoku.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

#define SOV_TARGET_PATH "sudoku.txt"
#define GEN_TARGET_PATH "game.txt"
//#define DEBUG_SUDOKU

void Sudoku::print_chess_borad(int chess_board[9][9], std::ofstream& output) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (chess_board[i][j] != 0)
				output << (char)('0' + chess_board[i][j]);
			else 
				output << '$';
		}
		output << std::endl;
	}
	output << std::endl;
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

bool Sudoku::solve(int chess_board[9][9], std::vector<std::pair<int, int>> &zeros, int pos) {
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
	int (*chess_b)[9] = chess_board;
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
	static int first_row[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	
}

 void Sudoku::solve_game(std::string source_path) {
	int chess_board[9][9] = {};
	std::ifstream input;
	input.open(source_path);
	std::ofstream output;
	output.open(SOV_TARGET_PATH);
	int chess_num = 0;
	int game_no = 1;
	char c;
	while (input >> c) {
		chess_board[chess_num / 9][chess_num % 9] = (c == '$') ? 0 : c - '0';
		chess_num++;
		if (chess_num < 81)
			continue;
		if (solve_single_game(chess_board)) {
			print_chess_borad(chess_board, output);
			chess_num = 0;
			game_no++;
		}
		else {
			std::cout << "第" << game_no << "个游戏无解" << std::endl;
			input.close();
			output.close();
			exit(0);
		}
	}
	input.close();
	output.close();
}

 void Sudoku::gen_over(int game_nums) {
	int chess_board[9][9];
 }

 void Sudoku::gen_game(int game_nums) {
 
 }