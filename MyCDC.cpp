#include "stdafx.h"
#include "MyCDC.h"


MyCDC::MyCDC() {
	c = RGB(100, 100, 100);
}


MyCDC::~MyCDC() {
}

//底层实现
void MyCDC::drawLineDDA(int x1, int y1, int x2, int y2) {
	int dx, dy, eps1;
	float x, y, xi, yi;
	dx = x2 - x1;
	dy = y2 - y1;
	x = (float)x1;
	y = (float)y1;
	if (abs(dx) > abs(dy)) {
		eps1 = abs(dx);
	}
	else {
		eps1 = abs(dy);
	}
	xi = float(dx) / float(eps1);
	yi = float(dy) / float(eps1);
	for (int k = 0; k <= eps1; k++) {
		SetPixel(x, y, c);
		x += xi;
		y += yi;
	}
}

void MyCDC::drawLineMP(int x1, int y1, int x2, int y2) {
	int x, y, dx, dy, d, d1, d2;
	dx = x2 - x1;
	dy = y1 - y2;
	d = 2 * dy + dx;
	d1 = 2 * dy;
	d2 = 2 * (dx + dy);
	for (x = x1, y = y1; x < x2; x++) {
		if (d < 0) {
			y++;
			d += d2;
		}
		else {
			d += d1;
		}
		SetPixel(x, y, c);
	}
}

void MyCDC::drawCircleDDA(int xc, int yc, int r) {
	int x, y;
	const double PI = 3.1415926;
	double da, rad;
	da = 1.0 / (r + 1);
	cout << da << endl;
	rad = 2 * PI;
	int steps = rad / da;
	x = r*cos(0);
	y = r*sin(0);
	for (double i = 0; i <= steps; i++) {
		SetPixel(x + xc, y + yc, c);
		x = r*cos(rad*i / steps);
		y = r*sin(rad*i / steps);
	}
}

void MyCDC::drawCircleMP(int cx, int cy, int r) {
	float d;
	int x = 0, y = r;
	d = 1.25 - r;
	while (x < y) {
		draw8Points(cx, cy, x, y);
		if (d < 0) {
			d += 2 * x + 3;
			x++;
		}
		else {
			d += 2 * (x - y) + 5;
			x++;
			y--;
		}
	}
}

void MyCDC::drawCircleBresenham(int cx, int cy, int r) {
	int x, y, delta, d1, d2, dir;
	x = 0;
	y = r;
	delta = 2 * (1 - r);
	while (y >= 0) {
		draw4Points(cx, cy, x, y);
		if (delta < 0) {
			d1 = 2 * (delta + y) - 1;
			if (d1 <= 0)dir = 1;
			else dir = 2;
		}
		else if (delta > 0) {
			d2 = 2 * (delta - x) - 1;
			if (d2 <= 0)dir = 2;
			else dir = 3;
		}
		else {
			dir = 2;
		}
		switch (dir) {
			case 1:
				x++;
				delta += 2 * x + 1;
				break;
			case 2:
				x++; y--;
				delta += 2 * (x - y) + 1;
				break;
			case 3:
				y--;
				delta += -2 * y + 1;
				break;
			default:
				break;
		}
	}
}

void MyCDC::drawEllipseMP(int left, int top, int right, int bottom) {
	/*float d;
	int cx = (left + right) / 2;
	int cy = (top + bottom) / 2;
	int a = abs(left - right) / 2;
	int b = abs(top - bottom) / 2;
	int x = 0, y = b;
	d = toFixed(b*b + a*(-b + 0.25));
	while (b*b*(x + 1) < a*a*(y - 0.5)) {
		draw4Points(cx, cy, x, y);
		if (d < 0) {
			d += b*b*(2 * x + 3);
		}
		else {
			d += b*b*(2 * x + 3) + a*a*(-2 * y + 2);
			y--;
		}
		x++;
	}
	d = toFixed(b*b*(x + 0.5)*(x + 0.5) + a*a*(y - 1)*(y - 1) - a*a*b*b);
	while (y >0 ) {
		draw4Points(cx,cy, x, y);
		if (d < 0) {
			d = b*b*(2 * x + 2) + a*a*(-2 * y + 3);
			x++; 
		}
		else {
			d += a*a*(-2 * y + 3);
		}
		y--;
	}*/
}

void MyCDC::drawEllipseMidPoint(int xCenter, int yCenter, int a, int b) {
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


void MyCDC::setColor(COLORREF c) {
	this->c = c;
}

void MyCDC::setColor(uc r, uc g, uc b) {
	c = RGB(r, g, b);
	setColor(RGB(r, g, b));
}

void MyCDC::draw8Points(int cx, int cy, int x, int y) {
	SetPixel(cx + x, cy + y, c);
	SetPixel(cx - x, cy + y, c);
	SetPixel(cx + x, cy - y, c);
	SetPixel(cx - x, cy - y, c);
	SetPixel(cx + y, cy + x, c);
	SetPixel(cx + y, cy - x, c);
	SetPixel(cx - y, cy + x, c);
	SetPixel(cx - y, cy - x, c);
}

void MyCDC::draw4Points(int cx, int cy, int x, int y) {
	SetPixel(cx + x, cy + y, c);
	SetPixel(cx - x, cy + y, c);
	SetPixel(cx + x, cy - y, c);
	SetPixel(cx - x, cy - y, c);
}

int MyCDC::toFixed(double number) {
	return (int)(number+0.5);
}
