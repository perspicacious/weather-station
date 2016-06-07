#ifndef wind
#define wind

#include "inclusions.h"

class windy // creates wind structure
{
	int wspeed = 'word';
	string wdir = "";
public:
	bool is_number(const string);
	bool is_Direction(string);
	string make_lowercase(const string);
	void set_wind();
	int get_wspeed() { return wspeed; }
	string get_wdir() { return wdir; }
	void print_wind();
};

#endif // !wind
