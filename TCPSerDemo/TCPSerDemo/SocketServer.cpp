// SocketServer.cpp : ʵ���ļ�
//
#include<iostream>
#include "stdafx.h"
#include "TCPSerDemo.h"
#include "SocketServer.h"
#include "mysql.h" 
#include <string>
using namespace std;
// SocketServer

SocketServer::SocketServer()
{
}

SocketServer::~SocketServer()
{
}


// SocketServer ��Ա����


void SocketServer::OnReceive(int nErrorCode)
{
	//�������գ��Ƚ��մ�������TCPͨѶЭ��
	int msgType; //����һ���������յ�Э��
	this->Receive(&msgType,sizeof(msgType)); //��ʼ����
	switch(msgType) //����������Э�飬���ദ��
	{
	case MSG_LOGIN: //��¼Э��
		{
			DoLogin(); //�Լ���д��һ����Ա����
		}
		break;
	case MSG_REGISTER: //ע��Э��
		{
			//Register(); 
			DoRegister();
		}
		break;
	case MSG_TEXT: //��ѯЭ��
		{

		}
		break; 
	case MSG_PIC: //����Э��
		{

		}
		break;
	}

	CSocket::OnReceive(nErrorCode);
}

	//�����¼
	/*********************************
	��������Login
	���������������¼�����͵�¼�Ƿ�ɹ������ݸ��ͻ���
	��������
	����ֵ����
	**********************************/
	void SocketServer::DoLogin(void)
	{
		//bool bRes = false;  //���ڸ��ͻ��˷������ݵı�������ʼ��Ϊfalse
		int bRes = 0;
		User userInfo ;
		//�����жϽ��յ������Ƿ���ȷ
		if (this->Receive(&userInfo,sizeof(User)) != sizeof(User))
		{
			//�������ʧ�ܣ��ͷ������ݣ���ʱbRes��ֵΪfalse
			this->Send(&bRes,sizeof(bRes));
			return ;
		}


		User user;
		strcpy_s(user.m_aName,userInfo.getUserName());
		strcpy_s(user.m_aPsw,userInfo.getPassWord());

		//���ӷ������������жϲ���
		MYSQL *m_sqlCon = NULL;
		m_sqlCon = mysql_init(NULL);
	// localhost:������ root/123456Ϊ�˺����� managesystemdbΪ���ݿ��� 3306Ϊ�˿�    
	if (!mysql_real_connect(m_sqlCon, "localhost", "root", "199716", "User", 3306, NULL, 0))
	{
		AfxMessageBox(_T("�������ݿ�ʧ��!"));
		this->Send(&bRes,sizeof(bRes));
	}
	else
	{
		mysql_query(m_sqlCon, "SET Username 'GB2312'");//��������ݿ��ж�ȡ���ݺ���������ʾ������  
	}
	// ��ѯ��Ӧ���û�������Ӧ����
	string sqlstr;
	sqlstr = "select Username,Passward from `user`.`user_info` where Username = '";
	sqlstr += user.m_aName;
	sqlstr += "';";

	MYSQL_RES *result = NULL;
    if (mysql_query(m_sqlCon, sqlstr.c_str())) {
		this->Send(&bRes,sizeof(bRes));
		return;
	}
	else
	{
	    //һ����ȡ�����ݼ�
		result = mysql_store_result(m_sqlCon);
		//ȡ�ò���ӡ����
        int rowcount = mysql_num_rows(result);

		if (rowcount == 1 )
		{
			//��ȡ��Ӧ���ݵ���
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);

			//�����ж������Ƿ�ƥ��
			if( 0 == strcmp(row[1],user.m_aPsw))
			{
				bRes = 2;
				this->Send(&bRes,sizeof(bRes));
			}
			else{

				this->Send(&bRes,sizeof(bRes));
			}
		} 
		else
		{
			this->Send(&bRes,sizeof(bRes));
		}

	}
		mysql_close(m_sqlCon);
}
	//ע�Ṧ��
	/*********************************
	��������Doregister
	��������������ע�Ტ���ݸ��ͻ���ע��ɹ�����Ϣ
	��������
	����ֵ����
	**********************************/
	void SocketServer::DoRegister(void)
	{
		//bool bRes = false;  //���ڸ��ͻ��˷������ݵı�������ʼ��Ϊfalse
		int bRes = 0;
		User userInfo ;
		//�����жϽ��յ������Ƿ���ȷ
		if (this->Receive(&userInfo,sizeof(User)) != sizeof(User))
		{
			//�������ʧ�ܣ��ͷ������ݣ���ʱbRes��ֵΪfalse
			this->Send(&bRes,sizeof(bRes));
			return ;
		}
		User user;
		strcpy_s(user.m_aName,userInfo.getUserName());
		strcpy_s(user.m_aPsw,userInfo.getPassWord());

		//���ӷ������������жϲ���
		MYSQL *m_sqlConM = NULL;
		m_sqlConM = mysql_init(NULL);

	if (!mysql_real_connect(m_sqlConM , "localhost", "root", "199716", "User", 3306, NULL, 0))
	{
		AfxMessageBox(_T("�������ݿ�ʧ��!"));
		this->Send(&bRes,sizeof(bRes));
		return;
	}
	else
	{
		mysql_query(m_sqlConM , "SET Username 'GB2312'");//��������ݿ��ж�ȡ���ݺ���������ʾ������  
	}

	// ������Ӷ�Ӧ��
	string sqlstr2;
	sqlstr2 += "INSERT INTO `user`.`user_info` (`Username`, `Passward`) VALUES ('";
	sqlstr2 += user.m_aName;
	sqlstr2 += "' , '";
	sqlstr2 += user.m_aPsw;
	sqlstr2 += "');";


	MYSQL_RES *result = NULL;
    if (mysql_query(m_sqlConM , sqlstr2.c_str())) {

		CString cstr(sqlstr2.c_str());
		AfxMessageBox(cstr);

		this->Send(&bRes,sizeof(bRes));
		return;
	}
	else
	{

			bRes = 2;
			this->Send(&bRes,sizeof(bRes));
	}
		mysql_close(m_sqlConM);
}