#include "man.h"
#include "chess.h"
void man::init(chess* chess)
{
	this->chess1 = chess;
}

void man::go()
{
	MOUSEMSG msg;
	chessset pos;
	
	while (1)
	{
		//获取鼠标点击的信息
		msg = GetMouseMsg();
		//通过chess对象，来调用 判断落子是否有效，以及落子功能
		if (msg.uMsg == WM_LBUTTONDOWN && chess1->clickboard(msg.x, msg.y, &pos))
		{
			break;
		}
	}

	//printf("%d,%d \n", pos.row,pos.col);//检验落棋位置是否正确
	//落子
	chess1->chessfall(&pos, black_chess);
	

}
