
// GIS_CGView.cpp : CGIS_CGView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GIS_CG.h"
#endif

#include "GIS_CGDoc.h"
#include "GIS_CGView.h"
#include "MyCDC.h"
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
END_MESSAGE_MAP()

// CGIS_CGView 构造/析构

CGIS_CGView::CGIS_CGView()
{
	// TODO: 在此处添加构造代码

}

CGIS_CGView::~CGIS_CGView()
{
}

BOOL CGIS_CGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGIS_CGView 绘制

void CGIS_CGView::OnDraw(CDC* pDC)
{
	CGIS_CGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	////add console to "debug"
	//AllocConsole();                          // 开辟控制台
	//SetConsoleTitle(_T("Debug Title"));      // 设置控制台窗口标题
	//FILE* pf;
	//freopen_s(&pf, "CONOUT$", "w", stdout);
	

	MyCDC &g = static_cast<MyCDC&>(*pDC);

	g.drawCircleBresenham(100, 100, 30);
	g.setColor(200, 10, 10);
	g.drawLineDDA(10, 10, 200, 200);
	// TODO: 在此处为本机数据添加绘制代码
}


// CGIS_CGView 打印
BOOL CGIS_CGView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGIS_CGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGIS_CGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CGIS_CGView 诊断

#ifdef _DEBUG
void CGIS_CGView::AssertValid() const
{
	CView::AssertValid();
}

void CGIS_CGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGIS_CGDoc* CGIS_CGView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGIS_CGDoc)));
	return (CGIS_CGDoc*)m_pDocument;
}
#endif //_DEBUG


// CGIS_CGView 消息处理程序
