
// TCPSerDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "SocketListen.h"

// CTCPSerDemoDlg �Ի���
class CTCPSerDemoDlg : public CDialogEx
{
// ����
public:
	CTCPSerDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TCPSERDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
	CSocketListen m_socketListen ; //���һ�������׽���

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
