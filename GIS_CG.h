
// GIS_CG.h : GIS_CG Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CGIS_CGApp:
// �йش����ʵ�֣������ GIS_CG.cpp
//

class CGIS_CGApp : public CWinApp
{
public:
	CGIS_CGApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGIS_CGApp theApp;
