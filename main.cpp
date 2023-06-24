#include <iostream>
#include <string>
#include <algorithm>
#include "Sudoku.h"

using namespace std;

//#define DEBUG_ARG_PARSER

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
int diffculty = BOT; // 难度
int lattice_num = 0;
bool only_one_res = false;

void parser_arg(int argc, char *argv[]) {
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
			if (i + 1 >= argc || (lattice_num = atoi(argv[i + 1])) < 20 || lattice_num > 55) {
				cout << "-r argument error" << endl;
				exit(0);
			}
			i++;
		}
		else if (!strcmp(argv[i], "-u")) {
			only_one_res = true;
		}
		else {
			cout << "arguments arror" <<endl;
			exit(0);
		}
	}
	if (op_type != GEN_GAME && (only_one_res || diffculty != BOT || lattice_num != 0)) {
		cout << "arguments error" <<endl;
		exit(0);
	}
}

int main(int argc, char *argv[]) {
	parser_arg(argc, argv);

#ifdef DEBUG_ARG_PARSER
	cout << "op_type: " << op_type << endl;
	cout << "game_nums: " << game_nums << endl;
	cout << "game_path: " << game_path << endl;
	cout << "diffculty: " << diffculty << endl;
	cout << "lattice_num: " << lattice_num << endl;
	cout << "only_one_res: " << only_one_res << endl;
#endif

	switch (op_type)
	{
	case GEN_OVER:
		Sudoku::gen_over(game_nums);
		break;
	case GEN_GAME:
		break;
	case SOV_GAME:
		Sudoku::solve_game(game_path);
		break;
	default:
		break;
	}
}