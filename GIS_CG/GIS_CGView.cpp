
// GIS_CGView.cpp : CGIS_CGView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GIS_CG.h"
#endif
#include "consts.h"
#include "GIS_CGDoc.h"
#include "GIS_CGView.h"
#include "MyCDC.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGIS_CGView

IMPLEMENT_DYNCREATE(CGIS_CGView, CView)

BEGIN_MESSAGE_MAP(CGIS_CGView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_FILL, &CGIS_CGView::OnFill)
	ON_WM_MOUSEMOVE()
	//	ON_WM_NCRBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_EDGEFILL, &CGIS_CGView::OnEdgefill)
	ON_COMMAND(ID_DrawLineDDA, &CGIS_CGView::OnDrawlinedda)
	ON_COMMAND(ID_DrawLineMP, &CGIS_CGView::OnDrawlinemp)
	ON_COMMAND(ID_DrawCircleDDA, &CGIS_CGView::OnDrawcircledda)
	ON_COMMAND(ID_DrawCircleMP, &CGIS_CGView::OnDrawcirclemp)
	ON_COMMAND(ID_DrawCircleBre, &CGIS_CGView::OnDrawcirclebre)
	ON_COMMAND(ID_DrawEllipse, &CGIS_CGView::OnDrawellipse)
	ON_COMMAND(ID_CLEAR, &CGIS_CGView::OnClear)
	ON_COMMAND(ID_CLEAR_QUICK, &CGIS_CGView::OnClearQuick)
	ON_COMMAND(ID_Graph_MOVE, &CGIS_CGView::OnGraphMove)
	ON_COMMAND(ID_MUL_CUT, &CGIS_CGView::OnMulCut)
	ON_COMMAND(ID_CUT_POLY, &CGIS_CGView::OnCutPoly)
	ON_COMMAND(ID_CIRCLE_CUT, &CGIS_CGView::OnCircleCut)
END_MESSAGE_MAP()

// CGIS_CGView 构造/析构

CGIS_CGView::CGIS_CGView() {
	// TODO: 在此处添加构造代码
	MenuID = 0;
}


CGIS_CGView::~CGIS_CGView() {
}

BOOL CGIS_CGView::PreCreateWindow(CREATESTRUCT& cs) {
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGIS_CGView 绘制

void CGIS_CGView::OnDraw(CDC* pDC) {
	CGIS_CGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CDC *dc = GetDC();
	MyCDC &g = static_cast<MyCDC&>(*dc);
	////add console to "debug"
	//AllocConsole();                          // 开辟控制台
	//SetConsoleTitle(_T("Debug Title"));      // 设置控制台窗口标题
	//FILE* pf;
	//freopen_s(&pf, "CONOUT$", "w", stdout);


	//g.drawCircleBresenham(100, 100, 30);
	//g.setColor(200, 10, 10);
	//g.drawLineDDA(10, 10, 200, 200);

	//g.setColor(100, 233, 10);
	//g.drawEllipseMP_2(100, 100, 100, 100);
	//
	//g.setColor(200, 100, 10);
	//g.drawEllipseMP_1(100, 100, 300, 250);

	//g.drawEllipseMP_2(245, 123, 50, 30);

	// TODO: 在此处为本机数据添加绘制代码
}


// CGIS_CGView 打印
BOOL CGIS_CGView::OnPreparePrinting(CPrintInfo* pInfo) {
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGIS_CGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGIS_CGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
	// TODO: 添加打印后进行的清理过程
}


// CGIS_CGView 诊断

#ifdef _DEBUG
void CGIS_CGView::AssertValid() const {
	CView::AssertValid();
}

void CGIS_CGView::Dump(CDumpContext& dc) const {
	CView::Dump(dc);
}

CGIS_CGDoc* CGIS_CGView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGIS_CGDoc)));
	return (CGIS_CGDoc*)m_pDocument;
}
#endif //_DEBUG


// CGIS_CGView 消息处理程序


void CGIS_CGView::OnLButtonDown(UINT nFlags, CPoint point) {
	CGIS_CGDoc *pDoc = GetDocument(); //获得文档类指针
	CClientDC ht(this);
	CDC *dc = GetDC();
	MyCDC &g = static_cast<MyCDC&>(*dc);
	g.setColor(0, 0, 0);
	OnPrepareDC(&ht);
	g.SetROP2(R2_COPYPEN);
	// 种子填充:画边界
	if (MenuID == 20) {
		if (PressNum == 0) {
			mPointOrign = point;
			mPointOld = point;
			mPointOld1 = point; //记录第一点 
			PressNum++;
		}
		else {
			g.drawLine2PointDDA(mPointOrign, point);
			mPointOrign = point;
			mPointOld = point;
			PressNum++;
		}

	} // 确定种子点，填充 
	else if (MenuID == 21) {
		pDoc->SeedFill(&ht, point);
		PressNum = 0; MenuID = 20;//设置决定顶点操作方式
	}
	// 边缘填充选顶点 
	else if (MenuID == 22 || MenuID == 25) {
		pDoc->group[PressNum++] = point;
		pDoc->PointNum++;
		mPointOrign = point;
		mPointOld = point;
	}
	else if (MenuID == 24) {
		if (PressNum == 0) {
			mPointOrign = point;
			mPointOld = point;
			PressNum++;
		}
		else {
			pDoc->CohenSutherland(&ht, mPointOrign, point);
			ReleaseCapture();
			PressNum = 0;
		}
	}

	else if (MenuID == DRAW_MOVE) { //  平移 
		g.SetROP2(R2_NOT);
		if (PressNum == 0) {
			PressNum++;
			mPointOrign = point;
			mPointOld = point; //记录第一点 
			g.SetPixel(point.x, point.y, RGB(0, 0, 0));
		}
		else if (PressNum == 1) {	//根据两点间距计算平移量
			for (int i = 0; i < pDoc->PointNum; i++)//根据平移量计算新图形坐标
			{
				pDoc->group[i].x += point.x - mPointOrign.x;
				pDoc->group[i].y += point.y - mPointOrign.y;
			}
			//ht.MoveTo(mPointOrign);//擦除橡皮筋
			//ht.LineTo(point);
			g.drawLine2PointDDA(mPointOrign, mPointOld);
			pDoc->DrawGraph(&ht);//生成新图形 
			PressNum = 0;
		}
	}
	else {
		switch (MenuID) {
			case DRAW_LINE_DDA_MODE:case DRAW_LINE_MP_MODE:
				if (PressNum == 0) {
					mPointOrign = point;
					mPointOld = point;
					mPointOld1 = point; //记录第一点 
					PressNum++;
				}
				else {
					pDoc->group[0] = mPointOrign;
					pDoc->group[1] = point;
					if (MenuID == DRAW_LINE_DDA_MODE)g.drawLine2PointDDA(pDoc->group[0], pDoc->group[1]);
					if (MenuID == DRAW_LINE_MP_MODE)g.drawLine2PointDDA(pDoc->group[0], pDoc->group[1]);
					mPointOrign = point;
					mPointOld = point;
					PressNum = 0;
				}
				break;
			case DRAW_CIRCLE_BRE_MODE:case DRAW_CIRCLE_DDA_MODE:case DRAW_CIRCLE_MP_MODE:
				if (PressNum == 0) {
					mPointOrign = point;
					mPointOld = point;
					mPointOld1 = point; //记录第一点 
					PressNum++;
				}
				else {
					pDoc->group[0] = mPointOrign;
					pDoc->group[1] = point;
					if (MenuID == DRAW_CIRCLE_BRE_MODE) {
						g.drawCircleBresenham(mPointOrign.x, mPointOrign.y,
											  sqrt(pow(mPointOld.x - point.x, 2) + pow(mPointOld.y - point.y, 2)));
					}
					else if (MenuID == DRAW_CIRCLE_DDA_MODE) {
						g.drawCircleDDA(mPointOrign.x, mPointOrign.y,
										sqrt(pow(mPointOld.x - point.x, 2) + pow(mPointOld.y - point.y, 2)));
					}
					else if (MenuID == DRAW_CIRCLE_MP_MODE) {
						g.drawCircleMP(mPointOrign.x, mPointOrign.y,
									   sqrt(pow(mPointOld.x - point.x, 2) + pow(mPointOld.y - point.y, 2)));
					}
					g.SetPixel(mPointOrign.x, mPointOrign.y, RGB(255, 255, 255));
					mPointOrign = point;
					mPointOld = point;
					PressNum = 0;
				}
				if (PressNum == 1 && MenuID == 33) 					//圆裁剪
				{
					pDoc->group[PressNum] = point;
					PressNum = 0;
					pDoc->CircleCut(&ht);
					ReleaseCapture();
				}

			default:
				break;
		}
	}

	ReleaseDC(dc);
	CView::OnLButtonDown(nFlags, point);
}





void CGIS_CGView::OnMouseMove(UINT nFlags, CPoint point) {
	CGIS_CGDoc *pDoc = GetDocument(); //获得文档类指针
	CClientDC pDC(this);
	CDC *dc = GetDC();
	MyCDC &g = static_cast<MyCDC&>(*dc);
	OnPrepareDC(dc);
	pDC.SetROP2(R2_NOT);
	g.SetROP2(R2_NOT);
	if ((MenuID == 1 || MenuID == 11 || MenuID == 15 || MenuID == 20 || MenuID == 22 || MenuID == 24 || MenuID == 25 || MenuID == DRAW_LINE_DDA_MODE || MenuID == DRAW_LINE_MP_MODE)
		&& PressNum > 0) {
		if (mPointOld != point) {
			g.drawLine2PointDDA(mPointOrign, mPointOld);
			g.drawLine2PointDDA(mPointOrign, point);
			mPointOld = point;
		}
	}

	switch (MenuID) {
		case DRAW_CIRCLE_BRE_MODE:case DRAW_CIRCLE_DDA_MODE:case DRAW_CIRCLE_MP_MODE:
			if (mPointOld != point&& PressNum > 0) {
				g.SelectStockObject(NULL_BRUSH);//画空心圆 
				double r = (int)sqrt((mPointOrign.x - mPointOld.x)*(mPointOrign.x -
																	mPointOld.x) + (mPointOrign.y - mPointOld.y)*(mPointOrign.y - mPointOld.y));
				g.Ellipse(mPointOrign.x - r, mPointOrign.y - r, mPointOrign.x + r, mPointOrign.y + r);//擦旧圆 
				r = (int)sqrt((mPointOrign.x - point.x)*(mPointOrign.x - point.x)
							  + (mPointOrign.y - point.y)*(mPointOrign.y - point.y));
				g.Ellipse(mPointOrign.x - r, mPointOrign.y - r, mPointOrign.x + r, mPointOrign.y + r);//画新圆 
				mPointOld = point;
			}
			break;
		default:
			break;
	}
	ReleaseDC(dc);
	CString c;
	c.Format(L"%d,%d", point.x, point.y);
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	p->m_wndStatusBar.SetPaneText(0, c);
	CView::OnMouseMove(nFlags, point);
}



void CGIS_CGView::OnRButtonDown(UINT nFlags, CPoint point) {
	CGIS_CGDoc *pDoc = GetDocument(); //获得文档类指针
	CClientDC ht(this);
	CDC *dc = GetDC();
	MyCDC &g = static_cast<MyCDC&>(*dc);
	g.setColor(0, 0, 0);
	if (MenuID == 20 && PressNum > 0) { //  种子填充 
		ht.MoveTo(mPointOrign);//擦除橡皮筋
		ht.LineTo(point);
		pDoc->group[0] = mPointOld1;//封闭多边形
		pDoc->group[1] = mPointOrign;
		g.drawLineMP(pDoc->group[0].x, pDoc->group[0].y, pDoc->group[1].x, pDoc->group[1].y);
		PressNum = 0; MenuID = 21;//改变操作方式为种子点选取
	}
	else if (MenuID == 22) { // 边缘填充选点结束 
		g.SetROP2(R2_COPYPEN);
		pDoc->group[PressNum] = pDoc->group[0]; pDoc->PointNum++;
		//ht.MoveTo(pDoc->group[PressNum - 1]);
		g.drawLine2PointDDA(pDoc->group[PressNum - 1], pDoc->group[0]);
		//ht.LineTo(pDoc->group[0]);
		for (int i = 0; i < PressNum; i++)
			//ht.LineTo(pDoc->group[i + 1]);
			g.drawLine2PointDDA(pDoc->group[i], pDoc->group[i + 1]);
		pDoc->EdgeFill(&ht);
		PressNum = 0;
		//pDoc->PointNum = 0;
	}
	else if (MenuID == 25) { // 多边形裁剪 
		pDoc->group[PressNum] = pDoc->group[0];//将第一个顶点作为最后一个顶点 
		pDoc->PointNum = PressNum;	//记录顶点数量
		ht.MoveTo(pDoc->group[PressNum - 1]); ht.LineTo(pDoc->group[0]);
		pDoc->PolygonCut(&ht);
		PressNum = 0; pDoc->PointNum = 0;
		ReleaseCapture();
	}

	else if (MenuID >= 100) {
		MenuID = 0;
	}
	else {
		MenuID = 0;
	}
	ReleaseDC(dc);
	CView::OnRButtonDown(nFlags, point);
}

void CGIS_CGView::OnFill() {
	PressNum = 0; MenuID = 20;
}

void CGIS_CGView::OnEdgefill() {
	MenuID = 22;
}


void CGIS_CGView::OnDrawlinedda() {
	MenuID = DRAW_LINE_DDA_MODE;
}


void CGIS_CGView::OnDrawlinemp() {
	MenuID = DRAW_LINE_MP_MODE;
}


void CGIS_CGView::OnDrawcircledda() {
	MenuID = DRAW_CIRCLE_DDA_MODE;
	PressNum = 0;
}


void CGIS_CGView::OnDrawcirclemp() {
	MenuID = DRAW_CIRCLE_MP_MODE;
	PressNum = 0;

}


void CGIS_CGView::OnDrawcirclebre() {
	MenuID = DRAW_CIRCLE_BRE_MODE;
	PressNum = 0;
}


void CGIS_CGView::OnDrawellipse() {
	MenuID = DRAW_ELLIPSE_MP_MODE;
	PressNum = 0;
}


void CGIS_CGView::OnClear() {
	CClientDC pDC(this);
	CDC *dc = GetDC();
	MyCDC &g = static_cast<MyCDC&>(*dc);
	COLORREF oldcolor = g.GetBkColor();
	RECT r;
	GetClientRect(&r);
	g.clearByRectangle(r);
	ReleaseDC(dc);
}


void CGIS_CGView::OnClearQuick() {
	CClientDC pDC(this);
	CDC *dc = GetDC();
	MyCDC &g = static_cast<MyCDC&>(*dc);
	COLORREF oldcolor = g.GetBkColor();
	RECT r;
	GetClientRect(&r);
	CBrush brush(ColorWhite);
	g.FillRect(&r, &brush);
	ReleaseDC(dc);
}


void CGIS_CGView::OnGraphMove() {
	CGIS_CGDoc *pDoc = GetDocument(); //获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->GenerateGraph(&pDC);//调用文档类函数在屏幕上生成图形 
	PressNum = 0; MenuID = DRAW_MOVE;

}


void CGIS_CGView::OnMulCut() {
	CGIS_CGDoc *pDoc = GetDocument(); //获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->DrawWindow(&pDC);
	PressNum = 0; MenuID = 24;
}


void CGIS_CGView::OnCutPoly() {
	CGIS_CGDoc *pDoc = GetDocument(); //获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->DrawWindow(&pDC);
	PressNum = 0; MenuID = 25;
}


void CGIS_CGView::OnCircleCut() {
	CGIS_CGDoc *pDoc = GetDocument(); //获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->DrawWindow(&pDC);
	PressNum = 0; MenuID = 33;
}
