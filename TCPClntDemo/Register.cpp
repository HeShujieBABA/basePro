// Register.cpp : 实现文件
//

#include "stdafx.h"
#include "TCPClntDemo.h"
#include "Register.h"
#include "afxdialogex.h"


// Register 对话框

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


// Register 消息处理程序


void Register::OnBnClickedButtonrcomfirm()
{
	CTCPClntDemoDlg *mainDlg = (CTCPClntDemoDlg*)AfxGetMainWnd();
	UpdateData(TRUE);
	if (m_rUsername.IsEmpty())
	{
		MessageBox(_T("用户名不能为空"));
		m_rUsername = _T("");
		UpdateData(FALSE);
		return;
	}
	if (m_rPsw.IsEmpty())
	{
		MessageBox(_T("密码不能为空"));
		m_rPsw = _T("");
		UpdateData(FALSE);
		return;
	}
	if (m_rConPsw.IsEmpty())
	{
		MessageBox(_T("确认密码不能为空"));
		m_rPsw = _T("");
		UpdateData(FALSE);
		return;
	}
	if (m_rPsw != m_rConPsw)
	{
		MessageBox(_T("两次密码输入不同！"));
		m_rConPsw = _T("");
		UpdateData(FALSE);
		return;
	}
	//数据的判断，比如长度
	//m_edt_UserName.GetLength()

	User userInfo;
	USES_CONVERSION;
	strcpy_s(userInfo.m_aName,T2A(m_rUsername));
	strcpy_s(userInfo.m_aPsw ,T2A(m_rPsw));

	//先发送协议
	int msgType = MSG_REGISTER;
	mainDlg->m_socketClient.Send(&msgType,sizeof(msgType));

	//再发送内容
	mainDlg->m_socketClient.Send(&userInfo,sizeof(User));

	//再接受服务器端发送过来的结果
	//bool bSrvRes = false;
	int bSrvRes;
	mainDlg->m_socketClient.Receive(&bSrvRes,sizeof(bSrvRes));

	if (bSrvRes!=2)
	{
		MessageBox(_T("注册失败！请重试！"));
		m_rPsw = _T("");
		m_rConPsw = _T("");

		UpdateData(FALSE);
		return;
	}
	else
	{
		MessageBox(_T("注册成功！"));
		EndDialog(1001);  //这个函数是用来关闭模态对话框的
	}
}
