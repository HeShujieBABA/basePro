
// TCPClntDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "SocketClient.h"

// CTCPClntDemoDlg �Ի���
class CTCPClntDemoDlg : public CDialogEx
{
// ����
public:
	CTCPClntDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TCPCLNTDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	SocketClient m_socketClient;
	

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
