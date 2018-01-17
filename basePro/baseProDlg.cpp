
// baseProDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "basePro.h"
#include "baseProDlg.h"
#include "afxdialogex.h"
#include "mainDlg.h"
#include "winsock.h"    
#include "mysql.h"  
#include "cstring"
#pragma comment(lib,"libmysql.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CbaseProDlg 对话框



CbaseProDlg::CbaseProDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CbaseProDlg::IDD, pParent)
	, etUsername(_T(""))
	, etPassword(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CbaseProDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, etUsername);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, etPassword);
	DDX_Control(pDX, IDC_BUTTON_LOGIN, btnLogin);
	DDX_Control(pDX, IDC_BUTTON_REGISTER, btnRegister);
}

BEGIN_MESSAGE_MAP(CbaseProDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CbaseProDlg::OnClickedButtonLogin)
END_MESSAGE_MAP()


// CbaseProDlg 消息处理程序

BOOL CbaseProDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CbaseProDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CbaseProDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		
		//获取窗口dc，你要在哪画
		CPaintDC dc(this); //获取当前程序窗口的dc
		//dc就是设备上下文，也叫做设备描述符或设备环境

		//获取窗口的大小,你要画多大
		CRect clientRect;
		GetClientRect(&clientRect);

		//准备图片，你要画什么上去
		CImage imgHero;  //图片的对象
		//CImage imgSwore;
		//相对路径和绝对路径,一定要注意图片的后缀名
		//绘图的出现的问题，绝大多数会出现这里
		imgHero.Load(_T("theme\\background_1.png"));
		//imgSwore.Load(_T("theme\\background.jpeg"));

		//imgHero.Draw(dc,0,0,clientRect.Width(),clientRect.Height());
		//imgHero.Draw(dc,0,0,imgHero.GetWidth(),imgHero.GetHeight());

		//imgSwore.Draw(dc,0,0,clientRect.Width(),clientRect.Height());
		//imgSwore.Draw(dc,0,0,imgSwore.GetWidth(),imgSwore.GetHeight());

		imgHero.BitBlt(dc,0,0,imgHero.GetWidth(),imgHero.GetHeight(),0,0,SRCCOPY);
		//imgSwore.BitBlt(dc,100,100,clientRect.Width(),clientRect.Height(),0,0,SRCCOPY);

		//当你要去很多张图片的时候，贴很多的图，或者是有很多图要刷新的时候，这个时候就会出现闪烁
		//双缓冲绘图技术
		//他会先将图片拷贝到内存上，再由内存拷贝到桌面上
		//CDC memDC; //内存dc，主要用于将图片保存它这里CDC,HDC CPaintDC
		//这里是用来创建一个相兼容的位图对象，可以理解为画布
		//CBitmap hBitMap;

		//这里的相兼容是与窗口dc相兼容
		//hBitMap.CreateCompatibleBitmap(&dc, clientRect.Width(), clientRect.Height());

		//创建一个相兼容的DC,这里内存dc与窗口dc相兼容
		//memDC.CreateCompatibleDC(&dc);

		//选择上面所创建的相兼容的位图对象，并要保存原有的位图对象,因为系统
		//会提供一个十分简单的位图对象
		//CBitmap* hOldMap = (CBitmap*)memDC.SelectObject(&hBitMap);
		//先将图片画在内存dc上面
		//imgHero.BitBlt(memDC, 0, 0, clientRect.Width(), clientRect.Height(), 0, 0, SRCCOPY);
		//imgSwore.BitBlt(memDC, 0, 0, clientRect.Width(), clientRect.Height(), 0, 0, SRCCOPY);

		//再将内存dc上面的内容画到窗口dc上面
		//dc.BitBlt(0, 0, clientRect.Width(), clientRect.Height(), &memDC, 0, 0, SRCCOPY);

		//一些资源释放的操作
		//将原来的位图对象还原
		//memDC.SelectObject(hOldMap);  //选择原来系统提供给我们的位图对象
		//hBitMap.DeleteObject();
		//memDC.DeleteDC();
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CbaseProDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CbaseProDlg::OnClickedButtonLogin()
{


	MYSQL m_sqlCon;
	CString dbUsername, dbPassword;
	CString etUsername,etPassword;
	MYSQL_RES *res;
	MYSQL_ROW row ;

	
	mysql_init(&m_sqlCon);
	   
	if (!mysql_real_connect(&m_sqlCon, "139.199.75.89", "root", "", "user", 3306, NULL, 0))
	{
		AfxMessageBox(_T("访问数据库失败!"));
		return;
	}
	else
	{
		mysql_query(&m_sqlCon, "SET NAMES 'GB2312'");
		if (mysql_real_query(&m_sqlCon, "select * from user", (unsigned long)strlen("select * from user"))) 
		{
			return;
		}
		res = mysql_store_result(&m_sqlCon);
		if (NULL == res)
		{
			return;
		}
		while (row = mysql_fetch_row(res)){
			
			dbUsername = row[1];
			dbPassword = row[2];
			
			UpdateData(TRUE);
			GetDlgItemText(IDC_EDIT_USERNAME,etUsername);
			GetDlgItemText(IDC_EDIT_PASSWORD,etPassword);
		
			if (!etUsername.Compare(dbUsername) && !etPassword.Compare(dbPassword)){
				ShowWindow(SW_HIDE);

				//创建套接字
				m_mySocket.Create();
				//连接服务器
				m_mySocket.Connect(_T("100.64.238.119"), 6666);
				
			    //m_mySocket.Connect(_T("127.0.0.1"), 6666);
				mainDlg mainDlg;
				mainDlg.DoModal();
				break;

			}
			else
			{
				MessageBox(_T("用户名或者密码错误，请重试！"), _T("温馨提示"), MB_OKCANCEL|MB_ICONEXCLAMATION);
				break;
			}

		}

	}
	mysql_close(&m_sqlCon);
	mysql_server_end();
}
