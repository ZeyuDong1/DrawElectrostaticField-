// 静电场.cpp : 定义控制台应用程序的入口点。
//

#include "main.h"

#ifdef D1

#include "graphics.h"
#include "math.h"
#define PI 3.1415926535
#define W 800			//宏定义屏幕宽
#define L 800			//宏定义屏幕长
#define LINE 20			//设置划线数量
#define NUM 30000		//迭代次数

int main()
{
	double r1, r2, Ex, Ey, x, y, x0, y0, X = 0.0, E;		//设置变量
	initgraph(W, L);								//初始化屏幕
	setbkcolor(WHITE);							//设置背景色
	cleardevice();								//清除屏幕内容
	setorigin(400, 400);							//重新设置原点位置
	setlinecolor(BLACK);						//设置线的颜色为白色

	setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 2);		//设置线为虚线，端点为平坦的
	line(0, -400, 0, 400);							//y轴
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 2);	//设置线为实线，端点为平坦的
	line(-400, 0, 400, 0);							//x轴

	circle(-200, 0, 15);							//画半径为15的圆，把这个圆当做正电荷
	setfillcolor(RED);							//设置填充颜色为红色
	fillcircle(-200, 0, 15);						//填充正电荷

	circle(200, 0, 15);							//画半径为15的圆，把这个圆当做负电荷
	setfillcolor(BLUE);							//设置填充颜色为蓝色
	fillcircle(200, 0, 15);						//填充负电荷

	line(-208, 0, -192, 0);
	line(-200, -8, -200, 8);						//画正号
	line(192, 0, 208, 0);							//画负号

	for (int i = 0; i < LINE; i++)						//设置要画线的循环条件
	{
		x = -200 + 15 * cos(X);						//设置好出划画线点的出发位置
		y = 0 + 15 * sin(X);							//以半径为15的圆线圈为出发点
		for (int j = 0; j < NUM; j++)					//迭代次数
		{
			r1 = sqrt(pow(x - 200, 2) + pow(y - 0, 2));   //计算负(正???)电荷到p点位置的半径	
			r2 = sqrt(pow(x + 200, 2) + pow(y - 0, 2));   //计算正(负???)电荷到p点位置的半径
			Ex = (200 - x) / pow(r1, 3) + (x + 200) / pow(r2, 3);//计算x轴方向的场强
			Ey = (0 - y) / pow(r1, 3) + (y - 0) / pow(r2, 3);	//计算y轴方向的场强
			E = sqrt(pow(Ex, 2) + pow(Ey, 2));		//计算总场强
			x0 = x + Ex / E;							//计算更新之后p点的位置
			y0 = y + Ey / E;							//计算更新之后p点的位置
			line(x, y, x0, y0);					//连接两点
			x = x0;								//更新x坐标
			y = y0;								//更新y坐标
			if (pow(x - 200, 2) + pow(y - 0, 2) <= 15 * 15)//防止画的线挡住我画的负电荷
				break;
		}
		X += 2 * PI / LINE;//改变画线点的位置
	}
	system("pause");
}

#endif