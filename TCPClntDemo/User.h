#pragma once
class User
{
public:
	User(void);
	~User(void);
public:
	User(char* strUserName,char* strPwd);

	//getºÍsetº¯Êý
	char* getUserName();
	void setUserName(char* strUserName);
	char* getPassWord();
	void setPassWord(char* strPassWord);


	char m_aName[20];
	char m_aPsw[20];

};

