
// GIS_CGView.h : CGIS_CGView ��Ľӿ�
//

#pragma once


class CGIS_CGView : public CView
{
protected: // �������л�����
	CGIS_CGView();
	DECLARE_DYNCREATE(CGIS_CGView)

// ����
public:
	CGIS_CGDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CGIS_CGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GIS_CGView.cpp �еĵ��԰汾
inline CGIS_CGDoc* CGIS_CGView::GetDocument() const
   { return reinterpret_cast<CGIS_CGDoc*>(m_pDocument); }
#endif

