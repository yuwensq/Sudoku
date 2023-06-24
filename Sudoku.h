#ifndef _SUDOKU_H_
#define _SUDOKU_H_
#include <string>
#include <vector>

class Sudoku{
private:
	Sudoku(){}; // 这里把Sudoku写成个工具类吧
	// 判断在棋盘的(i, j)处放一个k是否合法
	static bool is_legal(int chess_board[9][9], int i, int j, int k);
	// 递归求解，zeros是存储棋盘初始时所有空格子的坐标
	static bool solve(int chess_board[9][9], std::vector<std::pair<int, int>> &zeros, int pos);
	// 对solve函数进行封装，change_chess表示是否允许改变棋盘内容，为true表示允许，
	// 则最终chess_board的内容将会是求解好后的内容；为true表示不允许，则最终chess_board
	// 的内容将会是调用solve_single_game函数前的内容
	static bool solve_single_game(int chess_board[9][9], bool change_chess=true);
	// 生成一个棋盘终局，每次调用返回不同的终局
	static void gen_single_over(int chess_board[9][9]);
	// 将棋盘打印至文件，这里要先定义一个ofstream
	static void print_chess_borad(int chess_borad[9][9], std::ofstream &output);
public:
	static void solve_game(std::string source_path); // 解游戏
	static void gen_over(int game_nums); // 生成终局
	static void gen_game(int game_nums); // 生成游戏，这里还差几个参数
};

#endif