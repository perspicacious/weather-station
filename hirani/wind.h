#ifndef wind
#define wind

#include "inclusions.h"

//creates windy object
class windy
{
	int wspeed = 'word';
	string wdir = "";
public:
	bool is_Direction(string);
	string make_lowercase(const string);
	void set_wind();
	int get_wspeed() { return wspeed; }
	string get_wdir() { return wdir; }
	void print_wind();
};

#endif // !wind
