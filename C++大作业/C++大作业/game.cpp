#include "game.h"


//对局，开始五子棋游戏
void game::play()
{
	//先进行棋盘的初始化
	chess->init();
	while (1)
	{
		//先由人走
		man->go();
		if (chess->checkover())
		{
			chess->init();
			continue;
		}
		//再由AI走
		ai->go();
		if (chess->checkover())
		{
			chess->init();
			continue;
		}
	}
}
