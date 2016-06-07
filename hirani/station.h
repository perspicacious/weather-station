#ifndef station
#define station

#include "inclusions.h"
#include "measurement.h"

//creations weather station object
class weatherStation
{
	measure nmeas;
	vector<measure> pmetrics;
public:
	int determineSize();
	void printer(bool&);
	void make_name();
	vector<measure> get_history(){ return pmetrics; }
	void sub_menu();
	void print_stations(vector<weatherStation>);
	void modify_station(vector<weatherStation>&);
};

#endif // !station
