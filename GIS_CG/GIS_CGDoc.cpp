
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
