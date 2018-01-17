#pragma once

// SocketServer ÃüÁîÄ¿±ê

class SocketServer : public CSocket
{
public:
	SocketServer();
	virtual ~SocketServer();
	virtual void OnReceive(int nErrorCode);
	void DoLogin();
	void DoRegister();
};


