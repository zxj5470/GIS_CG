
// GIS_CGDoc.cpp : CGIS_CGDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GIS_CG.h"
#endif

#include "GIS_CGDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGIS_CGDoc

IMPLEMENT_DYNCREATE(CGIS_CGDoc, CDocument)

BEGIN_MESSAGE_MAP(CGIS_CGDoc, CDocument)
END_MESSAGE_MAP()


// CGIS_CGDoc 构造/析构

CGIS_CGDoc::CGIS_CGDoc() {
	// TODO: 在此添加一次性构造代码

}

CGIS_CGDoc::~CGIS_CGDoc() {
}

void CGIS_CGDoc::DDALine(CClientDC * DCPoint) {
	int x1 = group[0].x;
	int x2 = group[1].x;
	int y1 = group[0].y;
	int y2 = group[1].y;
	int x, y, dx, dy, d, d1, d2;
	dx = x2 - x1;
	if (x2 < x1) {
		x1 = x1 + x2;
		x2 = x1 - x2;
		x1 = x1 - x2;
	}
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
		DCPoint->SetPixel(x, y, RGB(186, 233, 0));
	}
}

void CGIS_CGDoc::SeedFill(CClientDC * pDC, CPoint seedpoint) {
	int savex, xleft, xright, pflag, x, y, num; CPoint stack_ptr[200];//堆栈 
	int tx;
	pDC->SetROP2(R2_COPYPEN); //绘图方法为直接画 
	num = 0; //num 为堆栈中的种子数 
	stack_ptr[num++] = seedpoint;
	while (num>0) {
		x = stack_ptr[--num].x; y = stack_ptr[num].y;
		pDC->SetPixel(x, y, RGB(0, 0, 0));
		savex = x;     x++;
		while (pDC->GetPixel(x, y) != RGB(0, 0, 0))//向右填充，直到边界
		{
			x++;
		};
		tx = savex;
		while (tx != x) {
			pDC->SetPixel(tx++, y, RGB(0, 0, 0));//向右填充，直到边界
		}

		xright = x - 1;   x = savex - 1;
		while (pDC->GetPixel(x, y) != RGB(0, 0, 0))//向左填充，直到边界
		{
			pDC->SetPixel(x--, y, RGB(0, 0, 0));
		};
		xleft = x + 1;    x = xleft; y++;//在扫描线下一行搜索未填充区域
		pflag = 1;
		while (x<xright) {
			if (pDC->GetPixel(x, y) != RGB(0, 0, 0) && pflag == 1) {//边界后的第一个未填充区域像素 
				stack_ptr[num].x = x; stack_ptr[num++].y = y; x++;
			}
			if (pDC->GetPixel(x, y) == RGB(0, 0, 0))
				pflag = 1;//pflag=1 表示填充区域或边界 
			else
				pflag = 0;//pflag=0 表示未填充区域 
			x++;
		}
		x = xleft; y -= 2;	pflag = 1;//在扫描线上一行搜索未填充区域
		while (x<xright) {
			if (pDC->GetPixel(x, y) != RGB(0, 0, 0) && pflag == 1) {
				stack_ptr[num].x = x; stack_ptr[num++].y = y; x++;
			}
			if (pDC->GetPixel(x, y) == RGB(0, 0, 0))
				pflag = 1;
			else
				pflag = 0;
			x++;
		}
	}


}

void CGIS_CGDoc::EdgeFill(CClientDC * pDC) {
	int i, xr, x1, y1, x2, y2, y;
	float m, x;
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 254, 254));//确定填充颜色，由该颜色与背景 
												 //色异或混合而成 
	pDC->SetROP2(R2_XORPEN); //绘图方法为异或 
	CPen *pOldPen = pDC->SelectObject(&pen);
	xr = 0;
	for (i = 0; i<PointNum; i++)//找出边界盒右边界参数
	{
		if (xr<group[i].x)xr = group[i].x;
	}
	for (i = 0; i<PointNum - 1; i++) {
		x1 = group[i].x; x2 = group[i + 1].x;//取一条边
		y1 = group[i].y; y2 = group[i + 1].y;
		if (y1 != y2) {
			if (y1>y2)//确保（x1,y1）为下端点
			{
				y = y1; y1 = y2; y2 = y;
				y = x1; x1 = x2; x2 = y;
			}
			m = (float)(x2 - x1) / (float)(y2 - y1); x = x1;//m为相邻扫描线之间边的 x 增量 
			for (y = y1 + 1; y <= y2; y++) {
				x += m;//确定边缘点 
				pDC->MoveTo((int)x, y);//从边缘点一直画到边界盒右端 
				pDC->LineTo(xr, y);
			}
		}
	}
	pDC->SelectObject(pOldPen);
}

void CGIS_CGDoc::DrawGraph(CClientDC * pDC) {
	int i;
	CPen pen, *pOldPen;
	pDC->SetROP2(R2_COPYPEN);
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); pOldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(group[0]);
	for (i = 1; i<PointNum; i++)
		pDC->LineTo(group[i]);
	pDC->SelectObject(pOldPen);

}

void CGIS_CGDoc::GenerateGraph(CClientDC * pDC) {
	//group[0].x = 100; group[0].y = 100;//图形数据准备 
	//group[1].x = 200; group[1].y = 100;
	//group[2].x = 200; group[2].y = 200;
	//group[3].x = 100; group[3].y = 200;
	//group[4].x = 100; group[4].y = 100;
	//PointNum = 5;
	DrawGraph(pDC);
}

void CGIS_CGDoc::DrawWindow(CClientDC *pDC) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	CPen *pOldPen = pDC->SelectObject(&pen); pDC->SetROP2(R2_COPYPEN);
	pDC->MoveTo(XMIN, YMIN);
	pDC->LineTo(XMAX, YMIN);
	pDC->LineTo(XMAX, YMAX);
	pDC->LineTo(XMIN, YMAX);
	pDC->LineTo(XMIN, YMIN);
	pDC->SelectObject(pOldPen);
}

void CGIS_CGDoc::CohenSutherland(CClientDC * pDC, CPoint p1, CPoint p2) {
	int code1, code2, code, x, y, x1, y1, x2, y2;
	pDC->SetROP2(R2_COPYPEN);
	CPen Pen;
	Pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen *OldPen = pDC->SelectObject(&Pen);
	x1 = p1.x; y1 = p1.y;
	x2 = p2.x; y2 = p2.y;
	code1 = encode(x1, y1);
	code2 = encode(x2, y2);
	while (code1 != 0 || code2 != 0) {
		if ((code1&code2) != 0)return;//完全不可见 
		code = code1;
		if (code1 == 0)code = code2;
		if ((LEFT&code) != 0)//求线段与窗口左边的交点
		{
			x = XMIN;
			y = y1 + (y2 - y1)*(x - x1) / (x2 - x1);
		}
		else if ((RIGHT&code) != 0) //求线段与窗口右边的交点
		{
			x = XMAX;
			y = y1 + (y2 - y1)*(x - x1) / (x2 - x1);
		}
		else if ((BOTTOM&code) != 0) //求线段与窗口底边的交点
		{
			y = YMIN;
			x = x1 + (x2 - x1)*(y - y1) / (y2 - y1);
		}
		else if ((TOP&code) != 0) //求线段与窗口顶边的交点 
		{
			y = YMAX;
			x = x1 + (x2 - x1)*(y - y1) / (y2 - y1);
		}
		if (code == code1) {
			x1 = x; y1 = y; code1 = encode(x, y);
		}
		else {
			x2 = x; y2 = y; code2 = encode(x, y);
		}
	}
	pDC->MoveTo(x1, y1);
	pDC->LineTo(x2, y2);
	pDC->SelectObject(OldPen);

}

void CGIS_CGDoc::PolygonCut(CClientDC * pDC) {
	CPen pen;
	pen.CreatePen(0, 2, RGB(255, 0, 0));
	CPen *OldPen = pDC->SelectObject(&pen); pDC->SetROP2(R2_COPYPEN);
	EdgeClipping(0);	//用第一条窗口边进行裁剪
	EdgeClipping(1);	//用第二条窗口边进行裁剪
	EdgeClipping(2);	//用第三条窗口边进行裁剪
	EdgeClipping(3);	//用第四条窗口边进行裁剪

	pDC->MoveTo(group[0]); //    绘制裁剪多边形 
	for(int i=1;i<=PointNum;i++) 
		pDC->LineTo(group[i]);
	pDC->SelectObject(OldPen);

}

void CGIS_CGDoc::EdgeClipping(int linecode) {
	float x, y;
	int n, i, number1;
	CPoint q[200];
	number1 = 0;
	if (linecode == 0)// x=XMIN 
	{
		for (n = 0; n<PointNum; n++) {
			if (group[n].x<XMIN&&group[n + 1].x<XMIN)//外外，不输出 
			{
			}
			if (group[n].x >= XMIN&&group[n + 1].x >= XMIN)//里里，输出后点 
			{
				q[number1++] = group[n + 1];
			}
			if (group[n].x >= XMIN&&group[n + 1].x<XMIN)//里外，输出交点 
			{
				y = group[n].y + (float)(group[n + 1].y - group[n].y) /
					(float)(group[n + 1].x - group[n].x)*(float)(XMIN - group[n].x); q[number1].x = XMIN;
				q[number1++].y = (int)y;
			}
			if (group[n].x<XMIN&&group[n + 1].x >= XMIN)//外里，输出交点、后点 
			{
				y = group[n].y + (float)(group[n + 1].y - group[n].y) /
					(float)(group[n + 1].x - group[n].x)*(float)(XMIN - group[n].x); q[number1].x = XMIN;
				q[number1++].y = (int)y;
				q[number1++] = group[n + 1];
			}
		}

		for (i = 0; i<number1; i++) {
			group[i] = q[i];
		}
		group[number1] = q[0];
		PointNum = number1; number1 = 0;
	}
	if (linecode == 1)//y=YMAX 
	{
		for (n = 0; n<PointNum; n++) {
			if (group[n].y >= YMAX&&group[n + 1].y >= YMAX)//外外，不输出
			{
			}
			if (group[n].y<YMAX&&group[n + 1].y<YMAX)//里里，输出后点
			{
				q[number1++] = group[n + 1];
			}
			if (group[n].y<YMAX&&group[n + 1].y >= YMAX)//里外，输出交点
			{
				x = group[n].x + (float)(group[n + 1].x - group[n].x) /
					(float)(group[n + 1].y - group[n].y)*(float)(YMAX - group[n].y);
				q[number1].x = (int)x;
				q[number1++].y = YMAX;
			}
			if (group[n].y >= YMAX&&group[n + 1].y<YMAX)//外里，输出交点、后点
			{
				x = group[n].x + (float)(group[n + 1].x - group[n].x) /
					(float)(group[n + 1].y - group[n].y)*(float)(YMAX - group[n].y); q[number1].x = (int)x;
				q[number1++].y = YMAX;
				q[number1++] = group[n + 1];
			}
		}
		for (i = 0; i<number1; i++) {
			group[i] = q[i];
		}
		group[number1] = q[0];
		PointNum = number1; number1 = 0;
	}
	if (linecode == 2)//x=XMAX 
	{
		for (n = 0; n<PointNum; n++) {
			if (group[n].x >= XMAX&&group[n + 1].x >= XMAX)//外外，不输出 
			{
			}
			if (group[n].x<XMAX&&group[n + 1].x<XMAX)//里里，输出后点 
			{
				q[number1++] = group[n + 1];
			}
			if (group[n].x<XMAX&&group[n + 1].x >= XMAX)//里外，输出交点 
			{
				y = group[n].y + (float)(group[n + 1].y - group[n].y) /
					(float)(group[n + 1].x - group[n].x)*(float)(XMAX - group[n].x); q[number1].x = XMAX;
				q[number1++].y = (int)y;
			}
			if (group[n].x >= XMAX&&group[n + 1].x<XMAX)//外里，输出交点、后点 
			{
				y = group[n].y + (float)(group[n + 1].y - group[n].y) /
					(float)(group[n + 1].x - group[n].x)*(float)(XMAX - group[n].x); q[number1].x = XMAX;
				q[number1++].y = (int)y;
				q[number1++] = group[n + 1];
			}
		}
		for (i = 0; i<number1; i++) {
			group[i] = q[i];
		}
		group[number1] = q[0];
		PointNum = number1; number1 = 0;
	}
	if (linecode == 3)// y=YMIN 
	{
		for (int n = 0; n<PointNum; n++) {
			if (group[n].y<YMIN&&group[n + 1].y<YMIN)//外外，不输出 
			{
			}
			if (group[n].y >= YMIN&&group[n + 1].y >= YMIN)//里里，输出后点 
			{
				q[number1++] = group[n + 1];
			}
			if (group[n].y >= YMIN&&group[n + 1].y<YMIN)//里外，输出交点 
			{
				x = group[n].x + (float)(group[n + 1].x - group[n].x) /
					(float)(group[n + 1].y - group[n].y)*(float)(YMIN - group[n].y); q[number1].x = (int)x;
				q[number1++].y = YMIN;
			}
			if (group[n].y<YMIN&&group[n + 1].y >= YMIN)//外里，输出交点、后点 
			{
				x = group[n].x + (float)(group[n + 1].x - group[n].x) /
					(float)(group[n + 1].y - group[n].y)*(float)(YMIN - group[n].y); q[number1].x = (int)x;
				q[number1++].y = YMIN;
				q[number1++] = group[n + 1];
			}
		}
		for (i = 0; i<number1; i++) {
			group[i] = q[i];
		}
		group[number1] = q[0];
		PointNum = number1; number1 = 0;
	}

}

void CGIS_CGDoc::BCircle(CClientDC * DCPoint, CPoint p1, CPoint p2) {
	CRect rc;
	bool a = DCPoint->GetBoundsRect(&rc, 0);
	BCircle(DCPoint, &rc, p1, p2);

}

void CGIS_CGDoc::BCircle(CClientDC * DCPoint, CRect * rc, CPoint p1, CPoint p2) {
	COLORREF m_crColor = RGB(0, 0, 0);
	int r, d, x, y, x0, y0;
	DCPoint->SetROP2(R2_COPYPEN); //绘图方法为直接画 
	r = (int)sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
	x = 0; y = r; d = 3 - 2 * r; x0 = p1.x; y0 = p1.y;
	while (x<y || x == y) {
		if (rc->PtInRect(CPoint(x + x0, y + y0)))	//判断点是否在矩形框内
			DCPoint->SetPixel(x + x0, y + y0, m_crColor);
		if (rc->PtInRect(CPoint(-x + x0, y + y0)))
			DCPoint->SetPixel(-x + x0, y + y0, m_crColor);
		if (rc->PtInRect(CPoint(x + x0, -y + y0)))
			DCPoint->SetPixel(x + x0, -y + y0, m_crColor);
		if (rc->PtInRect(CPoint(-x + x0, -y + y0)))
			DCPoint->SetPixel(-x + x0, -y + y0, m_crColor);
		if (rc->PtInRect(CPoint(y + x0, x + y0)))
			DCPoint->SetPixel(y + x0, x + y0, m_crColor);
		if (rc->PtInRect(CPoint(-y + x0, x + y0)))
			DCPoint->SetPixel(-y + x0, x + y0, m_crColor);
		if (rc->PtInRect(CPoint(y + x0, -x + y0)))
			DCPoint->SetPixel(y + x0, -x + y0, m_crColor);
		if (rc->PtInRect(CPoint(-y + x0, -x + y0)))
			DCPoint->SetPixel(-y + x0, -x + y0, m_crColor);

		x = x + 1;
		if (d<0 || d == 0) {
			d = d + 4 * x + 6;
		}
		else {
			y = y - 1; d = d + 4 * (x - y) + 10;
		}
	};

}

void CGIS_CGDoc::CircleCut(CClientDC * DCPoint) {
	CRect rc(XMIN, YMIN, XMAX, YMAX);
}

BOOL CGIS_CGDoc::OnNewDocument() {
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CGIS_CGDoc 序列化

void CGIS_CGDoc::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		// TODO: 在此添加存储代码
	}
	else {
		// TODO: 在此添加加载代码
	}
}
int CGIS_CGDoc::encode(int x, int y) {
	int c;
	c = 0;
	if (x<XMIN)c = c + LEFT;
	else if (x>XMAX)c = c + RIGHT;
	if (y<YMIN)c = c + BOTTOM;
	else if (y>YMAX)c = c + TOP;
	return c;
}
#ifdef SHARED_HANDLERS

// 缩略图的支持
void CGIS_CGDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds) {
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(254, 254, 254));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CGIS_CGDoc::InitializeSearchContent() {
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CGIS_CGDoc::SetSearchContent(const CString& value) {
	if (value.IsEmpty()) {
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else {
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL) {
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGIS_CGDoc 诊断

#ifdef _DEBUG

void CGIS_CGDoc::AssertValid() const {
	CDocument::AssertValid();
}

void CGIS_CGDoc::Dump(CDumpContext& dc) const {
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGIS_CGDoc 命令
