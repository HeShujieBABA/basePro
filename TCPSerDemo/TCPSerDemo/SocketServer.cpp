// SocketServer.cpp : 实现文件
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


// SocketServer 成员函数


void SocketServer::OnReceive(int nErrorCode)
{
	//用来接收，先接收传过来的TCP通讯协议
	int msgType; //定义一个用来接收的协议
	this->Receive(&msgType,sizeof(msgType)); //开始接收
	switch(msgType) //将接收来的协议，分类处理
	{
	case MSG_LOGIN: //登录协议
		{
			DoLogin(); //自己编写的一个成员函数
		}
		break;
	case MSG_REGISTER: //注册协议
		{
			//Register(); 
			DoRegister();
		}
		break;
	case MSG_TEXT: //查询协议
		{

		}
		break; 
	case MSG_PIC: //保存协议
		{

		}
		break;
	}

	CSocket::OnReceive(nErrorCode);
}

	//检验登录
	/*********************************
	函数名：Login
	函数描述：检验登录并发送登录是否成功的内容给客户端
	参数：无
	返回值：无
	**********************************/
	void SocketServer::DoLogin(void)
	{
		//bool bRes = false;  //用于给客户端发送内容的变量，初始化为false
		int bRes = 0;
		User userInfo ;
		//用来判断接收的数据是否正确
		if (this->Receive(&userInfo,sizeof(User)) != sizeof(User))
		{
			//如果接受失败，就发送内容，此时bRes的值为false
			this->Send(&bRes,sizeof(bRes));
			return ;
		}


		User user;
		strcpy_s(user.m_aName,userInfo.getUserName());
		strcpy_s(user.m_aPsw,userInfo.getPassWord());

		//连接服务器，进行判断操作
		MYSQL *m_sqlCon = NULL;
		m_sqlCon = mysql_init(NULL);
	// localhost:服务器 root/123456为账号密码 managesystemdb为数据库名 3306为端口    
	if (!mysql_real_connect(m_sqlCon, "localhost", "root", "199716", "User", 3306, NULL, 0))
	{
		AfxMessageBox(_T("访问数据库失败!"));
		this->Send(&bRes,sizeof(bRes));
	}
	else
	{
		mysql_query(m_sqlCon, "SET Username 'GB2312'");//解决从数据库中读取数据后汉字乱码显示的问题  
	}
	// 查询对应的用户名所对应的行
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
	    //一次性取得数据集
		result = mysql_store_result(m_sqlCon);
		//取得并打印行数
        int rowcount = mysql_num_rows(result);

		if (rowcount == 1 )
		{
			//获取对应数据的行
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);

			//进行判断密码是否匹配
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
	//注册功能
	/*********************************
	函数名：Doregister
	函数描述：进行注册并传递给客户端注册成功的信息
	参数：无
	返回值：无
	**********************************/
	void SocketServer::DoRegister(void)
	{
		//bool bRes = false;  //用于给客户端发送内容的变量，初始化为false
		int bRes = 0;
		User userInfo ;
		//用来判断接收的数据是否正确
		if (this->Receive(&userInfo,sizeof(User)) != sizeof(User))
		{
			//如果接受失败，就发送内容，此时bRes的值为false
			this->Send(&bRes,sizeof(bRes));
			return ;
		}
		User user;
		strcpy_s(user.m_aName,userInfo.getUserName());
		strcpy_s(user.m_aPsw,userInfo.getPassWord());

		//连接服务器，进行判断操作
		MYSQL *m_sqlConM = NULL;
		m_sqlConM = mysql_init(NULL);

	if (!mysql_real_connect(m_sqlConM , "localhost", "root", "199716", "User", 3306, NULL, 0))
	{
		AfxMessageBox(_T("访问数据库失败!"));
		this->Send(&bRes,sizeof(bRes));
		return;
	}
	else
	{
		mysql_query(m_sqlConM , "SET Username 'GB2312'");//解决从数据库中读取数据后汉字乱码显示的问题  
	}

	// 进行添加对应行
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