#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include "Sudoku.h"

using namespace std;

#define DEBUG_ARG_PARSER

enum
{
	NONE,
	GEN_OVER,
	GEN_GAME,
	SOV_GAME
};

enum
{
	BOT, // 未定义难度
	EASY,
	MIDDLE,
	HARD
};

int op_type = NONE; // 操作类型
int game_nums; // 要生成的游戏数或终局数
string game_path; // 求解游戏的源文件
int diffculty = BOT;// 难度
int min_lattice_num = 0;
int max_lattice_num = 0;
int lattice_num = 0;
bool only_one_res = false;

void parser_arg(int argc, char* argv[]) {
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-c")) {
			if (op_type != NONE) {
				cout << "option conflict!" << endl;
				exit(0);
			}
			op_type = GEN_OVER;
			if (i + 1 >= argc || (game_nums = atoi(argv[i + 1])) < 1 || game_nums > 1000000) {
				cout << "-c argument error" << endl;
				exit(0);
			}
			i++; // 跳过i+1的数字
		}
		else if (!strcmp(argv[i], "-s")) { // 这里认为如果-s出现，不能有其他的参数了
			if (op_type != NONE) {
				cout << "option conflict!" << endl;
				exit(0);
			}
			op_type = SOV_GAME;
			if (argc > 3 || i + 1 >= argc) {
				cout << "-s arguments error" << endl;
				exit(0);
			}
			game_path = argv[i + 1];
			i++;
		}
		else if (!strcmp(argv[i], "-n")) {
			if (op_type != NONE) {
				cout << "option conflict!" << endl;
				exit(0);
			}
			op_type = GEN_GAME;
			if (i + 1 >= argc || (game_nums = atoi(argv[i + 1])) < 1 || game_nums > 10000) {
				cout << "-n argument error" << endl;
				exit(0);
			}
			i++;
		}
		else if (!strcmp(argv[i], "-m")) {
			if (i + 1 >= argc || (diffculty = atoi(argv[i + 1])) < 1 || diffculty > 3) {
				cout << "-m argument error" << endl;
				exit(0);
			}
			i++;
		}
		else if (!strcmp(argv[i], "-r")) {
			if (i + 1 < argc) {
				char *token = strtok(argv[i + 1], "~");
				if (token == NULL)
					goto RERROR;
				min_lattice_num = atoi(token);
				token = strtok(NULL, "~");
				if (token == NULL)
					goto RERROR;
				max_lattice_num = atoi(token);
				if (min_lattice_num < 20 || min_lattice_num > 55 || max_lattice_num < 20 || max_lattice_num > 55 || min_lattice_num > max_lattice_num) {
					goto RERROR;
				}
			}
			else {
				RERROR:
				cout << "-r argument error" << endl;
				exit(0);
			}
			i++;
		}
		else if (!strcmp(argv[i], "-u")) {
			only_one_res = true;
		}
		else {
			cout << "arguments arror" << endl;
			exit(0);
		}
	}
	if (op_type != GEN_GAME && (only_one_res || diffculty != BOT || lattice_num != 0)) {
		cout << "arguments error" << endl;
		exit(0);
	}
}

int main(int argc, char* argv[]) {
	parser_arg(argc, argv);

#ifdef DEBUG_ARG_PARSER
	cout << "op_type: " << op_type << endl;
	cout << "game_nums: " << game_nums << endl;
	cout << "game_path: " << game_path << endl;
	cout << "diffculty: " << diffculty << endl;
	cout << "only_one_res: " << only_one_res << endl;
	cout << "min_lattice_num: " << min_lattice_num << endl;
	cout << "max_lattice_num: " << max_lattice_num << endl;
#endif

	auto t_start = chrono::high_resolution_clock::now();
	switch (op_type)
	{
	case GEN_OVER:
		Sudoku::gen_over(game_nums);
		break;
	case GEN_GAME:
		Sudoku::gen_game(game_nums, diffculty, lattice_num, only_one_res);
		break;
	case SOV_GAME:
		Sudoku::solve_game(game_path);
		break;
	default:
		break;
	}
	auto t_end = chrono::high_resolution_clock::now();
	cout << "用时";
	cout << chrono::duration_cast<chrono::microseconds>(t_end - t_start).count() / 1000000.0;
	cout << "s";
	return 0;
}