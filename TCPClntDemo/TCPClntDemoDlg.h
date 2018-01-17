
// TCPClntDemoDlg.h : 头文件
//

#pragma once
#include "SocketClient.h"

// CTCPClntDemoDlg 对话框
class CTCPClntDemoDlg : public CDialogEx
{
// 构造
public:
	CTCPClntDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TCPCLNTDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	SocketClient m_socketClient;
	

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
