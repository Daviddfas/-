#include "AI.h"

void AI::init(chess* chess)
{
	this->chess2 = chess;
	int size = chess2->getsize();
	for (int i = 0; i < size; i++)
	{
		vector<int>row;
		for (int j = 0; j < size; j++)
		{
			row.push_back(0);
		}

		scoremap.push_back(row);
	}
}

void AI::go()
{
	chessset pos=think();
	Sleep(1000);//假装思考
	chess2->chessfall(&pos, white_chess);
}

void AI::calculategrade()
{
	int personNum = 0;//棋手（黑棋）连续有多少个棋子
	int aiNum = 0;//AI方有多少个连续的棋子
	int emptyNum = 0;//该方向上空白位的个数

	//评分向量数组清零
	for (int i = 0; i < scoremap.size(); i++)
	{
		for (int j = 0; j < scoremap[i].size(); j++)
		{
			scoremap[i][j] = 0;
		}
	}
	int size = chess2->getsize();
	//不确定此处究竟是chess还是chess1还是chess2

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			/*personNum = 0;
			aiNum = 0;
			emptyNum = 0;*/

			//对每个点进行计算

			if (chess2->getchessdata(row, col))
			{
				continue;
			}
			for (int y = -1; y <= 0; y++)
			{
				for (int x = -1; x <= 1; x++)
				{
					if (y == 0 && x == 0)
					{
						continue;
					}
					if (y == 0 && x != 1)
					{
						continue;
					}

					personNum = 0;
					aiNum = 0;
					emptyNum = 0;



					//假设黑棋在该位置落子，会构成什么棋型

					for (int i = 1; i <= 4; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess2->getchessdata(curRow, curCol) == 1)
						{
							personNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess2->getchessdata(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}

					/*反向计算*/

					for (int i = 1; i <= 4; i++)
					{
						int curRow = row - i * y;
						int curCol = col -i * x;
						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess2->getchessdata(curRow, curCol) == 1)
						{
							personNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess2->getchessdata(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}

					if (personNum == 1)
					{
						/*连2*/
						scoremap[row][col] += 10;
					}
					else if (personNum == 2)
					{
						if (emptyNum == 1)
						{
							scoremap[row][col] += 30;
						}
						else if (emptyNum == 2)
						{
							scoremap[row][col] += 40;
						}
					
					}
					else if (personNum == 3)
					{
						if (emptyNum == 1)
						{
							scoremap[row][col] += 60;/*=还是+=*/
						}
						else if (emptyNum == 2)
						{
							scoremap[row][col] += 200;/*=还是+=*/
						}
					}
					else if (personNum == 4)
					{
						scoremap[row][col] += 20000;
					}

					//假设白棋在该位置落子，会构成什么棋型
					emptyNum = 0;

					for (int i = 1; i <= 4; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess2->getchessdata(curRow, curCol) == -1)
						{
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess2->getchessdata(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}

					/*反向计算*/
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess2->getchessdata(curRow, curCol) == -1)
						{
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess2->getchessdata(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}

					if (aiNum == 0)
					{
						scoremap[row][col] += 5;
					}
					else if (aiNum == 10)
					{
						scoremap[row][col] += 10;
					}
					else if (aiNum == 2)
					{
						if (emptyNum == 1)
						{
							scoremap[row][col] += 25;
						}
						else if (emptyNum == 2)
						{
							scoremap[row][col] += 50;
						}
					}
					else if (aiNum == 3)
					{
						if (emptyNum == 1)
						{
							scoremap[row][col] += 55;
						}
						else if (emptyNum == 2)
						{
							scoremap[row][col] += 10000;
						}
					}
					else if (aiNum == 4)
					{
						scoremap[row][col] += 30000;
					}
				}
			}

			
		}
	}
}

chessset AI::think()
{
	calculategrade();

	vector<chessset> maxPoints;
	int maxScore = 0;
	int size = chess2->getsize();
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (chess2->getchessdata(row, col) == 0)
			{
				if (scoremap[row][col] > maxScore)
				{
					maxScore = scoremap[row][col];
					maxPoints.clear();
					maxPoints.push_back(chessset(row, col));

				}
				else if (scoremap[row][col] == maxScore)
				{
					
					maxPoints.push_back(chessset(row, col));
				}
			}
		}
	}

	int index = rand() % maxPoints.size();
	return maxPoints[index];
}
