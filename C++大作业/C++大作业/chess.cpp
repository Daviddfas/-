#include<math.h>
#include "chess.h"
#include<easyx.h>
#include<graphics.h>
#include<mmsystem.h>
#include "tietu.h"
#pragma comment(lib,"winmm.lib")
#include<conio.h>

//static void putimagePNG(int x, int y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
//{
//	// 变量初始化
//	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
//	DWORD* draw = GetImageBuffer();
//	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
//	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
//	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
//	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
//	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
//	int dstX = 0;    //在显存里像素的角标
//
//	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
//	for (int iy = 0; iy < picture_height; iy++)
//	{
//		for (int ix = 0; ix < picture_width; ix++)
//		{
//			int srcX = ix + iy * picture_width; //在显存里像素的角标
//			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
//			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
//			int sg = ((src[srcX] & 0xff00) >> 8);   //G
//			int sb = src[srcX] & 0xff;              //B
//			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
//			{
//				dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
//				int dr = ((dst[dstX] & 0xff0000) >> 16);
//				int dg = ((dst[dstX] & 0xff00) >> 8);
//				int db = dst[dstX] & 0xff;
//				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
//					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
//					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
//			}
//		}
//	}
//}
void chess::init()
{
	//创建游戏窗口
	initgraph(826,867,EW_SHOWCONSOLE);
	//显示我们的棋牌图片
	loadimage(0, "D:/C++项目/C++大作业/C++大作业/view.jpg");
	//播放开始提示音
	mciSendString("play D:/C++项目/C++大作业/C++大作业/对局开始.wav", 0, 0, 0);

	//加载黑棋和白棋的图片
	loadimage(&blackyanma, "D:/C++项目/C++大作业/C++大作业/黑棋2.png", chesssize, chesssize, true);
	loadimage(&chessblack, "D:/C++项目/C++大作业/C++大作业/黑棋.png",chesssize,chesssize,true);
	loadimage(&whiteyanma, "D:/C++项目/C++大作业/C++大作业/白棋2.png", chesssize, chesssize, true);
	loadimage(&chesswhite, "D:/C++项目/C++大作业/C++大作业/白棋.png", chesssize, chesssize, true);
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
	int col = (x - margin_x) / chesssize;
	int row = (y - margin_y) / chesssize;
	int lefttoppos_x = margin_x + chesssize * col;
	int lefttoppos_y = margin_y + chesssize * row;
	int offset = chesssize * 0.4;

	int len;
	bool ret = false;

	do 
	{
		//左上角的判断
		len = sqrt(pow(x - lefttoppos_x, 2) + pow(y - lefttoppos_y, 2));
		if (len < offset)
		{
			pos->row = row;
			pos->col = col;
			if (chessmap[pos->row][pos->col] == 0)
			{
				ret = true;
			}
			break;
		}
		//右上角的判断
		int x2 = lefttoppos_x + chesssize;
		int y2 = lefttoppos_y;
		len = sqrt(pow(x - x2, 2) + pow(y - y2, 2));
		if (len < offset)
		{
			pos->row = row;
			pos->col = col+1;
			if (chessmap[pos->row][pos->col] == 0)
			{
				ret = true;
			}
			break;
		}
		//左下角的判断
		int x3 = lefttoppos_x;
		int y3 = lefttoppos_y + chesssize;
		len = sqrt(pow(x - x3, 2) + pow(y - y3, 2));
		if (len < offset)
		{
			pos->row = row+1;
			pos->col = col;
			if (chessmap[pos->row][pos->col] == 0)
			{
				ret = true;
			}
			break;
		}
		//右下角的判断
		int x4 = lefttoppos_x + chesssize;
		int y4 = lefttoppos_y + chesssize;

		len = sqrt(pow(x - x4, 2) + pow(y - y4, 2));
		if (len < offset)
		{
			pos->row = row+1;
			pos->col = col+1;
			if (chessmap[pos->row][pos->col] == 0)
			{
				ret = true;
			}
			break;
		}


	} while (0);
	
	return ret;
}

void chess::chessfall(chessset* p, chess_kind ki)
{
	mciSendString("play D:/C++项目/C++大作业/C++大作业/落棋声音.mp3",0, 0, 0);
	int x = margin_x + chesssize * p->col-0.5*chesssize ;
	int y = margin_y + chesssize * p->row-0.5*chesssize;

	if (ki == white_chess)
	{
		putimage(x,y,&whiteyanma, SRCAND);
		putimage(x, y,&chesswhite,SRCPAINT);
	}
	else
	{
		putimage(x, y, &blackyanma, SRCAND);
		putimage(x, y, &chessblack,SRCPAINT );

	}
	updatechessmap(p);
}

int chess::getsize()
{

	return gradesize;
}

int chess::getchessdata(chessset* pos)
{
	return chessmap[pos->row][pos->col];
}

int chess::getchessdata(int row, int col)
{
	return chessmap[row][col];
}

bool chess::checkover()
{
	if (checkWin())
	{
		Sleep(1500);
		if (playerflag == false)
		{
			//刚才走棋的是黑方（棋手方），棋手胜利
			mciSendString("play D:/C++项目/C++大作业/C++大作业/战斗胜利.wav", 0, 0, 0);
			loadimage(0, "D:D:/C++项目/C++大作业/C++大作业/胜利2.png");
			loadimage(0, "D:/C++项目/C++大作业/C++大作业/胜利1.png");
		}
		else
		{
			mciSendString("play D:/C++项目/C++大作业/C++大作业/战斗失败.wav", 0, 0, 0);
			loadimage(0, "D:/C++项目/C++大作业/C++大作业/失败3.png");
			loadimage(0, "D:/C++项目/C++大作业/C++大作业/失败2.png");

		}
		
		_getch();//暂停
		return true;
	}
	return false;
}

void chess::updatechessmap(chessset* pos)
{
	lastPos = *pos;
	chessmap[pos->row][pos->col] = playerflag ? black_chess : white_chess;
	playerflag = !playerflag;//黑白方交换
}

bool chess::checkWin()
{
	//最近落子点的位置
	int row = lastPos.row;
	int col = lastPos.col;

	//落子点的水平方向
	for (int i = 0; i < 5; i++)
	{
		//对于第i次
		//五子连读的最左侧位置
		//i=0:(row,col),(row,col+1),(row,col+2),(row,col+3),(row,col+4)
		//i=1:(row,col-1),(row,col-1+1),(row,col-1+2).(row,col-1+3),(row,col-1+4）
		if (col-i>=0&&col-i+4<gradesize&&
			chessmap[row][col - i] == chessmap[row][col - i + 1] &&
			chessmap[row][col - i] == chessmap[row][col - i + 2] &&
			chessmap[row][col - i] == chessmap[row][col - i + 3] &&
			chessmap[row][col - i] == chessmap[row][col - i + 4])
		{
			return true;
		}

	}
	//垂直方向
	for (int i = 0; i < 5; i++)
	{
		if (row - i > 0 && row - i + 4 < gradesize &&
			chessmap[row - i][col] == chessmap[row - i + 1][col] &&
			chessmap[row - i][col] == chessmap[row - i + 2][col] &&
			chessmap[row - i][col] == chessmap[row - i + 3][col] &&
			chessmap[row - i][col] == chessmap[row - i + 4][col])
		{
			return true;
		}
	}
	//"/"方向
	for (int i = 0; i < 5; i++)
	{
		if (row + i < gradesize && row + i - 4 >= 0 &&
			col - i >= 0 && col - i + 4 < gradesize &&
			chessmap[row + i][col - i] == chessmap[row + i - 1][col - i + 1] &&
			chessmap[row + i][col - i] == chessmap[row + i - 2][col - i + 2] &&
			chessmap[row + i][col - i] == chessmap[row + i - 3][col - i + 3] &&
			chessmap[row + i][col - i] == chessmap[row + i - 4][col - i + 4])
		{
			return true;
		}
	}

	//"\"方向
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 && row - i + 4 < gradesize &&
			col - i >= 0 && col - i + 4 < gradesize &&
			chessmap[row - i][col - i] == chessmap[row - i + 1][col - i + 1] &&
			chessmap[row - i][col - i] == chessmap[row - i + 2][col - i + 2] &&
			chessmap[row - i][col - i] == chessmap[row - i + 3][col - i + 3] &&
			chessmap[row - i][col - i] == chessmap[row - i + 4][col - i + 4])
		{
			return true;
		}
	}
	return false;
}
