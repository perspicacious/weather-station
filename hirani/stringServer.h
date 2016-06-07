#include "inclusions.h"

//creates StringServer object
class stringServer
{
	int lang = 0;
	string println, filename;
	string fLines[1000];
public:
	static stringServer* Instance();
	~stringServer();
	void set_Language();
	int get_lang() { return lang; }
	void get_Language();
	void line(int);
private:
	stringServer(){};
	static stringServer* m_pInstance;
};

