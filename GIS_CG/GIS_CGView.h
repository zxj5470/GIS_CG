
// GIS_CGView.h : CGIS_CGView 类的接口
//

#pragma once

class CGIS_CGView : public CView
{
protected: // 仅从序列化创建
	CGIS_CGView();
	DECLARE_DYNCREATE(CGIS_CGView)
// 特性
public:
	CGIS_CGDoc* GetDocument() const;
protected: // create from serialization only 
	int MenuID, PressNum, SaveNumber;
	CPoint mPointOrign, mPointOld, mPointOld1;
private :
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGIS_CGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFill();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEdgefill();
	afx_msg void OnDrawlinedda();
	afx_msg void OnDrawlinemp();
	afx_msg void OnDrawcircledda();
	afx_msg void OnDrawcirclemp();
	afx_msg void OnDrawcirclebre();
	afx_msg void OnDrawellipse();
	afx_msg void OnClear();
	afx_msg void OnClearQuick();
	afx_msg void OnGraphMove();
	afx_msg void OnMulCut();
	afx_msg void OnCutPoly();
	afx_msg void OnCircleCut();
};

#ifndef _DEBUG  // GIS_CGView.cpp 中的调试版本
inline CGIS_CGDoc* CGIS_CGView::GetDocument() const
   { return reinterpret_cast<CGIS_CGDoc*>(m_pDocument); }
#endif

