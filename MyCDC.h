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

	void setColor(COLORREF c);
	void setColor(uc r,uc g,uc b);
	void ellipseMidpoint(int xCenter, int yCenter, int a, int b) {
		int aSQ = a * a;
		int bSQ = b * b;
		int twoRx2 = 2 * aSQ;
		int twoRy2 = 2 * bSQ;
		int p;
		int x = 0;
		int y = b;
		int px = 0;
		int py = twoRx2 * y;
		draw4Points(xCenter, yCenter, x, y);
		p = toFixed(bSQ - (aSQ * b) + (0.25 * aSQ));
		while (px < py) {
			x++;
			px += twoRy2;
			if (p < 0)
				p += bSQ + px;
			else {
				y--;
				py -= twoRx2;
				p += bSQ + px - py;
			}
			draw4Points(xCenter, yCenter, x, y);
		}
		p = toFixed(bSQ * (x + 0.5) * (x + 0.5) + aSQ * (y - 1) * (y - 1) - aSQ * bSQ);
		while (y > 0) {
			y--;
			py -= twoRx2;
			if (p > 0)
				p += aSQ - py;
			else {
				x++;
				px += twoRy2;
				p += aSQ - py + px;
			}
			draw4Points(xCenter, yCenter, x, y);
		}
	}

private:

	void draw8Points(int cx, int cy, int x, int y);
	void draw4Points(int cx, int cy, int x, int y);
	int toFixed(double number);
private:
	COLORREF c;
};