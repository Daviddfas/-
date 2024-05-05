#pragma once
//表示落子位置的结构体
struct chessset
{
	int row;
	int col;
};
typedef enum
{
	white_chess = -1,//白棋
	black_chess = 1	//黑棋
}chess_kind;
class chess
{
public:
	void init();//
	bool clickboard(int x, int y, chessset* pos);//判断在指定位置的点击是否为有效点击，如果是有效点击就可以把有效点击的位置保存在参数中
	void chessfall(chessset* p, chess_kind ki);//在棋盘的指定位置（pos),落子（kind)
	//row为行，col为列，val表示黑白
	int getsize();//获取棋盘大小
	//获取指定位置是黑棋还是白棋，还是空白
	int getchessdata(chessset* pos);
	int getchessdata(int row, int col);
	bool checkover();//检查棋局是否结束
};

