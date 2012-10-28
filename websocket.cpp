#include "StdAfx.h"
#include "websocket.h"
cookie::cookie(char* name, char* value)
{
		size_t l=strlen(name)+1;
		size_t l1=strlen(value)+1;

		this->name=new char[l];
		this->value=new char[l1];

		strcpy_s(this->name,l,name);
		strcpy_s(this->value,l1,value);
}
cookie::~cookie()
{
	delete(name);
	delete(value);
}

DomainCookies::DomainCookies()
{
	domain=NULL;
}
DomainCookies::~DomainCookies()
{
	for(unsigned int i=0;i<cookies.size();i++)
		delete (cookies[i]);
	if(domain!=NULL)
		delete(domain);
}

cookie* DomainCookies::FindCookie(char* name)
{
	for(unsigned int i=0;i<cookies.size();i++)
		if(strcmp(cookies[i]->name,name)==0)
			return cookies[i];
	return NULL;
}

void DomainCookies::AddCookie(char* name, char* val)
{
	cookie* c=FindCookie(name);
	if(c==NULL)
	{
		cookie* n=new cookie(name,val);
		cookies.push_back(n);
	}
}

websocket::websocket()
{
	log=NULL;
	is_connected=false;
	host=NULL;
	port=NULL;
}

websocket::~websocket()
{
	for(unsigned int i=0;i<this->Cookies.size();i++)
		delete (Cookies[i]);
	if(host!=NULL)delete(host);
	if(port!=NULL)delete(port);
	Disconnect();
}


DomainCookies* websocket::FindCookies(char*domain)
{
	if(domain==NULL)
	{
		for(unsigned int i=0;i<this->Cookies.size();i++)
			if(Cookies[i]->domain==NULL)
				return Cookies[i];
	}
	else
	{
		for(unsigned int i=0;i<this->Cookies.size();i++)
			if(Cookies[i]->domain!=NULL)
				if(strcmp(domain,Cookies[i]->domain)==0)
					return Cookies[i];
	}
	return NULL;
}

void websocket::AddCookie(char *name, char *value, char *domain)
{
	DomainCookies* c=FindCookies(domain);
	if(c==NULL)
	{
		c=new DomainCookies();
	
		int l;
		if(domain==NULL)
			c->domain=NULL;
		else
		{
			l=(int)strlen(domain)+1;
			c->domain=new char[l];
			strcpy_s(c->domain,l,domain);
		}
		Cookies.push_back(c);
	}
	c->AddCookie(name,value);
//	return NULL;
}


void websocket::AddLog(char* logtext, bool msg)
{int min,max;
	if(log!=NULL)
	{
		CString temp;
		log->GetWindowTextA(temp);
		temp.Append("\r\n");
		temp.Append(logtext);
		log->SetWindowTextA(temp);
		//log->GetScrollRange(SB_VERT,&min,&max);   
		//log->SetScrollPos(SB_VERT,max,1);
		//log->SetSel(5000000);
		log->LineScroll(1000);
		//log->RedrawWindow();
		//log->GetParent->
	}
	if(msg)MessageBox(NULL,logtext,"SysMsg",MB_OK);
}

bool websocket::Connect(char* serv,char* text_port)
{
	WSADATA wsaData;
	struct hostent *hp;
	unsigned int addr;
	struct sockaddr_in server;
	int wsaret=WSAStartup(0x101,&wsaData);
	if(wsaret)
	{
        AddLog("Could not init winsock");
		return 0;
	}
	conn=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(conn==INVALID_SOCKET)
	{
		AddLog("Could not create winsock");
		return 0;
	}
	addr=inet_addr(serv);
	if(addr==INADDR_NONE)
		hp=gethostbyname(serv);
	else
		hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
	if(hp==NULL)
	{
			closesocket(conn);
			AddLog("Could not find host");
			return 0;
	}
	server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
	server.sin_family=AF_INET;
	server.sin_port=htons((u_short)strtod(text_port,NULL));
	if(connect(conn,(struct sockaddr*)&server,sizeof(server)))
	{
			closesocket(conn);
			AddLog("Could not connect to host");
			return 0;
	}
	this->is_connected=true;
	AddLog("Connected to server");

	//We make it in such a weird manner because this class's host&port can be given as arguments - and it becomes funny ^_^'
	int l=(int)strlen(serv)+1;
	char* c=new char[l];
	strcpy_s(c,l,serv);
	delete(this->host);
	this->host=c;

	l=(int)strlen(text_port)+1;
	c=new char[l];
	strcpy_s(c,l,text_port);
	delete(this->port);
	this->port=c;
	return 1;
}

char* websocket::Request(char* data,int datalen)
{
	int s=send(conn,data,datalen,0);//
	if(s==SOCKET_ERROR)
	{
		s=GetLastError();
		AddLog("Data not sent!");
	}
	else
		AddLog("Request data sent!");
	char* buf=new char[1024];
	CString received;
	int y;
	CString temp;
	while(true)
	{
		y=recv(conn,buf,1024,0);
		temp.Format("%i bytes received",y);
		AddLog(temp.GetBuffer());
		if(y==SOCKET_ERROR)
		{
			AddLog("Socket error sending request");
			break;
		}
		if(y==0)
			break;
		else
			received.Append(buf,y);
	}
	delete(buf);
	int z=received.GetLength()+1;
	char* ret=new char[z];
	strcpy_s(ret,z,received.GetBuffer());
	return ret;
}

void websocket::GetCookies(char* data, char* domain)
{
	DomainCookies* c=new DomainCookies();
	int l;
	if(domain==NULL)
		c->domain=NULL;
	else
	{
		l=(int)strlen(domain)+1;
		c->domain=new char[l];
		strcpy_s(c->domain,l,domain);
	}
	Cookies.push_back(c);

	CString cookieStr,cook,val,name;
	cookieStr=data;
	int z,k=0,n;
	while(z=cookieStr.Find("Set-Cookie",k))
	{
		if(z==-1)break;
		k=cookieStr.Find("\n",z);
		cook=cookieStr.Mid(z+12,(k-z-12));

		n=cook.Find("=");
		name=cook.Left(n);
		//AddLog(name.GetBuffer());
		l=cook.Find(";");
		val=cook.Mid(n+1,(l-n-1));
		//AddLog("=");
		//AddLog(val.GetBuffer());
		c->AddCookie(name.GetBuffer(),val.GetBuffer());
	}
}

void websocket::Disconnect()
{
	closesocket(conn);
	WSACleanup();
	this->is_connected=false;
	AddLog("Disconnected from server");
}

char* websocket::URLDecode(char* src)
{
	unsigned long ascii;
	CString s;
	unsigned int i=0;
	char code[3]={0};
	while(i<strlen(src))
	{
		if(src[i]=='%')
		{
			memcpy(code, &src[i+1], 2);
			ascii = strtoul(code, NULL, 16);
			s.AppendChar((char)ascii);
			i+=3;
		}
		else 
		{
			s.AppendChar(src[i]);
			i++;
		}
	}
	i=s.GetLength()+1;
	char* res=new char[i];
	strcpy_s(res,i,s.GetBuffer());
	return res;
}