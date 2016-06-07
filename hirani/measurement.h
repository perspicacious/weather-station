#ifndef measurement
#define measurement

#include "inclusions.h"
#include "temper.h"
#include "wind.h"

//creates weather measurement
class measure
{
	string stationName;
	temperature t;
	windy w;
public:
	void set_name();
	string get_name() { return stationName; }
	void set_measurement();
	void print_measurement();
};

#endif // !measurement
