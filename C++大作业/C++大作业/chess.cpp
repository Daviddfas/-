#include "chess.h"
#include<easyx.h>
#include<graphics.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

void chess::init()
{
	//创建游戏窗口
	initgraph(845,867);
	//显示我们的棋牌图片
	loadimage(0, "D:/C++项目/C++大作业/C++大作业/view.jpg");
	//播放开始提示音
	mciSendString("play D:/C++项目/C++大作业/C++大作业/对局开始.wav", 0, 0, 0);

	//加载黑棋和白棋的图片
	loadimage(&chessblack, "D:/C++项目/C++大作业/C++大作业/黑棋.jpg",chesssize,chesssize,true);
	loadimage(&chesswhite, "D:/C++项目/C++大作业/C++大作业/白棋.jpg", chesssize, chesssize, true);
	//清理棋盘
	for (int i = 0; i < this->gradesize; i++)
	{
		for (int j = 0; j < this->gradesize; j++)
		{
			chessmap[i][j] = 0;
		}
	}
	playerflag = true;
}

bool chess::clickboard(int x, int y, chessset* pos)
{
	return false;
}

void chess::chessfall(chessset* p, chess_kind ki)
{
}

int chess::getsize()
{
	return 0;
}

int chess::getchessdata(chessset* pos)
{
	return 0;
}

int chess::getchessdata(int row, int col)
{
	return 0;
}

bool chess::checkover()
{
	return false;
}
