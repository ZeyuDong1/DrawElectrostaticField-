// ���糡.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "main.h"

#ifdef D2

#include "graphics.h"
#include "math.h"
#include <iostream>
#include <iomanip>
#include <vector> 
#include <sstream>
#include <fstream>
using namespace std;
#define PI 3.1415926535
#define W 800			//�궨����Ļ��
#define L 800			//�궨����Ļ��
#define LINE 20			//���û�������
#define NUM 3000		//��������

//
struct Poly
{
	float x = 0;
	float y = 0;
	bool isZheng;
};

Poly  getOtherPoint(Poly pp, double Barlong, double angle)
{
	Poly e;
	e.x = pp.x + (Barlong * cos(angle / 180 * PI));
	e.y = pp.y + (Barlong * sin(angle / 180 * PI));
	return e;
}
//��ȡ��������֮��ĽǶ�
double getTwoPositiveAngle(Poly p1, Poly p2)
{
	double angle = atan2(p2.y - p1.y, p2.x - p1.x);
	return angle;
}

double getAngle(double x, double y)
{
	double angle = atan2(y,x);
	return angle * (180 / PI);
}


double round(double number, unsigned int bits) {
	stringstream ss;
	ss << fixed << setprecision(bits) << number;
	ss >> number;
	return number;
}


//��ȡĳһ��ĳ�ǿ���ڸ�λ�û���ͼ��
double testPointNum(double x,double y,Poly p1, Poly p2,Poly n1,Poly n2)
{
	Poly testPoint;
	testPoint.x = x;
	testPoint.y = y;

	double rt1, rt2, rt3, rt4,Etx,Ety,Et;

	circle(testPoint.x, testPoint.y, 5);
	setfillcolor(RED);
	fillcircle(testPoint.x, testPoint.y, 5);

	rt1 = sqrt(pow(testPoint.x - p1.x, 2) + pow(testPoint.y - p1.y, 2));   //���㸺(��???)��ɵ�p��λ�õİ뾶	
	rt2 = sqrt(pow(testPoint.x - n1.x, 2) + pow(testPoint.y - n1.y, 2));   //������(��???)��ɵ�p��λ�õİ뾶
	rt3 = sqrt(pow(testPoint.x - p2.x, 2) + pow(testPoint.y - p2.y, 2));   //���㸺(��???)��ɵ�p��λ�õİ뾶	
	rt4 = sqrt(pow(testPoint.x - n2.x, 2) + pow(testPoint.y - n2.y, 2));   //������(��???)��ɵ�p��λ�õİ뾶
	//�������-x���������x-
	//һ��һ��
	Etx = (n1.x - testPoint.x) / pow(rt2, 3) + (testPoint.x - p1.x) / pow(rt1, 3)
		+ (n2.x - testPoint.x) / pow(rt4, 3) + (testPoint.x - p2.x) / pow(rt3, 3);//����x�᷽��ĳ�ǿ
	Ety = (n1.y - testPoint.y) / pow(rt2, 3) + (testPoint.y - p1.y) / pow(rt1, 3)
		+ (n2.y - testPoint.y) / pow(rt4, 3) + (testPoint.y - p2.y) / pow(rt3, 3);//����y�᷽��ĳ�ǿ

	Et = sqrt(pow(Etx, 2) + pow(Ety, 2));

	RECT r = { -10, -10, 90, -10 };
	TCHAR e[50];
	_stprintf(e, _T("%.2f"), Et);

	drawtext(e, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	return Et;
}

class Line
{
public:
	Line();
	~Line();

private:

};

Line::Line()
{
}

Line::~Line()
{
}




Poly p1;//����1
Poly n1;//����1
Poly p2;//����2
Poly n2;//����2

int main()
{
	//Poly p1();//����1
	//Poly n1();//����1
	//Poly p2();//����2
	//Poly n2();//����2


	//p1.x = -200;
	//p1.y = 200;
	//n1.x = -200;
	//n1.y = -200;

	//p2.x = 200;
	//p2.y = 200;
	//n2.x = 400;
	//n2.y = 200-400*sin(PI/3);

	p1.x = -200;
	p1.y = 0;
	n1.x = 200;
	n1.y = 0;
	p1.isZheng = true;
	n1.isZheng = false;
	p2.isZheng = true;
	n2.isZheng = false;
	p2.x = 0;
	p2.y = 200;
	n2.x = 0;
	n2.y = -200;


	p1.x = -200;
	p1.y = -200;
	n1.x = -200;
	n1.y = 200;
	p2.x = 200;
	p2.y = -200;
	n2.x = 200;
	n2.y = 200;





	p1.x = 200;
	p1.y = 0;

	p1.x = 300;
	p1.y = -100;

	n1 = getOtherPoint(p1, 400, 78);
	p2.x = 0;
	p2.y = 0;
	n2 = getOtherPoint(p2, 400, 300);

	double angleP = getTwoPositiveAngle(p1, p2);



	double  angle1 = 0.0;		//���ñ���
	double  angle2;
	double x1, y1, Etx, Ety, Et, xt0, yt0, rt1, rt2;
	double x2, y2, Evx, Evy, Ev, xv0, yv0, rv1, rv2;
	double rt3, rt4, rv3, rv4;
	double x3, y3;
	vector<double> linePointP1  ;
	vector<double> linePointP2;
	vector<double> linePointN1;
	vector<double> linePointN2;
	vector<Poly> polys;
	 vector<double> distenceToP;


	polys.push_back(p1);
	polys.push_back(p2);
	polys.push_back(n1);
	polys.push_back(n2);
	int r = 15;


	initgraph(W, L);								//��ʼ����Ļ
	setbkcolor(WHITE);							//���ñ���ɫ
	cleardevice();								//�����Ļ����
	setorigin(400, 400);							//��������ԭ��λ��
	setlinecolor(BLACK);						//�����ߵ���ɫΪ��ɫ

	setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 2);		//������Ϊ���ߣ��˵�Ϊƽ̹��
	line(0, -400, 0, 400);							//y��
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 2);	//������Ϊʵ�ߣ��˵�Ϊƽ̹��
	line(-400, 0, 400, 0);							//x��

	for (int i = 0; i < polys.size(); i++)
	{
		circle(p1.x, p1.y, r);							//���뾶Ϊ15��Բ�������Բ���������
		setfillcolor(RED);							//���������ɫΪ��ɫ
		fillcircle(p1.x, p1.y, r);						//��������

		circle(n1.x, n1.y, r);							//���뾶Ϊ15��Բ�������Բ���������
		setfillcolor(BLUE);							//���������ɫΪ��ɫ
		fillcircle(n1.x, n1.y, r);						//��为���
	}

	

	//���ڶ��Ե��
	circle(p2.x, p2.y, r);							//���뾶Ϊ15��Բ�������Բ���������
	setfillcolor(RGB(250, 128, 114));							//���������ɫΪ��ɫ
	fillcircle(p2.x, p2.y, r);						//��������

	circle(n2.x, n2.y, r);							//���뾶Ϊ15��Բ�������Բ���������
	setfillcolor(RGB(99, 184, 255));							//���������ɫΪ��ɫ
	fillcircle(n2.x, n2.y, r);						//��为���






	line(p2.x - 8, 0, p2.x + 8, 0);
	line(p2.x, -8, p2.x, 8);						//������
	line(n2.x - 8, 0, n2.x + 8, 0);							//������

	angle1 = angleP;
	angle2 = angleP + PI   ;
	//angle2 =  angleP+PI+ 1* PI /LINE ;
	double a = angleP / PI * 180;
	

	//double test1 = testPointNum(-20, -300, p1, p2, n1, n2);
	//double test2 = testPointNum(-10, -300, p1, p2, n1, n2);
	//double test3 = testPointNum(0, -300, p1, p2, n1, n2);
	//double test4 = testPointNum(10, -300, p1, p2, n1, n2);

	//double test5 = testPointNum(20, -300, p1, p2, n1, n2);



	ofstream output;
	output.open("number.txt");
	bool flag = p1.x < p2.x;
	int numPoly = polys.size();
	int startPoint[100];
	for (int i = 0; i < LINE; i++)						//����Ҫ���ߵ�ѭ������
	{
		//for (int pN = 0; pN < polys.size(); pN++)
		//{
		//	startPoint[pN] = polys.at(pN).x+r*cos(angle1);
		//	startPoint[pN] = polys.at(pN).y + r * sin(angle1);
		//}
		x1 = p1.x + 15 * cos(angle1);						//���úó������ߵ�ĳ���λ��
		y1 = p1.y + 15 * sin(angle1);							//�԰뾶Ϊ15��Բ��ȦΪ������

		x3 = p2.x + 15 * cos(angle2);						//���úó������ߵ�ĳ���λ��
		y3 = p2.y + 15 * sin(angle2);							//�԰뾶Ϊ15��Բ��ȦΪ������


		x3 = p2.x + 15 * cos(angle2);						//���úó������ߵ�ĳ���λ��
		y3 = p2.y + 15 * sin(angle2);

		x3 = p2.x + 15 * cos(angle2);						//���úó������ߵ�ĳ���λ��
		y3 = p2.y + 15 * sin(angle2);
 
		/*if (i == 0 || i == 19) {
			if (flag)
			{
				angle1 += 2 * PI / LINE;
				angle2 -= 2 * PI / LINE;
			}
			else
			{
				angle1 -= 2 * PI / LINE;
				angle2 += 2 * PI / LINE;
			}
			continue;
		}*/
		for (int j = 0; j < NUM; j++)					//��������
		{
			{
				//��ȡ
				//for (int rSize = 0; rSize < polys.size(); rSize++) {
				//	distenceToP.at(rSize) ;
				//	double distance = 0;
				//	for (int pSize = 0; pSize < polys.size(); pSize++) {
				//		distance = sqrt(pow(x1 - distenceToP.at(pSize).x, 2) + pow(y1 - p1.y, 2));
				//	}
				//	if (i == 0)
				//	{
				//		distenceToP.push_back(distance);

				//	}
				//	else {
				//		distenceToP.at(rSize) = distance;
				//	}
				//}

				//
				rt1 = sqrt(pow(x1 - p1.x, 2) + pow(y1 - p1.y, 2));   //���㸺(��???)��ɵ�p��λ�õİ뾶	
				rt2 = sqrt(pow(x1 - n1.x, 2) + pow(y1 - n1.y, 2));   //������(��???)��ɵ�p��λ�õİ뾶
				rt3 = sqrt(pow(x1 - p2.x, 2) + pow(y1 - p2.y, 2));   //���㸺(��???)��ɵ�p��λ�õİ뾶	
				rt4 = sqrt(pow(x1 - n2.x, 2) + pow(y1 - n2.y, 2));   //������(��???)��ɵ�p��λ�õİ뾶
				//�������-x���������x-
				//һ��һ�� 
				Etx = (n1.x - x1) / pow(rt2, 3) + (x1 - p1.x) / pow(rt1, 3)
					+ (n2.x - x1) / pow(rt4, 3) + (x1 - p2.x) / pow(rt3, 3);//����x�᷽��ĳ�ǿ
				Ety = (n1.y - y1) / pow(rt2, 3) + (y1 - p1.y) / pow(rt1, 3)
					+ (n2.y - y1) / pow(rt4, 3) + (y1 - p2.y) / pow(rt3, 3);//����y�᷽��ĳ�ǿ

				Etx = round(Etx, 20);
				Ety = round(Ety, 20);

				
				Et = sqrt(pow(Etx, 2) + pow(Ety, 2));
				xt0 = x1 + 1 * Etx / Et;							//�������֮��p���λ��
				yt0 = y1 + 1 * Ety / Et;							//�������֮��p���λ��
				linePointP1.push_back(x1);

				if (pow(x1 - p1.x, 2) + pow(y1 - p1.y, 2) > 15 * 15 && pow(x1 - p2.x, 2) + pow(y1 - p2.y, 2) > 15 * 15)
				{
					line(x1, y1, xt0, yt0);					//��������

				}
				x1 = xt0;								//����x����
				y1 = yt0;								//����y����
				output <<"Ex:"<<Etx<<"\t"<<"Ey:"<<Ety << "\t" <<"E:"<< Et << endl;

				rv1 = sqrt(pow(x3 - p1.x, 2) + pow(y3 - p1.y, 2));   //���㸺(��???)��ɵ�p��λ�õİ뾶	
				rv2 = sqrt(pow(x3 - n1.x, 2) + pow(y3 - n1.y, 2));   //������(��???)��ɵ�p��λ�õİ뾶
				rv3 = sqrt(pow(x3 - p2.x, 2) + pow(y3 - p2.y, 2));   //���㸺(��???)��ɵ�p��λ�õİ뾶	
				rv4 = sqrt(pow(x3 - n2.x, 2) + pow(y3 - n2.y, 2));   //������(��???)��ɵ�p��λ�õİ뾶
				//�������-x���������x-
				//һ��һ��
				Evx = (n1.x - x3) / pow(rv2, 3) + (x3 - p1.x) / pow(rv1, 3)
					+ (n2.x - x3) / pow(rv4, 3) + (x3 - p2.x) / pow(rv3, 3);//����x�᷽��ĳ�ǿ
				Evy = (n1.y - y3) / pow(rv2, 3) + (y3 - p1.y) / pow(rv1, 3)
					+ (n2.y - y3) / pow(rv4, 3) + (y3 - p2.y) / pow(rv3, 3);//����y�᷽��ĳ�ǿ
				


				Ev = sqrt(pow(Evx, 2) + pow(Evy, 2));
				xv0 = x3 + 1 * Evx / Ev;							//�������֮��p���λ��
				yv0 = y3 + 1 * Evy / Ev;							//�������֮��p���λ��
				linePointP1.push_back(x3);

				if (pow(x3 - p1.x, 2) + pow(y3 - p1.y, 2) > 15 * 15|| pow(x3 - p2.x, 2) + pow(y3 - p2.y, 2) > 15 * 15)
				{
					line(x3, y3, xv0, yv0);					//��������

				}
					 

				x3 = xv0;								//����x����
				y3 = yv0;								//����y����

				


			}


		}
		if (flag)
		{
			angle1 += 2 * PI / LINE;
			angle2 -= 2 * PI / LINE;
		}
		else
		{
			angle1 -= 2 * PI / LINE;
			angle2 += 2 * PI / LINE;
		}
		 
	}
	output.close();
	system("pause");
}

#endif