﻿
// GIS_CGDoc.h : CGIS_CGDoc 类的接口
//


#pragma once

class CGIS_CGDoc : public CDocument
{
protected: // 仅从序列化创建
	CGIS_CGDoc();
	DECLARE_DYNCREATE(CGIS_CGDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS
private:
	int encode(int x, int y);
// 实现
public:
	virtual ~CGIS_CGDoc();
	void DDALine(CClientDC *DCPoint);
	void SeedFill(CClientDC *pDC, CPoint seedpoint);
	void EdgeFill(CClientDC *pDC);
	void DrawGraph(CClientDC *pDC);
	void GenerateGraph(CClientDC *pDC);

	void DrawWindow(CClientDC*);
	void CohenSutherland(CClientDC *pDC, CPoint p1, CPoint p2);

	void PolygonCut(CClientDC *DCPoint);
	void EdgeClipping(int linecode);
	void BCircle(CClientDC * DCPoint, CPoint p1, CPoint p2);
	void BCircle(CClientDC * DCPoint,
				 CRect* rc,
				 CPoint p1, CPoint p2);
	void CircleCut(CClientDC *DCPoint);


public:

	CPoint group[100];
	int PointNum;


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
