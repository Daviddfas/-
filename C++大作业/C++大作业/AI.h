#pragma once
#include"chess.h"
class AI
{
public:
	void init(chess* chess);//
	void go();

private:
	chess* chess2;
	vector<vector<int>> scoremap;

private:
	void calculategrade();
	chessset think();
};

