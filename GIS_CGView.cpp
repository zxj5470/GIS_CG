
// GIS_CGView.cpp : CGIS_CGView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "GIS_CG.h"
#endif

#include "GIS_CGDoc.h"
#include "GIS_CGView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGIS_CGView

IMPLEMENT_DYNCREATE(CGIS_CGView, CView)

BEGIN_MESSAGE_MAP(CGIS_CGView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CGIS_CGView ����/����

CGIS_CGView::CGIS_CGView()
{
	// TODO: �ڴ˴���ӹ������

}

CGIS_CGView::~CGIS_CGView()
{
}

BOOL CGIS_CGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CGIS_CGView ����

void CGIS_CGView::OnDraw(CDC* /*pDC*/)
{
	CGIS_CGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CGIS_CGView ��ӡ

BOOL CGIS_CGView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGIS_CGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGIS_CGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CGIS_CGView ���

#ifdef _DEBUG
void CGIS_CGView::AssertValid() const
{
	CView::AssertValid();
}

void CGIS_CGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGIS_CGDoc* CGIS_CGView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGIS_CGDoc)));
	return (CGIS_CGDoc*)m_pDocument;
}
#endif //_DEBUG


// CGIS_CGView ��Ϣ�������
