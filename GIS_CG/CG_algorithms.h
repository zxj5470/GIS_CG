#pragma once
/**
* @Author:郑泓
*/
#include "stdc++.h"
#include <Windows.h>
#include <afxres.h>//GetTickCount()

using namespace std;


struct Point {
	double x, y;
};

/**
* 向量法计算
* @param x,y 点C
* @param xa,ya 点A坐标
* @param xb,yb 点B坐标
* @return
*/
double distanceVector(double x, double y, double xa, double ya, double xb, double yb) {
	//A(xa,ya) B(xb,yb) C(x,y);
	//AC(x-xa,y-ya)
	//AB(xb-xa,yb-ya);
	//BC(x-xb,y-yb);
	double ACAB = (x - xa) * (xb - xa) + (y - ya) * (yb - ya);
	if (ACAB <= 0)return sqrt((x - xa) * (x - xa) + (y - ya) * (y - ya));//return |AC|
	else {
		double BABC = (xa - xb) * (x - xb) + (ya - yb) * (y - yb);
		if (BABC <= 0)return sqrt((x - xa) * (x - xa) + (y - ya) * (y - ya));//return |BC|
		else {
			double AB2 = (xb - xa) * (xb - xa) + (yb - ya) * (yb - ya);
			double px = xa + (xb - xa) * ACAB / AB2;
			double py = ya + (yb - ya) * ACAB / AB2;
			return sqrt((x - px) * (x - px) + (y - py) * (y - py));//return |PC|
		}
	}
}

double distanceVector(Point C, Point A, Point B) {
	return distanceVector(C.x, C.y, A.x, A.y, B.x, B.y);
}

double distanceHeron(double x, double y, double xa, double ya, double xb, double yb) {
	double ACAB = (x - xa) * (xb - xa) + (y - ya) * (yb - ya);
	if (ACAB <= 0)return sqrt((x - xa) * (x - xa) + (y - ya) * (y - ya));//A为钝角 return |AC|
	else {
		double BABC = (xa - xb) * (x - xb) + (ya - yb) * (y - yb);
		if (BABC <= 0)return sqrt((x - xa) * (x - xa) + (y - ya) * (y - ya));//B为钝角return |BC|
		else {
			//different from belows
			double AB = sqrt((xb - xa) * (xb - xa) + (yb - ya) * (yb - ya));
			double AC = sqrt((x - xa) * (x - xa) + (y - ya) * (y - ya));
			double BC = sqrt((xb - x) * (xb - x) + (yb - y) * (yb - y));
			double p = (AB + AC + BC) / 2;
			double S = sqrt(p * (p - AB) * (p - AC) * (p - BC));
			return 2 * S / AB;
		}
	}
}

double distanceHeron(Point C, Point A, Point B) {
	return distanceHeron(C.x, C.y, A.x, A.y, B.x, B.y);
}
void test(double x, double y, double x1, double y1, double x2, double y2) {
	DWORD k = ::GetTickCount(); //获取毫秒数
	int counts = 1000000;
	for (int i = 0; i < counts; i++) {
		distanceVector(x, y, x1, y1, x2, y2);
	}
	DWORD k1 = ::GetTickCount();
	cout << k1 - k << endl;
	k = ::GetTickCount();
	for (int i = 0; i < counts; i++) {
		distanceHeron(x, y, x1, y1, x2, y2);
	}
	k1 = ::GetTickCount();
	cout << k1 - k << endl;
}