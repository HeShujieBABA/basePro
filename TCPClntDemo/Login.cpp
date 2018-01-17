// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "TCPClntDemo.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Register.h"
// Login 对话框

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


// Login 消息处理程序


void Login::OnBnClickedLogin()
{
	CTCPClntDemoDlg *mainDlg = (CTCPClntDemoDlg*)AfxGetMainWnd();
	UpdateData(TRUE);
	if (m_ed_Username.IsEmpty())
	{
		MessageBox(_T("用户名不能为空"));
		m_ed_Username = _T("");
		UpdateData(FALSE);
		return;
	}
	if (m_ed_Password.IsEmpty())
	{
		MessageBox(_T("密码不能为空"));
		m_ed_Password = _T("");
		UpdateData(FALSE);
		return;
	}
	//数据的判断，比如长度
	//m_edt_UserName.GetLength()

	User userInfo;
	USES_CONVERSION;
	strcpy_s(userInfo.m_aName,T2A(m_ed_Username));
	strcpy_s(userInfo.m_aPsw ,T2A(m_ed_Password));

	//先发送协议
	int msgType = MSG_LOGIN;
	mainDlg->m_socketClient.Send(&msgType,sizeof(msgType));

	//再发送内容
	mainDlg->m_socketClient.Send(&userInfo,sizeof(User));

	//再接受服务器端发送过来的结果
	//bool bSrvRes = false;
	int bSrvRes;
	mainDlg->m_socketClient.Receive(&bSrvRes,sizeof(bSrvRes));

	if (bSrvRes!=2)
	{
		MessageBox(_T("登录失败，请检查用户名或密码！"));
		m_ed_Username = _T("");
		m_ed_Password = _T("");
		UpdateData(FALSE);
		return;
	}
	else
	{
		MessageBox(_T("登录成功！"));
		EndDialog(1001);  //这个函数是用来关闭模态对话框的
	}


}

void Login::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	EndDialog(1002);  //这个函数是用来关闭模态对话框的
	CDialogEx::OnClose();
}


void Login::OnBnClickedRegister()
{
	Register zhuce;
	zhuce.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}
