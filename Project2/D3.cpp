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

#define kuan 800
#define gao 800
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


vector<Poly> calculateLines(vector<Poly> polys, int lineNum,int firstGap, int lastGap)
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


				if (polys.at(p).isZheng) {//正极绘制,负极绘制
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
				if (i > firstGap && i < lastGap)
				{
					continue;
				}
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

vector<Line> getOval(double x0, double y0, double ratio, double b, int lineSum,int pointSum,double density)
{
	vector<Line> lines;
 	double angle = 0;
	//int pointSum = 100;
	Point apoint;
	apoint.x = x0;
	apoint.y = y0;
	double a  ;
	 
	for (int j = 0; j < lineSum; j++)
	{
		Line aline;
		a = sqrt(ratio) * b;
		for (int i = 0; i < pointSum; i++)
		{
			apoint.x = a * cos(angle);
			//apoint.y = b * sin(angle) + b  ;
			 apoint.y = b * sin(angle) + b + (2000 / b);

			aline.points.push_back(apoint);
			angle += 2 * PI / pointSum;
		}
		lines.push_back(aline);
		if (j < 5)
			b *= density;
		else
			b *= 1.5;

	}
 	
	return lines;
}

vector<Line> getOval2(double x0, double y0, double ratio, double b, int lineSum, int pointSum, double density)
{
	vector<Line> lines;
	double angle = 0;
	//int pointSum = 100;
	Point apoint;
	apoint.x = x0;
	apoint.y = y0;
	double a;

	for (int j = 0; j < lineSum; j++)
	{
		Line aline;
		a = sqrt(ratio) * b;
		for (int i = 0; i < pointSum; i++)
		{
			apoint.x = a * cos(angle);
			//apoint.y = b * sin(angle) + b  ;
			apoint.y = b * sin(angle) + b + (2000 / b) - 85;
			//apoint.y = b * sin(angle) + b +  - 85;

			aline.points.push_back(apoint);
			angle += 2 * PI / pointSum;
		}
		lines.push_back(aline);
		if (j < 5)
			b *= density;
		else
			b *= 1.5;

	}

	return lines;
}

vector<Line> getOval3(double x0, double y0, double ratio, double b, int lineSum, int pointSum, double density)
{
	vector<Line> lines;
	double angle = 0;
	//int pointSum = 100;
	Point apoint;
	apoint.x = x0;
	apoint.y = y0;
	double a;

	for (int j = 0; j < lineSum; j++)
	{
		Line aline;
		a = sqrt(ratio)* b;
		for (int i = 0; i < pointSum; i++)
		{
			apoint.x = a * cos(angle);
			//apoint.y = b * sin(angle) + b  ;
			apoint.y = b * sin(angle)  + 135;
			//apoint.y = b * sin(angle) + b +  - 85;

			aline.points.push_back(apoint);
			angle += 2 * PI / pointSum;
		}
		lines.push_back(aline);
		b += 10;
		ratio *= 1.3;
	}

	return lines;
}



double getCompDirectionTop(double xCenter, double yCenter, double angle, double Kuan, double Gao, double x0, double y0)
{
	Poly n;
	Poly s;
	n.x = xCenter + cos(angle)*Kuan;
	n.y = yCenter + sin(angle) * Kuan;
	n.isZheng = true;
	s.x = xCenter - cos(angle) * Kuan;
	s.y = yCenter - sin(angle) * Kuan;
	s.isZheng = false;
	double distanceToN = sqrt(pow(x0 - n.x,2) + pow(y0 - n.y,2));
	double distanceToS = sqrt(pow(x0 - s.x, 2) + pow(y0 - s.y, 2));
	double ex = (x0 - n.x) / pow(distanceToN, 3)+ (  s.x-x0) / pow(distanceToS, 3);
	double ey = (y0 - n.y) / pow(distanceToN, 3) + (s.y - y0) / pow(distanceToS, 3);
	double e=  sqrt(pow(ex, 2) + pow(ey, 2));
	//double xNext = ex / e+y0;
	//double yNext = ey / e + y0;
	double directionAngle = atan2(ey, ex);
	return directionAngle;

}

double getCompDirectionBotton(double Xcenter,double yCenter,double angleOfMag,double x0, double y0, double ratio)
{
	//计算该点其x方向距离中心的距离和y方向距离其中心的距离
	x0 =x0- Xcenter;
	y0 =y0- yCenter;
	//计算长轴（或者短轴
	bool mirror=false;
	if (y0 < 0)
	{
		y0 = -y0;
		mirror = true;
	}

	double b = (x0 * x0 + ratio * y0 * y0) / (2 * ratio * y0);
	double hx=0, hy=0;
	//切线方形，并归一化
	double lenth = sqrt(ratio * ratio * (y0 - b) * (y0 - b)+(x0*x0));
	hx =(-ratio*(y0-b))/ lenth;
	hy  = x0/lenth;
	double angle = asin(hy);
	
	if (hx < 0)
		angle = PI - angle;//此时的angle为不考虑蹄形磁铁的倾斜的角度
	if (mirror)
		angle = -angle;
	return angle+ angleOfMag;//加上倾斜的角度即为改点的切线角度
}
double getCompDirection(double xCenter, double yCenter, double angleOfMag, double Kuan, double Gao, double x0, double y0, double oval_ratio)
{
	bool pointInTheTop;
	//判断点在磁铁的哪一边
	{
		//移动该点，使其相当于处于以磁铁中心为原点的坐标系中
		double x1 = x0 - xCenter;
		double y1 = y0 - yCenter;
		//该点与x轴的夹角
		double angle = atan2(y1, x1);
		//考虑磁铁旋转后，该点与磁铁中心线的夹角也改变
		angle -= angleOfMag;
		//如果夹角+-PI，那么是在线上,小于PI在上面，大于PI在下面
		if (angle <= 0 || angle == -PI || angle == PI)
		{
			pointInTheTop = true;
		}
		else
		{
			pointInTheTop = false;
		}
	}

	double resultAngle;

	if (pointInTheTop)
	{
		resultAngle= getCompDirectionTop(xCenter, yCenter, angleOfMag, Kuan, Gao, x0, y0);
	}
	else
	{
		resultAngle = getCompDirectionBotton(xCenter, yCenter, angleOfMag, x0, y0, oval_ratio);
	}

	return resultAngle;

}

void angleTest(double angle, double x0, double y0)
{
	fillcircle(x0, y0, 5);
	double nextX, nextY;
	nextX = x0 + 100 * cos(angle);
	nextY = y0 + 100 * sin(angle);
	line(x0, y0, nextX, nextY);
}

int main()
{

	initgraph(W, L);								//初始化屏幕
	setbkcolor(WHITE);							//设置背景色
	cleardevice();								//清除屏幕内容
	setorigin(400, 400);							//重新设置原点位置
	setlinecolor(BLACK);						//设置线的颜色为白色

	setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 2);		//设置线为虚线，端点为平坦的
	line(0, -400, 0, 400);							//y轴
	setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 2);	//设置线为实线，端点为平坦的
	line(-400, 0, 400, 0);							//x轴
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 2);	//设置线为实线，端点为平坦的


		//{
//	double r = 15;
//		circle(p1.x, p1.y, r);							//画半径为15的圆，把这个圆当做正电荷
//	setfillcolor(RED);							//设置填充颜色为红色
//	fillcircle(p1.x, p1.y, r);						//填充正电荷
//
//	circle(n1.x, n1.y, r);							//画半径为15的圆，把这个圆当做负电荷
//	setfillcolor(BLUE);							//设置填充颜色为蓝色
//	fillcircle(n1.x, n1.y, r);						//填充负电荷
////}
//
//	circle(p2.x, p2.y, r);							//画半径为15的圆，把这个圆当做正电荷
//	setfillcolor(RGB(250, 128, 114));							//设置填充颜色为红色
//	fillcircle(p2.x, p2.y, r);						//填充正电荷
//
//	circle(n2.x, n2.y, r);							//画半径为15的圆，把这个圆当做负电荷
//	setfillcolor(RGB(99, 184, 255));							//设置填充颜色为蓝色
//	fillcircle(n2.x, n2.y, r);						//填充负电荷


	ofstream output;
	output.open("number.txt");

	{
	

		
		

			//part1
		{
			//{
			//	int lineSum = 0;
			//	vector<Line> lines;

			//	lines = getOval(0, 0, 0.8, 40, 10, 1000, 1.5);//double x0, double y0, double ratio, double b, int lineSum,int pointSum,double density

			//	lineSum = lines.size();
			//	for (int j = 0; j < lineSum; j++) {
			//		int pointSum = lines.at(j).points.size();
			//		for (int i = 0; i < pointSum - 1; i++) {
			//			if (lines.at(j).points.at(i).x<60 && lines.at(j).points.at(i).x>-60 && lines.at(j).points.at(i).y<100 && lines.at(j).points.at(i).y>-100)
			//				//line(lines.at(j).points.at(i).x, lines.at(j).points.at(i).y-100, lines.at(j).points.at(i + 1).x, lines.at(j).points.at(i + 1).y - 100);
			//				continue;
			//			else
			//				line(lines.at(j).points.at(i).x, lines.at(j).points.at(i).y, lines.at(j).points.at(i + 1).x, lines.at(j).points.at(i + 1).y);

			//		}
			//		line(lines.at(j).points.at(0).x, lines.at(j).points.at(pointSum - 1).y, lines.at(j).points.at(pointSum - 1).x, lines.at(j).points.at(0).y);
			//	}

			//	vector<Line> linesOtherSide;
			//	linesOtherSide = getOval(0, 0, 0.8, 40, 12, 1000, 1.2);

			//	lineSum = linesOtherSide.size();
			//	for (int j = 0; j < lineSum; j++) {
			//		int pointSum = linesOtherSide.at(j).points.size();
			//		for (int i = 0; i < pointSum - 1; i++) {
			//			if (linesOtherSide.at(j).points.at(i).x<60 && linesOtherSide.at(j).points.at(i).x>-60 && linesOtherSide.at(j).points.at(i).y<100 && linesOtherSide.at(j).points.at(i).y>-100)
			//				continue;
			//			//line(linesOtherSide.at(j).points.at(i).x, linesOtherSide.at(j).points.at(i).y, linesOtherSide.at(j).points.at(i + 1).x, linesOtherSide.at(j).points.at(i + 1).y);
			//			line(linesOtherSide.at(j).points.at(i).x, -linesOtherSide.at(j).points.at(i).y, linesOtherSide.at(j).points.at(i + 1).x, -linesOtherSide.at(j).points.at(i + 1).y);

			//		}
			//		line(linesOtherSide.at(j).points.at(0).x, -linesOtherSide.at(j).points.at(pointSum - 1).y, linesOtherSide.at(j).points.at(pointSum - 1).x, -linesOtherSide.at(j).points.at(0).y);
			//	}


			//	//lineSum = polys.at(0).lines.size();
			//	//for (int i = 0; i < lineSum; i++)
			//	//{
			//	//	int pointSize = polys.at(0).lines.at(i).points.size();
			//	//	for (int j = 0; j < pointSize-1; j++)
			//	//	{
			//	//		line(polys.at(0).lines.at(i).points.at(j).x, -polys.at(0).lines.at(i).points.at(j).y, polys.at(0).lines.at(i).points.at(j + 1).x, -polys.at(0).lines.at(i).points.at(j + 1).y);
			//	//		line(-polys.at(0).lines.at(i).points.at(j).x, -polys.at(0).lines.at(i).points.at(j).y, -polys.at(0).lines.at(i).points.at(j + 1).x, -polys.at(0).lines.at(i).points.at(j + 1).y);

			//	//	}
			//	//}


			//	//vector<Line> lineCenter;
			//	//lineCenter = getOval(0, 0, 10, 40, 5, 100, 1);//double x0, double y0, double ratio, double b, int lineSum,int pointSum,double density

			//	//lineSum = lineCenter.size();
			//	//for (int j = 0; j < lineSum; j++) {
			//	//	int pointSum = lineCenter.at(j).points.size();
			//	//	for (int i = 0; i < pointSum - 1; i++) {

			//	//		line(lineCenter.at(j).points.at(i).x, -lineCenter.at(j).points.at(i).y, lineCenter.at(j).points.at(i + 1).x, -lineCenter.at(j).points.at(i + 1).y);

			//	//	}
			//	//	line(lineCenter.at(j).points.at(0).x, -lineCenter.at(j).points.at(pointSum - 1).y, lineCenter.at(j).points.at(pointSum - 1).x, -lineCenter.at(j).points.at(0).y);
			//	//}



			//	//circle(0,100,60);							//画半径为15的圆，把这个圆当做负电荷
			//	setfillcolor(RGB(99, 184, 255));							//设置填充颜色为蓝色
			//	fillcircle(0, 40, 60);						//填充负电荷

			//	setfillcolor(WHITE);							//设置填充颜色为蓝色
			//	fillcircle(0, 40, 40);


			//	rectangle(60, 40, -60, -100);
			//	setfillcolor(RGB(99, 184, 255));							//设置填充颜色为蓝色
			//	fillrectangle(60, 40, -60, -100);

			//	rectangle(40, 40, -40, -100);
			//	setfillcolor(WHITE);							//设置填充颜色为蓝色
			//	fillrectangle(40, 40, -40, -100);
			//}
		}
			
			//part 2
		{
			{
				vector<Poly> polys;
				Poly n, s;
				n.isZheng = true;
				n.x = -45;
				n.y = 85;
				s.isZheng = false;
				s.x = 45;
				s.y = 85;
				polys.push_back(n);
				polys.push_back(s);
				polys = calculateLines(polys, 40,0,20);


		

				int lineSum = 0;




				vector<Line> lines;

				lines = getOval2(0, 0, 0.6, 80, 10, 1000, 1.5);//double x0, double y0, double ratio, double b, int lineSum,int pointSum,double density

				lineSum = lines.size();
				for (int j = 0; j < lineSum; j++) {
					int pointSum = lines.at(j).points.size();
					for (int i = 0; i < pointSum - 1; i++) {
						if (lines.at(j).points.at(i).x<60 && lines.at(j).points.at(i).x>-60 && lines.at(j).points.at(i).y<100 && lines.at(j).points.at(i).y>-100)
							//line(lines.at(j).points.at(i).x, lines.at(j).points.at(i).y-100, lines.at(j).points.at(i + 1).x, lines.at(j).points.at(i + 1).y - 100);
							continue;
						else
							line(lines.at(j).points.at(i).x, lines.at(j).points.at(i).y, lines.at(j).points.at(i + 1).x, lines.at(j).points.at(i + 1).y);

					}
					line(lines.at(j).points.at(0).x, lines.at(j).points.at(pointSum - 1).y, lines.at(j).points.at(pointSum - 1).x, lines.at(j).points.at(0).y);
				}
				
				{
					//显示效果最好的方法，但是不知道该怎么计算切线
					// 				polys = calculateLines(polys, 40);
				//lineSum = polys.at(0).lines.size();
				//for (int i = 0; i < lineSum; i++)
				//{
				//	int pointSize = polys.at(0).lines.at(i).points.size();
				//	for (int j = 0; j < pointSize - 1; j++)
				//	{
				//		if (i < lineSum / 2)
				//		{
				//			line(polys.at(0).lines.at(i).points.at(j).x, -polys.at(0).lines.at(i).points.at(j).y, polys.at(0).lines.at(i).points.at(j + 1).x, -polys.at(0).lines.at(i).points.at(j + 1).y);
				//			line(-polys.at(0).lines.at(i).points.at(j).x, -polys.at(0).lines.at(i).points.at(j).y, -polys.at(0).lines.at(i).points.at(j + 1).x, -polys.at(0).lines.at(i).points.at(j + 1).y);
				//		}
				//		if (i > lineSum / 2 && i < lineSum / 4 * 3)
				//		{
				//			line(polys.at(0).lines.at(i).points.at(j).x, -polys.at(0).lines.at(i).points.at(j).y+(i-20)*10, polys.at(0).lines.at(i).points.at(j + 1).x, -polys.at(0).lines.at(i).points.at(j + 1).y + (i - 20) * 10);
				//			line(-polys.at(0).lines.at(i).points.at(j).x, -polys.at(0).lines.at(i).points.at(j).y + (i - 20) * 10, -polys.at(0).lines.at(i).points.at(j + 1).x, -polys.at(0).lines.at(i).points.at(j + 1).y + (i - 20) * 10);
				//		}
				//		if (i > lineSum / 4 * 3)
				//		{
				//			line(polys.at(0).lines.at(i).points.at(j).x, -polys.at(0).lines.at(i).points.at(j).y + (lineSum / 4 * 3 - i) * 10+100, polys.at(0).lines.at(i).points.at(j + 1).x, -polys.at(0).lines.at(i).points.at(j + 1).y + (lineSum / 4 * 3 - i) * 10 + 100);
				//			line(-polys.at(0).lines.at(i).points.at(j).x, -polys.at(0).lines.at(i).points.at(j).y + (lineSum / 4 * 3 - i) * 10 + 100, -polys.at(0).lines.at(i).points.at(j + 1).x, -polys.at(0).lines.at(i).points.at(j + 1).y + (lineSum / 4 * 3 - i) * 10 + 100);
				//		}
				//	}
				//}
				}
				

				lineSum = polys.at(0).lines.size();
				for (int i = 0; i < lineSum; i++)
				{
					int pointSize = polys.at(0).lines.at(i).points.size();
					for (int j = 0; j < pointSize - 1; j++)
					{
						line(polys.at(0).lines.at(i).points.at(j).x, -polys.at(0).lines.at(i).points.at(j).y, polys.at(0).lines.at(i).points.at(j + 1).x, -polys.at(0).lines.at(i).points.at(j + 1).y);
						line(-polys.at(0).lines.at(i).points.at(j).x, -polys.at(0).lines.at(i).points.at(j).y, -polys.at(0).lines.at(i).points.at(j + 1).x, -polys.at(0).lines.at(i).points.at(j + 1).y);

					}
				}

				
				angleTest(getCompDirectionTop(0,-85,0,60,100,100,-300), 100, -300);
				angleTest(getCompDirection(0, -85, 0, 60, 100, 100, -300, 0.6), 100, -300);
				//angleTest(getCompDirectionBotton(0, -85, 0, 200, 300,0.6), 200, 300);
				//angleTest(getCompDirection(0, -85, 0, 60, 100, 200,  300, 0.6), 200, 300);


					setfillcolor(RGB(99, 184, 255));							//设置填充颜色为蓝色
				fillcircle(0, 40, 60);						//填充负电荷


				rectangle(60, 40, -60, -100);
				setfillcolor(RGB(99, 184, 255));							//设置填充颜色为蓝色
				fillrectangle(60, 40, -60, -100);




				setfillcolor(WHITE);							//设置填充颜色为蓝色
				fillcircle(0, 40, 40);



				rectangle(40, 40, -40, -100);
				setfillcolor(WHITE);							//设置填充颜色为蓝色
				fillrectangle(40, 40, -40, -100);
			}
		}
	}






	


	output.close();
	system("pause");
}

#endif