// mainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "basePro.h"
#include "baseProDlg.h"
#include "mainDlg.h"
#include "afxdialogex.h"
#include "Show.h"
#include "Resource.h"



// mainDlg 对话框

IMPLEMENT_DYNAMIC(mainDlg, CDialogEx)

mainDlg::mainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(mainDlg::IDD, pParent)
	, etComputer(_T(""))
{

}

mainDlg::~mainDlg()
{
}

void mainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, btnConnect);
	DDX_Control(pDX, IDC_BUTTON_HELP, btnHelp);
	DDX_Text(pDX, IDC_EDIT_COMPUTER, etComputer);
}


BEGIN_MESSAGE_MAP(mainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &mainDlg::OnBnClickedButtonHelp)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &mainDlg::OnBnClickedButtonConnect)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void mainDlg::OnBnClickedButtonHelp()
{
	// TODO:  在此添加控件通知处理程序代码
}


BOOL mainDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}



void mainDlg::OnBnClickedButtonConnect()
{
	    int i = 1;
		USES_CONVERSION;
		//先进行简单的数据验证
		CUser userInfo;
		strcpy_s(userInfo.aName, T2A(etComputer));
		int nType = MSG_LOGIN;
		//这个函数是用来获取主对话框的窗口句柄
		CbaseProDlg *pMainDlg = (CbaseProDlg *)AfxGetMainWnd();
		//先发送协议
		pMainDlg->m_mySocket.Send(&nType, sizeof(int));
		//再发送内容
		pMainDlg->m_mySocket.Send(&userInfo, sizeof(CUser));
		int nLoginSuccess;
		pMainDlg->m_mySocket.Receive(&nLoginSuccess, sizeof(int));
		if (nLoginSuccess == 2 ){
			::Sleep(1000);

			int bType = MSG_TEXT;
			pMainDlg->m_mySocket.Send(&bType, sizeof(int));

			while(true){
				//发送图片
				//获取屏幕截图
				//发送协议
				int nStart = 100;
				pMainDlg->m_mySocket.Send(&nStart, sizeof(int));
				HDC hDCScreen = ::GetDC(NULL); //首先获取屏幕的句柄
				int nBitPerPixel = GetDeviceCaps(hDCScreen, BITSPIXEL);
				int nWidthScreen = GetDeviceCaps(hDCScreen, HORZRES);
				int nHeightScreen = GetDeviceCaps(hDCScreen, VERTRES);
				//创建一个CImage的对象
				CImage m_MyImage;
				//Create实例化CImage，使得其内部的画布大小与屏幕一致
				m_MyImage.Create(nWidthScreen, nHeightScreen, nBitPerPixel);
				HDC hDCImg = m_MyImage.GetDC();
				//使用bitblt 将屏幕的DC画布上的内容 拷贝到CImage上
				BitBlt(hDCImg, 0, 0, nWidthScreen, nHeightScreen, hDCScreen, 0, 0, SRCCOPY);
				CString strI;
				strI.Format(_T("%d"), i);
				CString picPath = (CString)"theme\\" + (CString)strI + (CString)".png";
				i++;
				m_MyImage.Save(picPath, Gdiplus::ImageFormatPNG);
				m_MyImage.ReleaseDC();

				WIN32_FIND_DATA FindFileData;
				FindClose(FindFirstFile(picPath, &FindFileData));
				pMainDlg->m_mySocket.Send(&FindFileData, sizeof(WIN32_FIND_DATA));

				CFile file;
				if (!file.Open(picPath, CFile::modeRead | CFile::typeBinary)){
					AfxMessageBox(_T("文件不存在"));
				}

				//发送
				UINT nSize = 0;
				UINT nSend = 0;
				char szBuff[2048];
				while (nSize < FindFileData.nFileSizeLow)
				{
					memset(szBuff, 0x00, 2048);
					nSend = file.Read(szBuff, 2048);
					pMainDlg->m_mySocket.Send(&szBuff, nSend);//发送数据
					nSize += nSend;
				}
				file.Close();
				::Sleep(800);

				boolean isSend = true;
				pMainDlg->m_mySocket.Send(&isSend, sizeof(boolean));

				::Sleep(700);
				}
		}
}


void mainDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect clientRect;
	GetClientRect(&clientRect);
	CImage imgHero;  //图片的对象
	imgHero.Load(_T("theme\\background_1.png"));
	imgHero.BitBlt(dc, 0, 0, imgHero.GetWidth(), imgHero.GetHeight(), 0, 0, SRCCOPY);
}
