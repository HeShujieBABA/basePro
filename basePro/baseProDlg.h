
// baseProDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "MySocket.h"

// CbaseProDlg 对话框
class CbaseProDlg : public CDialogEx
{
// 构造
public:
	CbaseProDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BASEPRO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//这个客户端的套接字就是用来通信的
	MySocket m_mySocket;
	// 用户名
	CString etUsername;
	// 密码
	CString etPassword;
	// 登录按钮
	CButton btnLogin;
	// 注册
	CButton btnRegister;
	afx_msg void OnClickedButtonLogin();
};
