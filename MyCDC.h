#pragma once
#include "afxwin.h"
#include <math.h>
typedef unsigned char uc;
class MyCDC :public CDC{
public:
	MyCDC();
	~MyCDC();
	
	void drawLineDDA(int x1, int y1, int x2, int y2);
	void drawLineMP(int x1, int y1, int x2, int y2);

	void drawCircleDDA(int x, int y, int r);
	void drawCircleMP(int x,int y,int r);
	void drawCircleBresenham(int x, int y, int r);

	void drawEllipseMP(int left, int top, int right, int bottom);
	void drawEllipseMidPoint(int xCenter, int yCenter, int a, int b);

	void setColor(COLORREF c);
	void setColor(uc r,uc g,uc b);

	

	

private:

	void draw8Points(int cx, int cy, int x, int y);
	void draw4Points(int cx, int cy, int x, int y);
	int toFixed(double number);
private:
	COLORREF c;
};