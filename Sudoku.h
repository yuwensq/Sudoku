#ifndef _SUDOKU_H_
#define _SUDOKU_H_
#include <string>
#include <vector>

class Sudoku{
private:
	Sudoku(){}; // �����Sudokuд�ɸ��������
	// �ж������̵�(i, j)����һ��k�Ƿ�Ϸ�
	static bool is_legal(int chess_board[9][9], int i, int j, int k);
	// �ݹ���⣬zeros�Ǵ洢���̳�ʼʱ���пո��ӵ�����
	static bool solve(int chess_board[9][9], std::vector<std::pair<int, int>> &zeros, int pos);
	// ��solve�������з�װ��change_chess��ʾ�Ƿ�����ı��������ݣ�Ϊtrue��ʾ����
	// ������chess_board�����ݽ��������ú�����ݣ�Ϊtrue��ʾ������������chess_board
	// �����ݽ����ǵ���solve_single_game����ǰ������
	static bool solve_single_game(int chess_board[9][9], bool change_chess=true);
	// ����һ�������վ֣�ÿ�ε��÷��ز�ͬ���վ�
	static void gen_single_over(int chess_board[9][9]);
	// �����̴�ӡ���ļ�������Ҫ�ȶ���һ��ofstream
	static void print_chess_borad(int chess_borad[9][9], std::ofstream &output);
public:
	static void solve_game(std::string source_path); // ����Ϸ
	static void gen_over(int game_nums); // �����վ�
	static void gen_game(int game_nums); // ������Ϸ�����ﻹ�������
};

#endif