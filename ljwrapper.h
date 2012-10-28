#include "websocket.h"
class Event
{
public:
	Event(char* itemid,char*security,char*subject,char*text);
	~Event();
	char* itemid;
	char*security;
	char*subject;
	char*text;
};
class ljwrapper : public websocket
{
public:
	ljwrapper();
	~ljwrapper();
	bool ChangePostsVisibility(int how,int fromday,int frommonth,int fromyear,int today,int tomonth,int toyear);
	bool Login(char* username,char* password, char* from);
	//bool Hate();
	bool GetMyPosts(int Skip=0);
private:
	//bool GetPosts(char* data);
	//vector<Post*> Posts;
	bool LoginToDomain(char* domain);
	//bool GetFriendsPosts(int Skip=0);
	//void AddPost(int type,char* name, int id);
	char* user;
	char* password;
};

