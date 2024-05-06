#include<math.h>
#include "chess.h"
#include<easyx.h>
#include<graphics.h>
#include<mmsystem.h>
#include "tietu.h"
#pragma comment(lib,"winmm.lib")

static void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}
void chess::init()
{
	//������Ϸ����
	initgraph(826,867,EW_SHOWCONSOLE);
	//��ʾ���ǵ�����ͼƬ
	loadimage(0, "D:/C++��Ŀ/C++����ҵ/C++����ҵ/view.jpg");
	//���ſ�ʼ��ʾ��
	mciSendString("play D:/C++��Ŀ/C++����ҵ/C++����ҵ/�Ծֿ�ʼ.wav", 0, 0, 0);

	//���غ���Ͱ����ͼƬ
	loadimage(&chessblack, "D:/C++��Ŀ/C++����ҵ/C++����ҵ/����.png",chesssize,chesssize,true);
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
	int col = (x - margin_x) / chesssize;
	int row = (y - margin_y) / chesssize;
	int lefttoppos_x = margin_x + chesssize * col;
	int lefttoppos_y = margin_y + chesssize * row;
	int offset = chesssize * 0.4;

	int len;
	bool ret = false;

	do 
	{
		//���Ͻǵ��ж�
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
		//���Ͻǵ��ж�
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
		//���½ǵ��ж�
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
		//���½ǵ��ж�
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
	int x = margin_x + chesssize * p->col-0.5*chesssize ;
	int y = margin_y + chesssize * p->row-0.5*chesssize;

	if (ki == white_chess)
	{
		putimagePNG(x, y,&chesswhite);
	}
	else
	{
		putimagePNG(x, y, &chessblack);
	}
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
