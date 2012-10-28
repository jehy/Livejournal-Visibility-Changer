#include "stdafx.h"
#include "ljwrapper.h"
#include "md5.h"
Event::Event(char* itemid,char*security,char*subject,char*text)
{
	size_t l=strlen(itemid)+1;
	this->itemid=new char[l];
	strcpy_s(this->itemid,l,itemid);

	l=strlen(security)+1;
	this->security=new char[l];
	strcpy_s(this->security,l,security);

	l=strlen(subject)+1;
	this->subject=new char[l];
	strcpy_s(this->subject,l,subject);

	l=strlen(text)+1;
	this->text=new char[l];
	strcpy_s(this->text,l,text);
}
Event::~Event()
{
	delete(itemid);
	delete(security);
	delete(subject);
	delete(text);
}

ljwrapper::ljwrapper()
{
	user=NULL;
	password=NULL;
}
ljwrapper::~ljwrapper()
{
///	for(unsigned int i=0;i<this->Posts.size();i++)
//		delete (Posts[i]);
	if(user!=NULL)delete(user);
	if(password!=NULL)delete(password);
}


bool ljwrapper::Login(char* username,char* password, char* from)
{
	int l=(int)strlen(username)+1;
	char* c=new char[l];
	strcpy_s(c,l,username);
	if(user!=NULL)delete(user);
	user=c;

	l=(int)strlen(password)+1;
	c=new char[l];
	strcpy_s(c,l,password);
	if(this->password!=NULL)delete(this->password);
	this->password=c;

	CString query,query2;
	query.Append("POST /login.bml?ret=1 HTTP/1.1\n");
	query.Append("Host: ");query.Append(from);query.Append("\n");
	query.Append("User-Agent: Opera/9.10 (Windows NT 5.1; U; ru)\n");
	query.Append("Accept-Encoding: deflate\n");
	query.Append("Referer: ");query.Append(from);query.Append("/\n");
	query.Append("Connection: Close\n");
	query.Append("Content-Type: application/x-www-form-urlencoded\n");
	query.Append("Content-Length: ");
    query2="mode=login&user=";
	query2.Append(username);
	query2.Append("&password=");
	query2.Append(password);
	query2.Append("&remember_me=1");;

	CString f;
	f.Format("%i",query2.GetLength());
	query.Append(f);
	query.Append("\r\n\r\n");
	query.Append(query2);
	//query.Format("%s%i%s",query.GetBuffer(),query2.GetLength(),query2.GetBuffer());
	char* data=Request(query.GetBuffer(),query.GetLength());
	//n=new DomainCookies();
	if(strlen(data)>(2.5*1024))
	{
		MessageBox(NULL,"Seems like login failed","Error",MB_OK);
		delete(data);
		return 0;
	}
	else
	{
		this->AddLog("Seems like login OK");
		GetCookies(data,NULL);
		delete(data);
		return 1;
	}
}


CString GetData(char* data, char* tag)
{
	CString d=data;
	CString t=tag;
	int k=d.Find(t);
	if(k==-1){d="";return d;}
	k=d.Find("\n",k+t.GetLength());
	if(k==-1){d="";return d;}
	int k2=d.Find("\n",k+1);
	if(k2==-1){d="";return d;}
	d=d.Mid(k+1,k2-k-1);
	return d;
}
bool ljwrapper::LoginToDomain(char* domain)
{
CString query="GET /misc/get_domain_session.bml?return=http://";
query.Append(domain);
query.Append(".livejournal.com/ HTTP/1.1\n");
query.Append("Host: ");
query.Append(this->host);
query.Append("\n");
query.Append("User-Agent: Opera/9.10 (Windows NT 5.1; U; ru)\n");
query.Append("Accept-Encoding: deflate\n");
query.Append("Connection: close\n");
query.Append("Cookie: ");
DomainCookies* cook=this->FindCookies(NULL);
if(cook==NULL)
{
	MessageBox(NULL,"No main site cookie available!","Error",MB_OK);
	return 0;
}
else
{
	for(unsigned int i=0;i<cook->cookies.size();i++)
	{
		query.Append(cook->cookies[i]->name);
		query.Append("=");
		query.Append(cook->cookies[i]->value);
		query.Append("; ");
	}
	query.Append("\r\n\r\n");
	char* data=Request(query.GetBuffer(),query.GetLength());
	query=data;
	int k=query.Find("&k=");
	int v=query.Find("&v=",k);
	int v2=query.Find("\n",v);
	int l=v-k-2;
	char* name=new char[l];
	strcpy_s(name,l,query.Mid(k+3,(v-k-3)));
	l=v2-v-2;
	query=query.Mid(v+3,(v2-v-3));
	char* value=URLDecode(query.GetBuffer());
	this->AddCookie(name,value,domain);
	delete(data);
	delete(name);
	delete(value);
	this->AddLog("Seems like login to domain OK");
	return 1;
}
}



bool ljwrapper::ChangePostsVisibility(int how,int fromday,int frommonth,int fromyear,int today,int tomonth,int toyear)
{

int day=fromday;
int month=frommonth;
int year=fromyear;

if(!LoginToDomain(user))
{
	MessageBox(NULL,"No user site cookie available!\n Did you press 'Login' button? ;)","Error",MB_OK);
	return 0;
}
while(true)
{
	CString date;
	date.Format("Checking data for %i-%i-%i",day,month,year);
	AddLog(date.GetBuffer());
	date.Format("&day=%i&month=%i&year=%i",day,month,year);
CString query="POST /interface/flat HTTP/1.1\nContent-type: application/x-www-form-urlencoded\nConnection: close\nUser-Agent: Semagic 1.7.3.3U\nHost: ";
query.Append(this->host);
query.Append("\nContent-Length: ");
	CString query2="lineendings=dots&mode=getevents&prefersubject=0&noprops=1&selecttype=day"+date+"&howmany=50&user=";
	query2.Append(this->user);
	query2.Append("&ver=1&hpassword=");
	char* md5=MD5String(this->password);
	query2.Append(md5);
	delete(md5);
	CString len;
	len.Format("%i",query2.GetLength());
	len.Append("\nCache-Control: no-cache\r\n\r\n");
	query.Append(len);
	query.Append(query2);
	if(!this->Connect(host,port))
	{
		MessageBox(NULL,"Could not connect!","Error",MB_OK);
		return 0;
	}
	char* data=Request(query.GetBuffer(),query.GetLength());
	//bool res=GetPosts(data);
	//AddLog(data);
	CString d=GetData(data,"events_count");
	CString l=d;
	l.Append(" events got");
	AddLog(l.GetBuffer());
	vector<Event*> Events;
	int z=atoi(d.GetBuffer());
	for(int i=1;i<=z;i++)
	{
		CString id,subj,text,sec;
		id.Format("events_%i_itemid",i);
		subj.Format("events_%i_subject",i);
		text.Format("events_%i_event",i);
		sec.Format("events_%i_security",i);
		id=GetData(data,id.GetBuffer());
		sec=GetData(data,sec.GetBuffer());
		subj=GetData(data,subj.GetBuffer());
		text=GetData(data,text.GetBuffer());
		//DAMNED BASTARDS! THEY REPLACE \n with "+...+" !!!
		text.Replace("+...+","\n");
		Event* ev=new Event(id.GetBuffer(),sec.GetBuffer(),subj.GetBuffer(),text.GetBuffer());
		Events.push_back(ev);
		d.Format("Got event# %i",i);
		AddLog(d.GetBuffer());
		d="Event topic - '"+subj+"'";
		AddLog(d.GetBuffer());
	}
	AddLog("Got all events :)");
	delete(data);

	for(unsigned int i=0;i<Events.size();i++)
	{
		query="POST /interface/flat HTTP/1.1\nContent-type: application/x-www-form-urlencoded\nConnection: close\nUser-Agent: Semagic 1.7.3.3U\nHost:  ";
		query.Append(this->host);
		query.Append("\nContent-Length: ");
		query2="mode=editevent&subject=";
		query2.Append(Events.at(i)->subject);
		if(how==0)
			query2.Append("&security=public");
		else if(how==1)
			query2.Append("&security=usemask&allowmask=1");//FRIENDS security level
		else if(how==2)
			query2.Append("&security=private");//Private security level
		
		query2.Append("&event=");
		query2.Append(Events.at(i)->text);
		query2.Append("&user=");
		query2.Append(this->user);
		query2.Append("&ver=1&hpassword=");
		char* md5=MD5String(this->password);
		query2.Append(md5);
		delete(md5);
		query2.Append("&itemid=");
		query2.Append(Events.at(i)->itemid);
		CString len;
		len.Format("%i",query2.GetLength());
		len.Append("\nCache-Control: no-cache\r\n\r\n");
		query.Append(len);
		query.Append(query2);
		this->Disconnect();
		this->Connect(host,port);
		char* data=Request(query.GetBuffer(),query.GetLength());
		if(strcmp((GetData(data,"success").GetBuffer()),"OK")==0)
			AddLog("Entry edited OK");
		else
			AddLog("Entry edit FAILED");
		delete(data);

	}
	AddLog("edited all events for date:)");
	for(unsigned int i=0;i<Events.size();i++)
		delete(Events[i]);
	//counter
	if((day>=today)&&(month==tomonth)&&(year==toyear))break;
	if((year>toyear)||(year==toyear)&&(month>tomonth))break;
	if(day<31)day++;
	else 
	{
		day=1;
		if(month<12)
			month++;
		else
		{
			month=1;
			year++;
		}
	}
}
		AddLog("edited all events:)");
		return 1;
}