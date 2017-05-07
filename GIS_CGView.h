
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
};

#ifndef _DEBUG  // GIS_CGView.cpp 中的调试版本
inline CGIS_CGDoc* CGIS_CGView::GetDocument() const
   { return reinterpret_cast<CGIS_CGDoc*>(m_pDocument); }
#endif

