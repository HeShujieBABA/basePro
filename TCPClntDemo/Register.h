#pragma once


// Register 对话框
#include "User.h"
#include"TCPClntDemoDlg.h"
class Register : public CDialogEx
{
	DECLARE_DYNAMIC(Register)

public:
	Register(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Register();

// 对话框数据
	enum { IDD = IDD_DIALOG_register };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_rUsername;
	CString m_rPsw;
	CString m_rConPsw;
	afx_msg void OnBnClickedButtonrcomfirm();
};
