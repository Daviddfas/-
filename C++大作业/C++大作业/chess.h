#pragma once
//表示落子位置的结构体
struct chessset
{
	int row;
	int col;
};
enum
{
	white_chess = -1,//白棋
	black_chess = 1	//黑棋
};
class chess
{
	void chessfall(chessset* p, int val)
	{};//row为行，col为列，val表示黑白
};

