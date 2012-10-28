#pragma once
class cookie
{
public:
	cookie(char* name, char* value);
	~cookie();
	char* name;
	char* value;
};

class DomainCookies
{
public:
	DomainCookies();
	~DomainCookies();
	vector<cookie*> cookies;
	char* domain;
	void AddCookie(char* name, char* value);
	cookie* FindCookie(char* name);
};

class websocket
{
public:
	websocket();
	~websocket();
	bool Connect(char* server,char* port);
	void Disconnect();
	char* URLDecode(char* src);
//private:
	vector<DomainCookies*> Cookies;
	bool is_connected;
	char* Request(char* data,int datalen);
	void GetCookies(char* data, char* domain=NULL);
	void AddLog(char* logtext, bool msg=0);
	DomainCookies* FindCookies(char*domain);
	void AddCookie(char* name, char* value,char* domain=NULL);
	CEdit* log;
	SOCKET conn;
	char* host;
	char* port;
};
