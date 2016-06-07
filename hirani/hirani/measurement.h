#ifndef measurement
#define measurement

#include "inclusions.h"
#include "temper.h"
#include "wind.h"

class measure // creates measurement structure
{
	temperature t;
	windy w;
public:
	void set_measurement();
	void print_measurement();
};

#endif // !measurement
