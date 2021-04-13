// ���糡.cpp : �������̨Ӧ�ó������ڵ㡣
//

//#include "main.h"

#ifdef D2

#include "graphics.h"
#include "math.h"
#define PI 3.1415926535
#define W 800			//�궨����Ļ��
#define L 800			//�궨����Ļ��
#define LINE 20			//���û�������
#define NUM 3000		//��������


struct Poly
{
	float x = 0;
	float y = 0;
};

int main()
{
	Poly p1;//����1
	Poly n1;//����1
	Poly p2;//����2
	Poly n2;//����2
	p1.x = -200;
	p1.y = 0;
	n1.x = 200;
	n1.y = 0;

	p2.x = 0;
	p2.y = 200;
	n2.x = 0;
	n2.y = -200;




	double  X = 0.0;		//���ñ���
	double x1, y1, Etx, Ety, Et , xt0, yt0,rt1,rt2;
	double x2, y2, Evx, Evy, Ev , xv0, yv0, rv1, rv2;
	double x3, y3;

	initgraph(W, L);								//��ʼ����Ļ
	setbkcolor(WHITE);							//���ñ���ɫ
	cleardevice();								//�����Ļ����
	setorigin(400, 400);							//��������ԭ��λ��
	setlinecolor(BLACK);						//�����ߵ���ɫΪ��ɫ

	setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 2);		//������Ϊ���ߣ��˵�Ϊƽ̹��
	line(0, -400, 0, 400);							//y��
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 2);	//������Ϊʵ�ߣ��˵�Ϊƽ̹��
	line(-400, 0, 400, 0);							//x��

	circle(p1.x, p1.y, 15);							//���뾶Ϊ15��Բ�������Բ���������
	setfillcolor(RED);							//���������ɫΪ��ɫ
	fillcircle(p1.x, p1.y, 15);						//��������

	circle(n1.x, n1.y, 15);							//���뾶Ϊ15��Բ�������Բ���������
	setfillcolor(BLUE);							//���������ɫΪ��ɫ
	fillcircle(n1.x, n1.y, 15);						//��为���

	//���ڶ��Ե��
	circle(p2.x, p2.y, 15);							//���뾶Ϊ15��Բ�������Բ���������
	setfillcolor(RED);							//���������ɫΪ��ɫ
	fillcircle(p2.x, p2.y, 15);						//��������

	circle(n2.x, n2.y, 15);							//���뾶Ϊ15��Բ�������Բ���������
	setfillcolor(BLUE);							//���������ɫΪ��ɫ
	fillcircle(n2.x, n2.y, 15);						//��为���

	line(p2.x - 8, 0, p2.x + 8, 0);
	line(p2.x, -8, p2.x, 8);						//������
	line(n2.x - 8, 0, n2.x + 8, 0);							//������

	for (int i = 0; i < LINE; i++)						//����Ҫ���ߵ�ѭ������
	{
		x1 = p1.x + 15 * cos(X);						//���úó������ߵ�ĳ���λ��
		y1 = p1.y + 15 * sin(X);							//�԰뾶Ϊ15��Բ��ȦΪ������
		x2 = p2.x + 15 * cos(X);						//���úó������ߵ�ĳ���λ��
		y2 = p2.y + 15 * sin(X);

		x3 = p1.x + 15 * cos(X);						//���úó������ߵ�ĳ���λ��
		y3 = p1.y + 15 * sin(X);							//�԰뾶Ϊ15��Բ��ȦΪ������

		for (int j = 0; j < NUM; j++)					//��������
		{
			{
				rt1 = sqrt(pow(x1 - p1.x, 2) + pow(y1 - p1.y, 2));   //���㸺(��???)��ɵ�p��λ�õİ뾶	
				rt2 = sqrt(pow(x1 - n1.x, 2) + pow(y1 - n1.y, 2));   //������(��???)��ɵ�p��λ�õİ뾶

				//�������-x���������x-
				//һ��һ��
				Etx = (n1.x - x1) / pow(rt2, 3) + (x1 - p1.x) / pow(rt1, 3);//����x�᷽��ĳ�ǿ
				Ety = (n1.y - y1) / pow(rt2, 3) + (y1 - p1.y) / pow(rt1, 3);	//����y�᷽��ĳ�ǿ
				//������ͬ���
				//Etx = (x1-n1.x) / pow(rt2, 3) + (x1 - p1.x) / pow(rt1, 3);//����x�᷽��ĳ�ǿ
				//Ety = (y1 - n1.y) / pow(rt2, 3) + (y1 - p1.y) / pow(rt1, 3);	//����y�᷽��ĳ�ǿ


				Et = sqrt(pow(Etx, 2) + pow(Ety, 2));		//������������ܳ�ǿ
				xt0 = x1 + 10 * Etx / Et;							//�������֮��p���λ��
				yt0 = y1 + 10 * Ety / Et;							//�������֮��p���λ��
				line(x1, y1, xt0, yt0);					//��������
				x1 = xt0;								//����x����
				y1 = yt0;								//����y����
				if (pow(x1 - n1.x, 2) + pow(y1 - n1.y, 2) <= 15 * 15)//��ֹ�����ߵ�ס�һ��ĸ����
					break;

			}
			{
				////�ڶ��Ե��
				//rv1 = sqrt(pow(x2 - p2.x, 2) + pow(y2 - p2.y, 2));   //���㸺(��???)��ɵ�p��λ�õİ뾶	
				//rv2 = sqrt(pow(x2 - n2.x, 2) + pow(y2 - n2.y, 2));   //������(��???)��ɵ�p��λ�õİ뾶

				////�������A-B���������B-A
				////һ��һ��
				////Evx = (n2.x - x2) / pow(rv2, 3) + (x2 - p2.x) / pow(rv1, 3);//����x�᷽��ĳ�ǿ
				////Evy = (n2.y - y2) / pow(rv2, 3) + (y2 - p2.y) / pow(rv1, 3);	//����y�᷽��ĳ�ǿ

				//{
				//	Evx = (n2.x - x2) / pow(rv2, 3) + (x2 - p2.x) / pow(rv1, 3);//����x�᷽��ĳ�ǿ
				//	Evy = (n2.y - y2) / pow(rv2, 3) + (y2 - p2.y) / pow(rv1, 3);	//����y�᷽��ĳ�ǿ
				//	Evx += Etx;
				//	Evy += Ety;
				//}



				//Ev = sqrt(pow(Evx, 2) + pow(Evy, 2));		//�����ܳ�ǿ

				//xv0 = x3 + 10 * Evx / Ev;							//�������֮��p���λ��
				//yv0 = y3 + 10 * Evy / Ev;							//�������֮��p���λ��
				//line(x3, y3, xv0, yv0);					//��������
				//x3 = xv0;								//����x����
				//y3 = yv0;								//����y����
				////xv0 = x2 + 10 * Evx / Ev;							//�������֮��p���λ��
				////yv0 = y2 + 10 * Evy / Ev;							//�������֮��p���λ��
				////line(x2, y2, xv0, yv0);					//��������
				////x2 = xv0;								//����x����
				////y2 = yv0;								//����y����
				////if (pow(x2 - n2.x, 2) + pow(y2 - n2.y, 2) <= 15 * 15)//��ֹ�����ߵ�ס�һ��ĸ����
				////	break;
			}

		}
		X += 2 * PI / LINE;//�ı仭�ߵ��λ��
	}
	system("pause");
}

#endif