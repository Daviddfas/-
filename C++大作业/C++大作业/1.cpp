/*
* 开发日志
* 1.创建项目，导入素材
* 2.设计项目框架
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

	game1.play();

	return 0;
}