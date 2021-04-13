// ���糡.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "main.h"

#ifdef D1

#include "graphics.h"
#include "math.h"
#define PI 3.1415926535
#define W 800			//�궨����Ļ��
#define L 800			//�궨����Ļ��
#define LINE 20			//���û�������
#define NUM 30000		//��������

int main()
{
	double r1, r2, Ex, Ey, x, y, x0, y0, X = 0.0, E;		//���ñ���
	initgraph(W, L);								//��ʼ����Ļ
	setbkcolor(WHITE);							//���ñ���ɫ
	cleardevice();								//�����Ļ����
	setorigin(400, 400);							//��������ԭ��λ��
	setlinecolor(BLACK);						//�����ߵ���ɫΪ��ɫ

	setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 2);		//������Ϊ���ߣ��˵�Ϊƽ̹��
	line(0, -400, 0, 400);							//y��
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 2);	//������Ϊʵ�ߣ��˵�Ϊƽ̹��
	line(-400, 0, 400, 0);							//x��

	circle(-200, 0, 15);							//���뾶Ϊ15��Բ�������Բ���������
	setfillcolor(RED);							//���������ɫΪ��ɫ
	fillcircle(-200, 0, 15);						//��������

	circle(200, 0, 15);							//���뾶Ϊ15��Բ�������Բ���������
	setfillcolor(BLUE);							//���������ɫΪ��ɫ
	fillcircle(200, 0, 15);						//��为���

	line(-208, 0, -192, 0);
	line(-200, -8, -200, 8);						//������
	line(192, 0, 208, 0);							//������

	for (int i = 0; i < LINE; i++)						//����Ҫ���ߵ�ѭ������
	{
		x = -200 + 15 * cos(X);						//���úó������ߵ�ĳ���λ��
		y = 0 + 15 * sin(X);							//�԰뾶Ϊ15��Բ��ȦΪ������
		for (int j = 0; j < NUM; j++)					//��������
		{
			r1 = sqrt(pow(x - 200, 2) + pow(y - 0, 2));   //���㸺(��???)��ɵ�p��λ�õİ뾶	
			r2 = sqrt(pow(x + 200, 2) + pow(y - 0, 2));   //������(��???)��ɵ�p��λ�õİ뾶
			Ex = (200 - x) / pow(r1, 3) + (x + 200) / pow(r2, 3);//����x�᷽��ĳ�ǿ
			Ey = (0 - y) / pow(r1, 3) + (y - 0) / pow(r2, 3);	//����y�᷽��ĳ�ǿ
			E = sqrt(pow(Ex, 2) + pow(Ey, 2));		//�����ܳ�ǿ
			x0 = x + Ex / E;							//�������֮��p���λ��
			y0 = y + Ey / E;							//�������֮��p���λ��
			line(x, y, x0, y0);					//��������
			x = x0;								//����x����
			y = y0;								//����y����
			if (pow(x - 200, 2) + pow(y - 0, 2) <= 15 * 15)//��ֹ�����ߵ�ס�һ��ĸ����
				break;
		}
		X += 2 * PI / LINE;//�ı仭�ߵ��λ��
	}
	system("pause");
}

#endif