#pragma once
#include "afxwin.h"


// mainDlg 对话框

class mainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(mainDlg)

public:
	mainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~mainDlg();

// 对话框数据
	enum { IDD = IDD_MAIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	
	// 连接
	CButton btnConnect;
	// 帮助
	CButton btnHelp;
	// 计算机IP
	CString etComputer;
	
	afx_msg void OnBnClickedButtonHelp();
	virtual BOOL OnInitDialog();
	

	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnPaint();
};
