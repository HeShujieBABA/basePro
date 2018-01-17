// SocketListen.cpp : 实现文件
//

#include "stdafx.h"
#include "TCPSerDemo.h"
#include "SocketListen.h"


// CSocketListen

CSocketListen::CSocketListen()
{
}

CSocketListen::~CSocketListen()
{
}


// CSocketListen 成员函数

//客户端链接的时候会触发这个函数
void CSocketListen::OnAccept(int nErrorCode)
{
	//这个定义的变量就是新加入的客户端的套接字
	SocketServer* pSockServer = new SocketServer;
	Accept(*pSockServer);//调用Accept函数，绑定，进行连接


	CSocket::OnAccept(nErrorCode);
}

//客户端和服务器端建立通信后，服务器端接受客户端发送过来的消息时会调用（触发）这个函数
void CSocketListen::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);
}

//断开链接的时候会触发这个函数
void CSocketListen::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnClose(nErrorCode);
}
