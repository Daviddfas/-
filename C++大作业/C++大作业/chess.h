#pragma once
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
	void init();//
	bool clickboard(int x, int y, chessset* pos);//�ж���ָ��λ�õĵ���Ƿ�Ϊ��Ч������������Ч����Ϳ��԰���Ч�����λ�ñ����ڲ�����
	void chessfall(chessset* p, chess_kind ki);//�����̵�ָ��λ�ã�pos),���ӣ�kind)
	//rowΪ�У�colΪ�У�val��ʾ�ڰ�
	int getsize();//��ȡ���̴�С
	//��ȡָ��λ���Ǻ��廹�ǰ��壬���ǿհ�
	int getchessdata(chessset* pos);
	int getchessdata(int row, int col);
	bool checkover();//�������Ƿ����
};

