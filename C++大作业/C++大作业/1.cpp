/*
* ������־
* 1.������Ŀ�������ز�
* 2.�����Ŀ���
* 
*/
#include<iostream>
#include "game.h"
using namespace std;

int main()
{
	man man1;
	chess chess1(15, 24, 16, 57.1);
	AI ai1;
	game game1(&man1, &ai1, &chess1);
	initgraph(597,706, EW_SHOWCONSOLE);
	IMAGE img11;
	loadimage(&img11, "D:/C++��Ŀ/C++����ҵ/C++����ҵ/��ʼ1.png",597,706,true);
	putimage(0, 0, &img11);
	

	//���Ʊ���
	settextcolor(RGB(255, 255, 255));
	settextstyle(50, 0, _T("����"));
	outtextxy(100, 590, _T("��Ϸ��ʼ�˵�"));

	//���ư�ť
	setfillcolor(RGB(0, 162, 232));
	setlinecolor(RGB(0, 162, 232));
	fillrectangle(100, 590, 500, 680);
	settextstyle(30, 0, _T("����"));
	settextcolor(RGB(255, 255, 255));
	outtextxy(240,610, _T("��ʼ��Ϸ"));
	while (true)
	{
		//��ȡ���״̬
		MOUSEMSG mousemsg = GetMouseMsg();
		if (mousemsg.uMsg == WM_LBUTTONDOWN)
		{
			if (mousemsg.x >= 100 && mousemsg.x <= 500 && mousemsg.y >= 590 && mousemsg.y <= 680)
			{
				break;
			}
		}
	}
	closegraph();
	game1.play();

	return 0;
}