#include "game.h"


//�Ծ֣���ʼ��������Ϸ
void game::play()
{
	//�Ƚ������̵ĳ�ʼ��
	chess->init();
	while (1)
	{
		//��������
		man->go();
		if (chess->checkover())
		{
			chess->init();
			continue;
		}
		//����AI��
		ai->go();
		if (chess->checkover())
		{
			chess->init();
			continue;
		}
	}
}
