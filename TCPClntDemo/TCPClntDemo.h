
// TCPClntDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTCPClntDemoApp:
// �йش����ʵ�֣������ TCPClntDemo.cpp
//

class CTCPClntDemoApp : public CWinApp
{
public:
	CTCPClntDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTCPClntDemoApp theApp;