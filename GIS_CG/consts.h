#pragma once

#define XMIN 100
#define XMAX 400 
#define YMIN 100 
#define YMAX 300 
#define LEFT 1
#define RIGHT 2 
#define BOTTOM 4 
#define TOP 8 

const int DRAW_LINE_DDA_MODE = 100;
const int DRAW_LINE_MP_MODE = 101;
const int DRAW_CIRCLE_DDA_MODE = 102;
const int DRAW_CIRCLE_MP_MODE = 103;
const int DRAW_CIRCLE_BRE_MODE = 104;
const int DRAW_ELLIPSE_MP_MODE = 105;

const int DRAW_MOVE = 11;

const COLORREF ColorBlack = RGB(0, 0, 0); 
const COLORREF ColorWhite = RGB(255, 255, 255);