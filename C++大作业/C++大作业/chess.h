#pragma once
#include<graphics.h>
#include<vector>
using namespace std;
//��ʾ����λ�õĽṹ��
struct chessset
{
	int row;
	int col;
};
typedef enum
{
	white_chess = -1,//����
	black_chess = 1	//����
}chess_kind;
class chess
{
public:
	chess(int gradesize, int margin_x, int margin_y, float chesssize)
	{
		this->gradesize = gradesize;
		this->margin_x = margin_x;
		this->margin_y = margin_y;
		this->chesssize = chesssize;
		playerflag = black_chess;
		for (int i = 0; i < gradesize; i++)
		{
			vector<int>row;
			for (int j = 0; j < gradesize; j++)
			{
				row.push_back(0);
			}
		}
	}
	
	void init();//��ʼ������
	bool clickboard(int x, int y, chessset* pos);//�ж���ָ��λ�õĵ���Ƿ�Ϊ��Ч������������Ч����Ϳ��԰���Ч�����λ�ñ����ڲ�����
	void chessfall(chessset* p, chess_kind ki);//�����̵�ָ��λ�ã�pos),���ӣ�kind)
	//rowΪ�У�colΪ�У�val��ʾ�ڰ�
	int getsize();//��ȡ���̴�С
	//��ȡָ��λ���Ǻ��廹�ǰ��壬���ǿհ�
	int getchessdata(chessset* pos);
	int getchessdata(int row, int col);
	bool checkover();//�������Ƿ����
private:
	IMAGE chessblack;//������
	IMAGE chesswhite;//������

	int gradesize;//���̵Ĵ�С��13��15��17��19��
	int margin_x;//���̵����߽�
	int margin_y;//���̵��Ҳ�߽�
	float chesssize;//���ӵĴ�С��С����Ĵ�С��
	//���浱ǰ���ӵ���ֲַ����� 0Ϊ�հ� 1Ϊ���� -1Ϊ����
	//chessmap��ʾ���̵ĵ����е����е��������
	vector<vector<int> >chessmap;

	//��ʾ���ڸ�˭����
	bool playerflag;//true �ú�����

};

