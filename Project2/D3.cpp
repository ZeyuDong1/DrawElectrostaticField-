// 静电场.cpp : 定义控制台应用程序的入口点。
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
#define W 800			//宏定义屏幕宽
#define L 800			//宏定义屏幕长
#define LINE 20			//设置划线数量
#define NUM 3000		//迭代次数

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
//获取两个正极之间的角度
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


//获取某一点的场强并在该位置绘制图形
double testPointNum(double x,double y,Poly p1, Poly p2,Poly n1,Poly n2)
{
	Poly testPoint;
	testPoint.x = x;
	testPoint.y = y;

	double rt1, rt2, rt3, rt4,Etx,Ety,Et;

	circle(testPoint.x, testPoint.y, 5);
	setfillcolor(RED);
	fillcircle(testPoint.x, testPoint.y, 5);

	rt1 = sqrt(pow(testPoint.x - p1.x, 2) + pow(testPoint.y - p1.y, 2));   //计算负(正???)电荷到p点位置的半径	
	rt2 = sqrt(pow(testPoint.x - n1.x, 2) + pow(testPoint.y - n1.y, 2));   //计算正(负???)电荷到p点位置的半径
	rt3 = sqrt(pow(testPoint.x - p2.x, 2) + pow(testPoint.y - p2.y, 2));   //计算负(正???)电荷到p点位置的半径	
	rt4 = sqrt(pow(testPoint.x - n2.x, 2) + pow(testPoint.y - n2.y, 2));   //计算正(负???)电荷到p点位置的半径
	//正电荷是-x，负电荷是x-
	//一正一负
	Etx = (n1.x - testPoint.x) / pow(rt2, 3) + (testPoint.x - p1.x) / pow(rt1, 3)
		+ (n2.x - testPoint.x) / pow(rt4, 3) + (testPoint.x - p2.x) / pow(rt3, 3);//计算x轴方向的场强
	Ety = (n1.y - testPoint.y) / pow(rt2, 3) + (testPoint.y - p1.y) / pow(rt1, 3)
		+ (n2.y - testPoint.y) / pow(rt4, 3) + (testPoint.y - p2.y) / pow(rt3, 3);//计算y轴方向的场强

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




Poly p1;//正极1
Poly n1;//负极1
Poly p2;//正极2
Poly n2;//负极2

int main()
{
	//Poly p1();//正极1
	//Poly n1();//负极1
	//Poly p2();//正极2
	//Poly n2();//负极2


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



	double  angle1 = 0.0;		//设置变量
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


	initgraph(W, L);								//初始化屏幕
	setbkcolor(WHITE);							//设置背景色
	cleardevice();								//清除屏幕内容
	setorigin(400, 400);							//重新设置原点位置
	setlinecolor(BLACK);						//设置线的颜色为白色

	setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 2);		//设置线为虚线，端点为平坦的
	line(0, -400, 0, 400);							//y轴
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 2);	//设置线为实线，端点为平坦的
	line(-400, 0, 400, 0);							//x轴

	for (int i = 0; i < polys.size(); i++)
	{
		circle(p1.x, p1.y, r);							//画半径为15的圆，把这个圆当做正电荷
		setfillcolor(RED);							//设置填充颜色为红色
		fillcircle(p1.x, p1.y, r);						//填充正电荷

		circle(n1.x, n1.y, r);							//画半径为15的圆，把这个圆当做负电荷
		setfillcolor(BLUE);							//设置填充颜色为蓝色
		fillcircle(n1.x, n1.y, r);						//填充负电荷
	}

	

	//画第二对电荷
	circle(p2.x, p2.y, r);							//画半径为15的圆，把这个圆当做正电荷
	setfillcolor(RGB(250, 128, 114));							//设置填充颜色为红色
	fillcircle(p2.x, p2.y, r);						//填充正电荷

	circle(n2.x, n2.y, r);							//画半径为15的圆，把这个圆当做负电荷
	setfillcolor(RGB(99, 184, 255));							//设置填充颜色为蓝色
	fillcircle(n2.x, n2.y, r);						//填充负电荷






	line(p2.x - 8, 0, p2.x + 8, 0);
	line(p2.x, -8, p2.x, 8);						//画正号
	line(n2.x - 8, 0, n2.x + 8, 0);							//画负号

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
	for (int i = 0; i < LINE; i++)						//设置要画线的循环条件
	{
		//for (int pN = 0; pN < polys.size(); pN++)
		//{
		//	startPoint[pN] = polys.at(pN).x+r*cos(angle1);
		//	startPoint[pN] = polys.at(pN).y + r * sin(angle1);
		//}
		x1 = p1.x + 15 * cos(angle1);						//设置好出划画线点的出发位置
		y1 = p1.y + 15 * sin(angle1);							//以半径为15的圆线圈为出发点

		x3 = p2.x + 15 * cos(angle2);						//设置好出划画线点的出发位置
		y3 = p2.y + 15 * sin(angle2);							//以半径为15的圆线圈为出发点


		x3 = p2.x + 15 * cos(angle2);						//设置好出划画线点的出发位置
		y3 = p2.y + 15 * sin(angle2);

		x3 = p2.x + 15 * cos(angle2);						//设置好出划画线点的出发位置
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
		for (int j = 0; j < NUM; j++)					//迭代次数
		{
			{
				//获取
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
				rt1 = sqrt(pow(x1 - p1.x, 2) + pow(y1 - p1.y, 2));   //计算负(正???)电荷到p点位置的半径	
				rt2 = sqrt(pow(x1 - n1.x, 2) + pow(y1 - n1.y, 2));   //计算正(负???)电荷到p点位置的半径
				rt3 = sqrt(pow(x1 - p2.x, 2) + pow(y1 - p2.y, 2));   //计算负(正???)电荷到p点位置的半径	
				rt4 = sqrt(pow(x1 - n2.x, 2) + pow(y1 - n2.y, 2));   //计算正(负???)电荷到p点位置的半径
				//正电荷是-x，负电荷是x-
				//一正一负 
				Etx = (n1.x - x1) / pow(rt2, 3) + (x1 - p1.x) / pow(rt1, 3)
					+ (n2.x - x1) / pow(rt4, 3) + (x1 - p2.x) / pow(rt3, 3);//计算x轴方向的场强
				Ety = (n1.y - y1) / pow(rt2, 3) + (y1 - p1.y) / pow(rt1, 3)
					+ (n2.y - y1) / pow(rt4, 3) + (y1 - p2.y) / pow(rt3, 3);//计算y轴方向的场强

				Etx = round(Etx, 20);
				Ety = round(Ety, 20);

				
				Et = sqrt(pow(Etx, 2) + pow(Ety, 2));
				xt0 = x1 + 1 * Etx / Et;							//计算更新之后p点的位置
				yt0 = y1 + 1 * Ety / Et;							//计算更新之后p点的位置
				linePointP1.push_back(x1);

				if (pow(x1 - p1.x, 2) + pow(y1 - p1.y, 2) > 15 * 15 && pow(x1 - p2.x, 2) + pow(y1 - p2.y, 2) > 15 * 15)
				{
					line(x1, y1, xt0, yt0);					//连接两点

				}
				x1 = xt0;								//更新x坐标
				y1 = yt0;								//更新y坐标
				output <<"Ex:"<<Etx<<"\t"<<"Ey:"<<Ety << "\t" <<"E:"<< Et << endl;

				rv1 = sqrt(pow(x3 - p1.x, 2) + pow(y3 - p1.y, 2));   //计算负(正???)电荷到p点位置的半径	
				rv2 = sqrt(pow(x3 - n1.x, 2) + pow(y3 - n1.y, 2));   //计算正(负???)电荷到p点位置的半径
				rv3 = sqrt(pow(x3 - p2.x, 2) + pow(y3 - p2.y, 2));   //计算负(正???)电荷到p点位置的半径	
				rv4 = sqrt(pow(x3 - n2.x, 2) + pow(y3 - n2.y, 2));   //计算正(负???)电荷到p点位置的半径
				//正电荷是-x，负电荷是x-
				//一正一负
				Evx = (n1.x - x3) / pow(rv2, 3) + (x3 - p1.x) / pow(rv1, 3)
					+ (n2.x - x3) / pow(rv4, 3) + (x3 - p2.x) / pow(rv3, 3);//计算x轴方向的场强
				Evy = (n1.y - y3) / pow(rv2, 3) + (y3 - p1.y) / pow(rv1, 3)
					+ (n2.y - y3) / pow(rv4, 3) + (y3 - p2.y) / pow(rv3, 3);//计算y轴方向的场强
				


				Ev = sqrt(pow(Evx, 2) + pow(Evy, 2));
				xv0 = x3 + 1 * Evx / Ev;							//计算更新之后p点的位置
				yv0 = y3 + 1 * Evy / Ev;							//计算更新之后p点的位置
				linePointP1.push_back(x3);

				if (pow(x3 - p1.x, 2) + pow(y3 - p1.y, 2) > 15 * 15|| pow(x3 - p2.x, 2) + pow(y3 - p2.y, 2) > 15 * 15)
				{
					line(x3, y3, xv0, yv0);					//连接两点

				}
					 

				x3 = xv0;								//更新x坐标
				y3 = yv0;								//更新y坐标

				


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