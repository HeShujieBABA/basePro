// SocketListen.cpp : ʵ���ļ�
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


// CSocketListen ��Ա����

//�ͻ������ӵ�ʱ��ᴥ���������
void CSocketListen::OnAccept(int nErrorCode)
{
	//�������ı��������¼���Ŀͻ��˵��׽���
	SocketServer* pSockServer = new SocketServer;
	Accept(*pSockServer);//����Accept�������󶨣���������


	CSocket::OnAccept(nErrorCode);
}

//�ͻ��˺ͷ������˽���ͨ�ź󣬷������˽��ܿͻ��˷��͹�������Ϣʱ����ã��������������
void CSocketListen::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);
}

//�Ͽ����ӵ�ʱ��ᴥ���������
void CSocketListen::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnClose(nErrorCode);
}
