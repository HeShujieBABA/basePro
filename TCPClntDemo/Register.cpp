// Register.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TCPClntDemo.h"
#include "Register.h"
#include "afxdialogex.h"


// Register �Ի���

IMPLEMENT_DYNAMIC(Register, CDialogEx)

Register::Register(CWnd* pParent /*=NULL*/)
	: CDialogEx(Register::IDD, pParent)
	, m_rUsername(_T(""))
	, m_rPsw(_T(""))
	, m_rConPsw(_T(""))
{

}

Register::~Register()
{
}

void Register::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_rusername, m_rUsername);
	DDX_Text(pDX, IDC_EDIT_rPsw, m_rPsw);
	DDX_Text(pDX, IDC_EDIT_rConfirm, m_rConPsw);
}


BEGIN_MESSAGE_MAP(Register, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_rComfirm, &Register::OnBnClickedButtonrcomfirm)
END_MESSAGE_MAP()


// Register ��Ϣ�������


void Register::OnBnClickedButtonrcomfirm()
{
	CTCPClntDemoDlg *mainDlg = (CTCPClntDemoDlg*)AfxGetMainWnd();
	UpdateData(TRUE);
	if (m_rUsername.IsEmpty())
	{
		MessageBox(_T("�û�������Ϊ��"));
		m_rUsername = _T("");
		UpdateData(FALSE);
		return;
	}
	if (m_rPsw.IsEmpty())
	{
		MessageBox(_T("���벻��Ϊ��"));
		m_rPsw = _T("");
		UpdateData(FALSE);
		return;
	}
	if (m_rConPsw.IsEmpty())
	{
		MessageBox(_T("ȷ�����벻��Ϊ��"));
		m_rPsw = _T("");
		UpdateData(FALSE);
		return;
	}
	if (m_rPsw != m_rConPsw)
	{
		MessageBox(_T("�����������벻ͬ��"));
		m_rConPsw = _T("");
		UpdateData(FALSE);
		return;
	}
	//���ݵ��жϣ����糤��
	//m_edt_UserName.GetLength()

	User userInfo;
	USES_CONVERSION;
	strcpy_s(userInfo.m_aName,T2A(m_rUsername));
	strcpy_s(userInfo.m_aPsw ,T2A(m_rPsw));

	//�ȷ���Э��
	int msgType = MSG_REGISTER;
	mainDlg->m_socketClient.Send(&msgType,sizeof(msgType));

	//�ٷ�������
	mainDlg->m_socketClient.Send(&userInfo,sizeof(User));

	//�ٽ��ܷ������˷��͹����Ľ��
	//bool bSrvRes = false;
	int bSrvRes;
	mainDlg->m_socketClient.Receive(&bSrvRes,sizeof(bSrvRes));

	if (bSrvRes!=2)
	{
		MessageBox(_T("ע��ʧ�ܣ������ԣ�"));
		m_rPsw = _T("");
		m_rConPsw = _T("");

		UpdateData(FALSE);
		return;
	}
	else
	{
		MessageBox(_T("ע��ɹ���"));
		EndDialog(1001);  //��������������ر�ģ̬�Ի����
	}
}
