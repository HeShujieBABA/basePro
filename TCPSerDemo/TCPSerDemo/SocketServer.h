#pragma once

// SocketServer ����Ŀ��

class SocketServer : public CSocket
{
public:
	SocketServer();
	virtual ~SocketServer();
	virtual void OnReceive(int nErrorCode);
	void DoLogin();
	void DoRegister();
};


