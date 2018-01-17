
// TCPSerDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TCPSerDemo.h"
#include "TCPSerDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTCPSerDemoDlg �Ի���



CTCPSerDemoDlg::CTCPSerDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCPSerDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCPSerDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTCPSerDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CTCPSerDemoDlg ��Ϣ�������

BOOL CTCPSerDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	//�����׽���
	BOOL nResult = m_socketListen.Create(6666);
	UINT nError = GetLastError();

	//�����Ĵ���ʧ��2�� һ��Ϊ��ʼ���׽���ʧ�ܣ�һ���Ƕ˿ںű�ռ��

	if (nError == WSANOTINITIALISED)
	{
		AfxMessageBox(_T("δ��ʼ���׽�����ػ��ʼ��ʧ�ܣ�")); //����δ����AfxSocketInit��������ʧ��
	}
	if(nError== WSAEADDRINUSE)
	{
		AfxMessageBox(_T("�˿ڱ�ռ�ã�")); 
	}
    //��ʼ����
	m_socketListen.Listen();//Ĭ��Ϊ5


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}



// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTCPSerDemoDlg::OnPaint()
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
HCURSOR CTCPSerDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

