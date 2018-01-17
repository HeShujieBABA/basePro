
// TCPSerDemoDlg.h : 头文件
//

#pragma once
#include "SocketListen.h"

// CTCPSerDemoDlg 对话框
class CTCPSerDemoDlg : public CDialogEx
{
// 构造
public:
	CTCPSerDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TCPSERDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:
	CSocketListen m_socketListen ; //添加一个监听套接字

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
