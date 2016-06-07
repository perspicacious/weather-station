#ifndef temper
#define temper

#include "inclusions.h"

class temperature
{
	int temp = 'word';
	string scale = "Fahrenheit";
public:
	bool is_number(const string);
	void set_temperature();
	int get_temperature() { return temp; }
	void print_temperature();
};

#endif // !temper
