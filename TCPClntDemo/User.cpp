#include "stdafx.h"
#include "User.h"



//���캯�����޲ι��캯��
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

//get��set����
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
