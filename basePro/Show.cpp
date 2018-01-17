// Show.cpp : 实现文件
//

#include "stdafx.h"
#include "basePro.h"
#include "baseProDlg.h"
#include "Show.h"
#include "afxdialogex.h"


// CShow 对话框

IMPLEMENT_DYNAMIC(CShow, CDialogEx)

CShow::CShow(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShow::IDD, pParent)
{

}

CShow::~CShow()
{
}

void CShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShow, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CShow 消息处理程序


void CShow::OnPaint()
{

	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	
}
