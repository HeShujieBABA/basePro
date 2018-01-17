// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TCPClntDemo.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Register.h"
// Login �Ի���

IMPLEMENT_DYNAMIC(Login, CDialogEx)

Login::Login(CWnd* pParent /*=NULL*/)
	: CDialogEx(Login::IDD, pParent)
	, m_ed_Username(_T(""))
	, m_ed_Password(_T(""))
{

}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Uname, m_ed_Username);
	DDX_Text(pDX, IDC_EDIT_Upsw, m_ed_Password);
}


BEGIN_MESSAGE_MAP(Login, CDialogEx)
	ON_BN_CLICKED(IDC_Login, &Login::OnBnClickedLogin)
//	ON_WM_SYSCOMMAND()
ON_WM_CLOSE()
ON_BN_CLICKED(IDC_Register, &Login::OnBnClickedRegister)
END_MESSAGE_MAP()


// Login ��Ϣ�������


void Login::OnBnClickedLogin()
{
	CTCPClntDemoDlg *mainDlg = (CTCPClntDemoDlg*)AfxGetMainWnd();
	UpdateData(TRUE);
	if (m_ed_Username.IsEmpty())
	{
		MessageBox(_T("�û�������Ϊ��"));
		m_ed_Username = _T("");
		UpdateData(FALSE);
		return;
	}
	if (m_ed_Password.IsEmpty())
	{
		MessageBox(_T("���벻��Ϊ��"));
		m_ed_Password = _T("");
		UpdateData(FALSE);
		return;
	}
	//���ݵ��жϣ����糤��
	//m_edt_UserName.GetLength()

	User userInfo;
	USES_CONVERSION;
	strcpy_s(userInfo.m_aName,T2A(m_ed_Username));
	strcpy_s(userInfo.m_aPsw ,T2A(m_ed_Password));

	//�ȷ���Э��
	int msgType = MSG_LOGIN;
	mainDlg->m_socketClient.Send(&msgType,sizeof(msgType));

	//�ٷ�������
	mainDlg->m_socketClient.Send(&userInfo,sizeof(User));

	//�ٽ��ܷ������˷��͹����Ľ��
	//bool bSrvRes = false;
	int bSrvRes;
	mainDlg->m_socketClient.Receive(&bSrvRes,sizeof(bSrvRes));

	if (bSrvRes!=2)
	{
		MessageBox(_T("��¼ʧ�ܣ������û��������룡"));
		m_ed_Username = _T("");
		m_ed_Password = _T("");
		UpdateData(FALSE);
		return;
	}
	else
	{
		MessageBox(_T("��¼�ɹ���"));
		EndDialog(1001);  //��������������ر�ģ̬�Ի����
	}


}

void Login::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	EndDialog(1002);  //��������������ر�ģ̬�Ի����
	CDialogEx::OnClose();
}


void Login::OnBnClickedRegister()
{
	Register zhuce;
	zhuce.DoModal();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
