#pragma once
#include<graphics.h>
#include<vector>
using namespace std;
//表示落子位置的结构体
struct chessset
{
	int row;
	int col;

	chessset(int r = 0, int c = 0) :row(r), col(c)
	{
	};
};
typedef enum
{
	white_chess = -1,//白棋
	black_chess = 1	//黑棋
}chess_kind;
class chess
{
public:
	chess(int gradesize, int margin_x, int margin_y, float chesssize)
	{
		this->gradesize = gradesize;
		this->margin_x = margin_x;
		this->margin_y = margin_y;
		this->chesssize = chesssize;
		playerflag = black_chess;
		for (int i = 0; i < gradesize; i++)
		{
			vector<int>row;
			for (int j = 0; j < gradesize; j++)
			{
				row.push_back(0);
			}
			chessmap.push_back(row);
		}
	}
	
	void init();//初始化棋盘
	bool clickboard(int x, int y, chessset* pos);//判断在指定位置的点击是否为有效点击，如果是有效点击就可以把有效点击的位置保存在参数中
	void chessfall(chessset* p, chess_kind ki);//在棋盘的指定位置（pos),落子（kind)
	//row为行，col为列，val表示黑白
	int getsize();//获取棋盘大小
	//获取指定位置是黑棋还是白棋，还是空白
	int getchessdata(chessset* pos);
	int getchessdata(int row, int col);
	bool checkover();//检查棋局是否结束
private:
	IMAGE chessblack;//黑棋子
	IMAGE blackyanma;//黑棋的掩码
	IMAGE chesswhite;//白棋子
	IMAGE whiteyanma;//白棋的掩码

	int gradesize;//棋盘的大小（13，15，17，19）
	int margin_x;//棋盘的左侧边界
	int margin_y;//棋盘的右侧边界
	float chesssize;//棋子的大小（小方格的大小）
	//储存当前棋子的棋局分布数据 0为空白 1为黑子 -1为白子
	//chessmap表示棋盘的第三行第五列的落子情况
	vector<vector<int> >chessmap;

	//表示现在该谁下棋
	bool playerflag;//true 该黑子走


	void updatechessmap(chessset* pos);

	bool checkWin();//如果胜负已分，就返回true，否则返回假

	chessset lastPos;//最近的落子点的位置
};

