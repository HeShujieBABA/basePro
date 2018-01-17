#pragma once

// CSocketListen ÃüÁîÄ¿±ê
#include "SocketServer.h"
class CSocketListen : public CSocket
{
public:
	CSocketListen();
	virtual ~CSocketListen();
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


