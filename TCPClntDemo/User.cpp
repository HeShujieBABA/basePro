#include "stdafx.h"
#include "User.h"



//构造函数，无参构造函数
User::User(void)
{
	strcpy_s(m_aName, "");
	strcpy_s(m_aPsw,"");
}

User::~User(void)
{
}

User::User(char* strUserName,char* strPwd)
{
	strcpy_s(m_aName,strUserName);
	strcpy_s(m_aPsw,strPwd);
}

//get和set方法
char* User::getUserName()
{
	return m_aName;
}
void User::setUserName(char* strUserName)
{
	strcpy_s(m_aName,strUserName);
}
char* User::getPassWord()
{
	return m_aPsw;
}
void User::setPassWord(char* strPassWord)
{
	strcpy_s(m_aPsw,strPassWord);
}
