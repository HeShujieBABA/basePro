#pragma once


// Register �Ի���
#include "User.h"
#include"TCPClntDemoDlg.h"
class Register : public CDialogEx
{
	DECLARE_DYNAMIC(Register)

public:
	Register(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Register();

// �Ի�������
	enum { IDD = IDD_DIALOG_register };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_rUsername;
	CString m_rPsw;
	CString m_rConPsw;
	afx_msg void OnBnClickedButtonrcomfirm();
};
