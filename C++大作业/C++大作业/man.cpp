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
		//��ȡ���������Ϣ
		msg = GetMouseMsg();
		//ͨ��chess���������� �ж������Ƿ���Ч���Լ����ӹ���
		if (msg.uMsg == WM_LBUTTONDOWN && chess1->clickboard(msg.x, msg.y, &pos))
		{
			break;
		}
	}

	//printf("%d,%d \n", pos.row,pos.col);//��������λ���Ƿ���ȷ
	//����
	chess1->chessfall(&pos, black_chess);
	

}
