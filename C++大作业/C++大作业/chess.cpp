#include "chess.h"
#include<easyx.h>
#include<graphics.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

void chess::init()
{
	//������Ϸ����
	initgraph(845,867);
	//��ʾ���ǵ�����ͼƬ
	loadimage(0, "D:/C++��Ŀ/C++����ҵ/C++����ҵ/view.jpg");
	//���ſ�ʼ��ʾ��
	mciSendString("play D:/C++��Ŀ/C++����ҵ/C++����ҵ/�Ծֿ�ʼ.wav", 0, 0, 0);

	//���غ���Ͱ����ͼƬ
	loadimage(&chessblack, "D:/C++��Ŀ/C++����ҵ/C++����ҵ/����.jpg",chesssize,chesssize,true);
	loadimage(&chesswhite, "D:/C++��Ŀ/C++����ҵ/C++����ҵ/����.jpg", chesssize, chesssize, true);
	//��������
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
