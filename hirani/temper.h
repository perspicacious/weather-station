#ifndef temper
#define temper

#include "inclusions.h"

//creates temperature object
class temperature
{
	int temp = 'word';
	string scale = "Fahrenheit";
public:
	void set_temperature();
	int get_temperature() { return temp; }
	string get_scale() { return scale; }
	void print_temperature();
};

#endif // !temper
