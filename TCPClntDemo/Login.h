#pragma once


// Login �Ի���
#include "User.h"
#include "TCPClntDemoDlg.h"
class Login : public CDialogEx
{
	DECLARE_DYNAMIC(Login)

public:
	Login(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Login();

// �Ի�������
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_ed_Username;
	CString m_ed_Password;
	afx_msg void OnBnClickedLogin();
//	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnBnClickedRegister();
};
