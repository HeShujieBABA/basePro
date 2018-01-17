
// TCPClntDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TCPClntDemo.h"
#include "TCPClntDemoDlg.h"
#include "afxdialogex.h"
#include "Login.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTCPClntDemoDlg �Ի���



CTCPClntDemoDlg::CTCPClntDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCPClntDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCPClntDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTCPClntDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CTCPClntDemoDlg ��Ϣ�������

BOOL CTCPClntDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	//�ͻ�������˿�
	if(!m_socketClient.Create()){
		AfxMessageBox(_T("��������ʧ��!"));
		return FALSE;
	}
	//��ʼ����
	else if(!m_socketClient.Connect(_T("127.0.0.1"),6666)){
		int nError = GetLastError();
		MessageBox(_T("���ӷ�����ʧ�ܣ�"));
		return FALSE;
	}
	else
	{
	int nRes = 0;
	Login loginDlg;
	nRes = loginDlg.DoModal();
	if(nRes == 1002)
	{
		return FALSE;
	}
}	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTCPClntDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTCPClntDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

