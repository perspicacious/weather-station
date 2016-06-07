#include "measurement.h"

void measure::set_measurement()
{
	t.set_temperature();
	w.set_wind();
}

void measure::print_measurement()
{	
	t.print_temperature();
	w.print_wind();
}