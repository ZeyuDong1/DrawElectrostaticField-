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
#define LINE 60			//设置划线数量
#define NUM 3000		//迭代次数

#define LENTH 50


class Point
{
public:
	double x;
	double y;
	double ex;
	double ey;
	double e;
	Point();
	static double round(double number, unsigned int bits) {
		stringstream ss;
		ss << fixed << setprecision(bits) << number;
		ss >> number;
		return number;
	}
	static double getAngle(double x, double y)
	{
		double angle = atan2(y, x);
		return angle * (180 / PI);
	}

	~Point();

private:

};

Point::Point()
{
	x = NULL;
	y = NULL;
	ex = NULL;
	ey = NULL;
	e = NULL;

}

Point::~Point()
{
}

class Line
{
public:
	Point startPoint;
	vector<Point> points;
	Point endPoint;
	int endTarget;
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

//
class Poly
{
public:
	int x;
	int y;
	bool isZheng;
	int lineNum;
	vector<Line> lines;

	Poly();
	Poly(int line);
	Poly(int x, int y, bool isZheng, int lineNum);
	~Poly();
	int getX() {
		return this->x;
	}
	int getY() {
		return this->y;
	}
	bool getIsZheng() {
		return this->isZheng;
	}
	void setIsZheng(bool isZheng) {
		this->isZheng = isZheng;
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
	vector<Line> getLines() {
		return lines;
	}
private:

};

Poly::Poly()
{
	x = NULL;
	y = NULL;
	isZheng = NULL;
	lineNum = NULL;
	lines.empty();


}


Poly::Poly(int line)
{
	lineNum = line;
}

Poly::Poly(int x, int y, bool isZheng, int lineNum)
{
	this->x = x;
	this->y = y;
	this->lineNum = lineNum;
	this->isZheng = isZheng;
}

Poly::~Poly() {
	lines.empty();
}

Poly  getOtherPoint(Poly pp, double Barlong, double angle)
{
	Poly e;
	e.setX(pp.getX() + (Barlong * cos(angle / 180 * PI)));
	e.setY(pp.getY() + (Barlong * sin(angle / 180 * PI)));
	return e;
}
//获取两个正极之间的角度
double getTwoPositiveAngle(Poly p1, Poly p2)
{
	double angle = atan2(p2.getY() - p1.getY(), p2.getX() - p1.getX());
	return angle;
}

double getAngle(double x, double y)
{
	double angle = atan2(y, x);
	return angle * (180 / PI);
}


////获取某一点的场强并在该位置绘制图形
//double testPointNum(double x,double y,Poly p1, Poly p2,Poly n1,Poly n2)
//{
//	Poly testPoint;
//	testPoint.setX(x);
//	testPoint.setY(y);
//
//	double rt1, rt2, rt3, rt4,Etx,Ety,Et;
//
//	circle(testPoint.x, testPoint.y, 5);
//	setfillcolor(RED);
//	fillcircle(testPoint.x, testPoint.y, 5);
//
//	rt1 = sqrt(pow(testPoint.x - p1.x, 2) + pow(testPoint.y - p1.y, 2));   //计算负(正???)电荷到p点位置的半径	
//	rt2 = sqrt(pow(testPoint.x - n1.x, 2) + pow(testPoint.y - n1.y, 2));   //计算正(负???)电荷到p点位置的半径
//	rt3 = sqrt(pow(testPoint.x - p2.x, 2) + pow(testPoint.y - p2.y, 2));   //计算负(正???)电荷到p点位置的半径	
//	rt4 = sqrt(pow(testPoint.x - n2.x, 2) + pow(testPoint.y - n2.y, 2));   //计算正(负???)电荷到p点位置的半径
//	//正电荷是-x，负电荷是x-
//	//一正一负
//	Etx = (n1.x - testPoint.x) / pow(rt2, 3) + (testPoint.x - p1.x) / pow(rt1, 3)
//		+ (n2.x - testPoint.x) / pow(rt4, 3) + (testPoint.x - p2.x) / pow(rt3, 3);//计算x轴方向的场强
//	Ety = (n1.y - testPoint.y) / pow(rt2, 3) + (testPoint.y - p1.y) / pow(rt1, 3)
//		+ (n2.y - testPoint.y) / pow(rt4, 3) + (testPoint.y - p2.y) / pow(rt3, 3);//计算y轴方向的场强
//
//	Et = sqrt(pow(Etx, 2) + pow(Ety, 2));
//
//	return Et;
//}


double getDistance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

}

Point centerPoint(double x1, double y1, double x2, double y2)
{
	Point point;
	point.x = (x1 + x2) / 2;
	point.y = (y1 + y2) / 2;
	return point;
}

Poly p1;//正极1
Poly n1;//负极1
Poly p2;//正极2
Poly n2;//负极2



vector<Poly> calculateLines(vector<Poly> polys,int lineNum)
{
	double angle1 = 0;
	double angle2 = 0;
	bool flag = true;
	double r = 15;
	{
		for (int p = 0; p < polys.size(); p++) {
			for (int i = 0; i < lineNum; i++)						//设置要画线的循环条件
			{
				Line aline;


				if (polys.at(p).isZheng) {
					if (flag) {
						aline.startPoint.x = polys.at(p).x + r * cos(angle1);
						aline.startPoint.y = polys.at(p).y + r * sin(angle1);
						polys.at(p).lines.push_back(aline);
						flag = -1 * flag;
					}
					else {
						aline.startPoint.x = polys.at(p).x + r * cos(angle2);
						aline.startPoint.y = polys.at(p).y + r * sin(angle2);
						polys.at(p).lines.push_back(aline);
						flag = -1 * flag;
					}

				}

				else
				{
					continue;
				}
				//output<<"i\t"<<i<<"\t"<< polys.at(p).lines.at(i).startPoint.x<<"\t"<< polys.at(p).lines.at(i).startPoint.y  <<endl;
				polys.at(p).lines.at(i).endPoint = polys.at(p).lines.at(i).startPoint;
				Point point;
				point = polys.at(p).lines.at(i).startPoint;

				for (int j = 0; j < NUM; j++)					//迭代次数
				{
					{
						polys.at(p).lines.at(i).endTarget = -1;

						vector<double> distanceToP;
						//output << "rt\t";
						for (int pp = 0; pp < polys.size(); pp++) {
							distanceToP.push_back(sqrt(pow(point.x - polys.at(pp).x, 2) + pow(point.y - polys.at(pp).y, 2)));
							//output<< distanceToP.at(pp)<<"\t";
						}
						//output<<endl;

						//rt1 = sqrt(pow(x1 - p1.x, 2) + pow(y1 - p1.y, 2));   //计算负(正???)电荷到p点位置的半径	
						//rt2 = sqrt(pow(x1 - n1.x, 2) + pow(y1 - n1.y, 2));   //计算正(负???)电荷到p点位置的半径
						//rt3 = sqrt(pow(x1 - p2.x, 2) + pow(y1 - p2.y, 2));   //计算负(正???)电荷到p点位置的半径	
						//rt4 = sqrt(pow(x1 - n2.x, 2) + pow(y1 - n2.y, 2));   //计算正(负???)电荷到p点位置的半径
						//正电荷是-x，负电荷是x-
						//一正一负 
						point.ex = 0;
						point.ey = 0;
						//output << "E\t";
						for (int pp = 0; pp < polys.size(); pp++) {
							if (polys.at(pp).isZheng) {
								point.ex += (point.x - polys.at(pp).x) / pow(distanceToP.at(pp), 3);
								point.ey += (point.y - polys.at(pp).y) / pow(distanceToP.at(pp), 3);
								double xx = (point.x - polys.at(pp).x) / pow(distanceToP.at(pp), 3);
								double yy = (point.y - polys.at(pp).y) / pow(distanceToP.at(pp), 3);

							}
							else
							{
								point.ex += (polys.at(pp).x - point.x) / pow(distanceToP.at(pp), 3);
								point.ey += (polys.at(pp).y - point.y) / pow(distanceToP.at(pp), 3);
								double xx = (polys.at(pp).x - point.x) / pow(distanceToP.at(pp), 3);
								double yy = (polys.at(pp).y - point.y) / pow(distanceToP.at(pp), 3);

							}

						}
						//Etx = (n1.x - x1) / pow(rt2, 3) + (x1 - p1.x) / pow(rt1, 3)
						//	+ (n2.x - x1) / pow(rt4, 3) + (x1 - p2.x) / pow(rt3, 3);//计算x轴方向的场强
						//Ety = (n1.y - y1) / pow(rt2, 3) + (y1 - p1.y) / pow(rt1, 3)
						//	+ (n2.y - y1) / pow(rt4, 3) + (y1 - p2.y) / pow(rt3, 3);//计算y轴方向的场强

						point.ex = Point::round(point.ex, 20);
						point.ey = Point::round(point.ey, 20);
						if (point.x > 400 || point.y > 400 || point.x < -400 || point.y < -400) {
							break;
						}
						point.e = sqrt(pow(point.ex, 2) + pow(point.ey, 2));

						//output << point.ex << "\t" << point.ey << "\t" << point.e<<endl;


						polys.at(p).lines.at(i).points.push_back(point);
						point.x += point.ex / point.e;
						point.y += point.ey / point.e;
						if (point.x > 400 || point.y > 400 || point.x < -400 || point.y < -400) {
							break;
						}
						bool isGetInTheNCircle = false; //是否进入了N极
						for (int g = 0; g < polys.size(); g++) {
							if (!polys.at(g).isZheng) {
								if (pow(point.x - polys.at(g).x, 2) + pow(point.y - polys.at(g).y, 2) <= 15 * 15) {
									isGetInTheNCircle = true;
									polys.at(p).lines.at(i).endTarget = g;
									break;
								}
							}
						}


						if (isGetInTheNCircle) {
							polys.at(p).lines.at(i).endPoint = point;
							break;
						}



						distanceToP.empty();
					}


				}

				angle1 += 2 * PI / lineNum;
				angle2 += 2 * PI / lineNum;
			}

		}

		return polys;



	}
}


vector<Poly> calculateLines2(vector<Poly> polys, int lineNum,int firstGap, int lastGap)
{
	double angle1 = 0;
	double angle2 = 0;
	bool flag = true;
	double r = 15;
	{
		for (int p = 0; p < polys.size(); p++) {
			for (int i = 0; i < lineNum; i++)						//设置要画线的循环条件
			{
				if (i > firstGap && i < lastGap)
				{
					break;
				}
				Line aline;


				if (polys.at(p).isZheng) {
					if (flag) {
						aline.startPoint.x = polys.at(p).x + r * cos(angle1);
						aline.startPoint.y = polys.at(p).y + r * sin(angle1);
						polys.at(p).lines.push_back(aline);
						flag = -1 * flag;
					}
					else {
						aline.startPoint.x = polys.at(p).x + r * cos(angle2);
						aline.startPoint.y = polys.at(p).y + r * sin(angle2);
						polys.at(p).lines.push_back(aline);
						flag = -1 * flag;
					}

				}

				else
				{
					continue;
				}
				//output<<"i\t"<<i<<"\t"<< polys.at(p).lines.at(i).startPoint.x<<"\t"<< polys.at(p).lines.at(i).startPoint.y  <<endl;
				polys.at(p).lines.at(i).endPoint = polys.at(p).lines.at(i).startPoint;
				Point point;
				point = polys.at(p).lines.at(i).startPoint;

				for (int j = 0; j < NUM; j++)					//迭代次数
				{
					{
						polys.at(p).lines.at(i).endTarget = -1;

						vector<double> distanceToP;
						//output << "rt\t";
						for (int pp = 0; pp < polys.size(); pp++) {
							distanceToP.push_back(sqrt(pow(point.x - polys.at(pp).x, 2) + pow(point.y - polys.at(pp).y, 2)));
							//output<< distanceToP.at(pp)<<"\t";
						}
						//output<<endl;

						//rt1 = sqrt(pow(x1 - p1.x, 2) + pow(y1 - p1.y, 2));   //计算负(正???)电荷到p点位置的半径	
						//rt2 = sqrt(pow(x1 - n1.x, 2) + pow(y1 - n1.y, 2));   //计算正(负???)电荷到p点位置的半径
						//rt3 = sqrt(pow(x1 - p2.x, 2) + pow(y1 - p2.y, 2));   //计算负(正???)电荷到p点位置的半径	
						//rt4 = sqrt(pow(x1 - n2.x, 2) + pow(y1 - n2.y, 2));   //计算正(负???)电荷到p点位置的半径
						//正电荷是-x，负电荷是x-
						//一正一负 
						point.ex = 0;
						point.ey = 0;
						//output << "E\t";
						for (int pp = 0; pp < polys.size(); pp++) {
							if (polys.at(pp).isZheng) {
								point.ex += (point.x - polys.at(pp).x) / pow(distanceToP.at(pp), 3);
								point.ey += (point.y - polys.at(pp).y) / pow(distanceToP.at(pp), 3);
								double xx = (point.x - polys.at(pp).x) / pow(distanceToP.at(pp), 3);
								double yy = (point.y - polys.at(pp).y) / pow(distanceToP.at(pp), 3);

							}
							else
							{
								point.ex += (polys.at(pp).x - point.x) / pow(distanceToP.at(pp), 3);
								point.ey += (polys.at(pp).y - point.y) / pow(distanceToP.at(pp), 3);
								double xx = (polys.at(pp).x - point.x) / pow(distanceToP.at(pp), 3);
								double yy = (polys.at(pp).y - point.y) / pow(distanceToP.at(pp), 3);

							}

						}
						//Etx = (n1.x - x1) / pow(rt2, 3) + (x1 - p1.x) / pow(rt1, 3)
						//	+ (n2.x - x1) / pow(rt4, 3) + (x1 - p2.x) / pow(rt3, 3);//计算x轴方向的场强
						//Ety = (n1.y - y1) / pow(rt2, 3) + (y1 - p1.y) / pow(rt1, 3)
						//	+ (n2.y - y1) / pow(rt4, 3) + (y1 - p2.y) / pow(rt3, 3);//计算y轴方向的场强

						point.ex = Point::round(point.ex, 20);
						point.ey = Point::round(point.ey, 20);
						if (point.x > 400 || point.y > 400 || point.x < -400 || point.y < -400) {
							break;
						}
						point.e = sqrt(pow(point.ex, 2) + pow(point.ey, 2));

						//output << point.ex << "\t" << point.ey << "\t" << point.e<<endl;


						polys.at(p).lines.at(i).points.push_back(point);
						point.x += point.ex / point.e;
						point.y += point.ey / point.e;
						if (point.x > 400 || point.y > 400 || point.x < -400 || point.y < -400) {
							break;
						}
						bool isGetInTheNCircle = false; //是否进入了N极
						for (int g = 0; g < polys.size(); g++) {
							if (!polys.at(g).isZheng) {
								if (pow(point.x - polys.at(g).x, 2) + pow(point.y - polys.at(g).y, 2) <= 15 * 15) {
									isGetInTheNCircle = true;
									polys.at(p).lines.at(i).endTarget = g;
									break;
								}
							}
						}


						if (isGetInTheNCircle) {
							polys.at(p).lines.at(i).endPoint = point;
							break;
						}



						distanceToP.empty();
					}


				}

				angle1 += 2 * PI / lineNum;
				angle2 += 2 * PI / lineNum;
			}

		}

		return polys;



	}
}



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


	//p1.x = -200;
	//p1.y = 0;
	//n1.x = 200;
	//n1.y = 0;
	//p1.isZheng = true;
	//n1.isZheng = false;
	//p2.isZheng = true;
	//n2.isZheng = false;
	//p2.x = 0;
	//p2.y = 200;
	//n2.x = 0;
	//n2.y = -200;


	p1.x = -200;
	p1.y = -200;
	n1.x = 200;
	n1.y = -200;
	p2.x = -200;
	p2.y = 200;
	n2.x = 200;
	n2.y = 200;


	p1.x = -100;
	p1.y = -100;
	n1.x = 100;
	n1.y = -100;
	p2.x = -100;
	p2.y = 100;
	n2.x = 100;
	n2.y = 100;




	//p1.x = 200;
	//p1.y = 0;



	//p1.x = 200;
	//p1.y = -100;


	p1.isZheng = true;
	p2.isZheng = true;
	//n1 = getOtherPoint(p1, 400, 78);
	//p2.x = -200;
	//p2.y = 0;
	//n2 = getOtherPoint(p2, 400, 300);

	double angleP = getTwoPositiveAngle(p1, p2);



	double  angle1 = 0.0;		//设置变量
	double  angle2;
	double x1, y1, Etx, Ety, Et, xt0, yt0, rt1, rt2;
	double x2, y2, Evx, Evy, Ev, xv0, yv0, rv1, rv2;
	double rt3, rt4, rv3, rv4;
	double x3, y3;
	vector<Poly> polys;


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
		//{
		circle(p1.x, p1.y, r);							//画半径为15的圆，把这个圆当做正电荷
	setfillcolor(RED);							//设置填充颜色为红色
	fillcircle(p1.x, p1.y, r);						//填充正电荷

	circle(n1.x, n1.y, r);							//画半径为15的圆，把这个圆当做负电荷
	setfillcolor(BLUE);							//设置填充颜色为蓝色
	fillcircle(n1.x, n1.y, r);						//填充负电荷
//}



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

	//angle1 = angleP;
	//angle2 = angleP + PI;
	////angle2 =  angleP+PI+ 1* PI /LINE ;
	//double a = angleP / PI * 180;
	angle2 = 0;

	//double test1 = testPointNum(-20, -300, p1, p2, n1, n2);
	//double test2 = testPointNum(-10, -300, p1, p2, n1, n2);
	//double test3 = testPointNum(0, -300, p1, p2, n1, n2);
	//double test4 = testPointNum(10, -300, p1, p2, n1, n2);

	//double test5 = testPointNum(20, -300, p1, p2, n1, n2);



	ofstream output;
	output.open("number.txt");
	//bool flag = p1.x < p2.x;
	int numPoly = polys.size();
	bool flag = true;



#define kuan 800
#define gao 800
	{
		{
			polys.clear();
			polys.push_back(p1);
			polys.push_back(n1);
			polys = calculateLines(polys,40);


			vector<Poly> polysDown;
			polysDown.push_back(p2);
			polysDown.push_back(n2);
			polysDown = calculateLines(polysDown,20);



			vector<Poly> polysCenter;
			p1.x = -100;
			p1.y = 0;
			n1.x = 100;
			n1.y = 0;
			polysCenter.push_back(p1);
			polysCenter.push_back(n1);
			polysCenter = calculateLines(polysCenter,40);

			vector<Poly> polysMid;
			p1.x = -100;
			p1.y = 0;
			n1.x = 100;
			n1.y = 0;
			polysMid.push_back(p1);
			polysMid.push_back(n1);
			polysMid = calculateLines2(polysMid, 80,5,75);




			int lineNum = 30;
			
	/*		
			for (int j = 0; j < polys[0].lines.size(); j++) {
				if (j > polys[0].lines.size() / 2) {
					for (int i = 0; i < polys[0].lines.at(j).points.size(); i++) {
						polys[0].lines.at(j).points.at(i).y -= 10;
					}
				}
				
			}*/

			vector<Line> oppositeLines;
			
			for (int p = 0; p < polys.size(); p++) {
				for (int i = 0; i < polys.at(p).lines.size(); i++)						//设置要画线的循环条件
				{
						Line aline;
						for (int j = 0; j < polys.at(p).lines.at(i).points.size() ; j++) {
							
							Point apoint;
							apoint.x = -polys.at(p).lines.at(i).points.at(j).x;
							apoint.y = polys.at(p).lines.at(i).points.at(j).y;
						
							aline.points.push_back(apoint);							

						}
						oppositeLines.push_back(aline);
				}
			}


			try
			{
				for (int p = 0; p < polys.size(); p++) {
					for (int i = 0; i < polys.at(p).lines.size(); i++)						//设置要画线的循环条件
					{
						if(i> 24)
							for (int j = 0; j < polys.at(p).lines.at(i).points.size() - 1; j++) {
								{
									if(polys.at(p).lines.at(i).points.at(j).x<0)
									line(polys.at(p).lines.at(i).points.at(j).x, polys.at(p).lines.at(i).points.at(j).y, polys.at(p).lines.at(i).points.at(j + 1).x, polys.at(p).lines.at(i).points.at(j + 1).y);
									if (oppositeLines.at(i).points.at(j).x > 0)


									line(oppositeLines.at(i).points.at(j).x, oppositeLines.at(i).points.at(j).y, oppositeLines.at(i).points.at(j + 1).x, oppositeLines.at(i).points.at(j + 1).y);
								}
							
							}
					}
				}


				for (int p = 0; p < polysDown.size(); p++) {
					for (int i = 0; i < polysDown.at(p).lines.size(); i++)						//设置要画线的循环条件
					{
						if (i < 7)

							for (int j = 0; j < polysDown.at(p).lines.at(i).points.size() - 1; j++) {
							
									line(polysDown.at(p).lines.at(i).points.at(j).x, polysDown.at(p).lines.at(i).points.at(j).y, polysDown.at(p).lines.at(i).points.at(j + 1).x, polysDown.at(p).lines.at(i).points.at(j + 1).y);
														

							}
					}
				}


				for (int p = 0; p < polysCenter.size(); p++) {
					int lineSize = polysCenter.at(p).lines.size();
					for (int i = 0; i < lineSize; i++)						//设置要画线的循环条件
					{
						int pointSize = polysCenter.at(p).lines.at(i).points.size();
						if((i>13&&i<25))
						for (int j = 0; j < pointSize - 1; j++) {
							if ((i > 13 && i < 25))
							{
								if (i > lineSize / 2) {
									line(polysCenter.at(p).lines.at(i).points.at(j).x, polysCenter.at(p).lines.at(i).points.at(j).y - (i % 20) * 15, polysCenter.at(p).lines.at(i).points.at(j + 1).x, polysCenter.at(p).lines.at(i).points.at(j + 1).y - (i % 20) * 15);
									line(-polysCenter.at(p).lines.at(i).points.at(j).x, polysCenter.at(p).lines.at(i).points.at(j).y - (i % 20) * 15, -polysCenter.at(p).lines.at(i).points.at(j + 1).x, polysCenter.at(p).lines.at(i).points.at(j + 1).y - (i % 20) * 15);

								}
								else
								{
									line(polysCenter.at(p).lines.at(i).points.at(j).x, polysCenter.at(p).lines.at(i).points.at(j).y + (20 - i) * 15, polysCenter.at(p).lines.at(i).points.at(j + 1).x, polysCenter.at(p).lines.at(i).points.at(j + 1).y + (20 - i) * 15);
									line(-polysCenter.at(p).lines.at(i).points.at(j).x, polysCenter.at(p).lines.at(i).points.at(j).y + (20 - i) * 15, -polysCenter.at(p).lines.at(i).points.at(j + 1).x, polysCenter.at(p).lines.at(i).points.at(j + 1).y + (20 - i) * 15);

								}
							}
							
						}
					}
				}
				for (int p = 0; p < polysMid.size(); p++) {
					int lineSize = polysMid.at(p).lines.size();
					for (int i = 0; i < lineSize; i++)						//设置要画线的循环条件
					{
						int pointSize = polysMid.at(p).lines.at(i).points.size();
							for (int j = 0; j < pointSize - 1; j++) {
				
								{
									/*if (i > lineSize / 2)*/ {
										line(polysMid.at(p).lines.at(i).points.at(j).x, polysMid.at(p).lines.at(i).points.at(j).y - (80-i) * 15, polysMid.at(p).lines.at(i).points.at(j + 1).x, polysMid.at(p).lines.at(i).points.at(j + 1).y - (80 - i) * 15);

									}
									/*else
									{
										line(polysMid.at(p).lines.at(i).points.at(j).x, polysMid.at(p).lines.at(i).points.at(j).y + ( i) * 15, polysMid.at(p).lines.at(i).points.at(j + 1).x, polysMid.at(p).lines.at(i).points.at(j + 1).y + ( i) * 15);

									}*/
								}

							}
					}
				}
			}
			catch (const std::exception&)
			{

			}
			vector<Point> endPointInFirstS;
			vector<Point> endPointInSecondS;
			for (int p = 0; p < polys.size(); p++) {
				for (int i = 0; i < polys.at(p).lines.size();i++) {
					if (polys.at(p).lines.at(i).endTarget == 2) {
						endPointInFirstS.push_back(polys.at(p).lines.at(i).endPoint);
					}
					if (polys.at(p).lines.at(i).endTarget == 3) {
						endPointInSecondS.push_back(polys.at(p).lines.at(i).endPoint);
					}
				}
			}
			vector<double> anglePoints;
			for (int f = 0; f < endPointInFirstS.size(); f++) {
				anglePoints.push_back(Point::getAngle(endPointInFirstS.at(f).x, endPointInFirstS.at(f).y));
			}
			for (int f = 0; f < endPointInSecondS.size();f++){
				//anglePoints.push_back(Point::getAngle(endPointInFirstS.at(f).x, endPointInSecondS.at(f).y));
			}
			cout << 1;
		}
	}

	ofstream output2;
	output2.open("number2.txt");




	
	{
		//{
		//	for (int i = 0; i < LINE; i++)						//设置要画线的循环条件
		//	{
		//		Line aline;

		//		x1 = p1.x + 15 * cos(angle1);						//设置好出划画线点的出发位置
		//		y1 = p1.y + 15 * sin(angle1);							//以半径为15的圆线圈为出发点

		//		x3 = p2.x + 15 * cos(angle2);						//设置好出划画线点的出发位置
		//		y3 = p2.y + 15 * sin(angle2);							//以半径为15的圆线圈为出发点
		//		output2 << "i\t" << i << "\t" << x1 <<"\t"<< y1 << endl;
		//	
		//		for (int j = 0; j < NUM; j++)					//迭代次数
		//		{
		//			{
		//				//获取
		//				//for (int rSize = 0; rSize < polys.size(); rSize++) {
		//				//	distenceToP.at(rSize) ;
		//				//	double distance = 0;
		//				//	for (int pSize = 0; pSize < polys.size(); pSize++) {
		//				//		distance = sqrt(pow(x1 - distenceToP.at(pSize).x, 2) + pow(y1 - p1.y, 2));
		//				//	}
		//				//	if (i == 0)
		//				//	{
		//				//		distenceToP.push_back(distance);

		//				//	}
		//				//	else {
		//				//		distenceToP.at(rSize) = distance;
		//				//	}
		//				//}

		//				//
		//				
		//				rt1 = sqrt(pow(x1 - p1.x, 2) + pow(y1 - p1.y, 2));   //计算负(正???)电荷到p点位置的半径	
		//				rt2 = sqrt(pow(x1 - n1.x, 2) + pow(y1 - n1.y, 2));   //计算正(负???)电荷到p点位置的半径
		//				rt3 = sqrt(pow(x1 - p2.x, 2) + pow(y1 - p2.y, 2));   //计算负(正???)电荷到p点位置的半径	
		//				rt4 = sqrt(pow(x1 - n2.x, 2) + pow(y1 - n2.y, 2));   //计算正(负???)电荷到p点位置的半径
		//				output2<< "rt\t"<<rt1 << "\t" << rt3 << "\t" << rt2 <<"\t" << rt4 <<endl;
		//			 
		//				//正电荷是-x，负电荷是x-
		//				//一正一负 
		//				Etx = (n1.x - x1) / pow(rt2, 3) + (x1 - p1.x) / pow(rt1, 3);
		//					//+ (n2.x - x1) / pow(rt4, 3) + (x1 - p2.x) / pow(rt3, 3);//计算x轴方向的场强
		//				Ety = (n1.y - y1) / pow(rt2, 3) + (y1 - p1.y) / pow(rt1, 3);
		//					//+ (n2.y - y1) / pow(rt4, 3) + (y1 - p2.y) / pow(rt3, 3);//计算y轴方向的场强
		//				
		//				Etx = Point::round(Etx, 20);
		//				Ety = Point::round(Ety, 20);


		//				Et = sqrt(pow(Etx, 2) + pow(Ety, 2));
		//				output2<< "E\t" << Etx << "\t" <<Ety << "\t" <<Et<<endl;
		//				xt0 = x1 + 1 * Etx / Et;							//计算更新之后p点的位置
		//				yt0 = y1 + 1 * Ety / Et;							//计算更新之后p点的位置
		//				output2 << "x\t" << xt0 << "y\t" << yt0 << endl;

		//				//linePointP1.push_back(x1);

		//				//if (pow(x1 - n1.x, 2) + pow(y1 - n1.y, 2) > 15 * 15 && pow(x1 - n2.x, 2) + pow(y1 - n2.y, 2) > 15 * 15  )
		//				{
		//					line(x1, y1, xt0, yt0);					//连接两点

		//				}

		//				x1 = xt0;								//更新x坐标
		//				y1 = yt0;								//更新y坐标
		//				//output << pow(x1 - p1.x, 2) + pow(y1 - p1.y, 2) << endl;

		//				//rv1 = sqrt(pow(x3 - p1.x, 2) + pow(y3 - p1.y, 2));   //计算负(正???)电荷到p点位置的半径	
		//				//rv2 = sqrt(pow(x3 - n1.x, 2) + pow(y3 - n1.y, 2));   //计算正(负???)电荷到p点位置的半径
		//				//rv3 = sqrt(pow(x3 - p2.x, 2) + pow(y3 - p2.y, 2));   //计算负(正???)电荷到p点位置的半径	
		//				//rv4 = sqrt(pow(x3 - n2.x, 2) + pow(y3 - n2.y, 2));   //计算正(负???)电荷到p点位置的半径
		//				////正电荷是-x，负电荷是x-
		//				////一正一负
		//				//Evx = 
		//				//	(n2.x - x3) / pow(rv4, 3) + (x3 - p2.x) / pow(rv3, 3);//计算x轴方向的场强
		//				//	Evy = 
		//				//	(n2.y - y3) / pow(rv4, 3) + (y3 - p2.y) / pow(rv3, 3);//计算y轴方向的场强



		//				//Ev = sqrt(pow(Evx, 2) + pow(Evy, 2));
		//				//xv0 = x3 + 1 * Evx / Ev;							//计算更新之后p点的位置
		//				//yv0 = y3 + 1 * Evy / Ev;							//计算更新之后p点的位置
		//				////linePointP1.push_back(x3);

		//				//if (pow(x3 - n1.x, 2) + pow(y3 - n1.y, 2) > 15 * 15 && pow(x3 - n2.x, 2) + pow(y3 - n2.y, 2) > 15 * 15 && i < LINE / 2 && i!=0)
		//				//{
		//				//	line(x3, y3, xv0, yv0);					//连接两点

		//				//}



		//				//x3 = xv0;								//更新x坐标
		//				//y3 = yv0;								//更新y坐标




		//			}


		//		}
		//	
		//			angle1 += 2 * PI / LINE;
		//			angle2 += 2 * PI / LINE;
		//	
		//	}

		//}
	}


	output.close();
	system("pause");
}

#endif