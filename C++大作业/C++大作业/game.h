#pragma once
#include "man.h"
#include "AI.h"
#include "chess.h"
class game
{
public:
	game(man* man, AI* ai, chess* chess)
	{
		this->man = man;
		this->ai = ai;
		this->chess = chess;

	}
	void play();//��ʼ�Ծ�
	//������ݳ�Ա
private:
	man* man;
	AI* ai;
	chess* chess;
};

