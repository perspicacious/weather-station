#include "measurement.h"
#include "stringServer.h"

//sets name for stations
void measure::set_name()
{
	string s, thouHastSpoken;

	//displays name message
	stringServer::Instance()->line(name_msg);
	cout << endl;

	//loops through name input
	do
	{
		//gets user input
		stringServer::Instance()->line(input_name);
		getline(cin, thouHastSpoken);
		cin.clear();
		cout << endl;

		//if input is less than length of 50 characters
		if (thouHastSpoken.length() < 50)
		{
			//assign input value to station name
			stationName = thouHastSpoken;
		}
		//displays error message if the user input is too long
		else
		{
			stringServer::Instance()->line(error_input_too_long);
			cout << endl;
		}
	//breaks out of loop if station name isn't blank
	} while (stationName == "");
}

//sets a measurement
void measure::set_measurement()
{
	//sets temperature
	t.set_temperature();
	//sets wind
	w.set_wind();
}

//prints the entire measurement with station name
void measure::print_measurement()
{	
	//displays station name
	stringServer::Instance()->line(output_name);
	cout << stationName << endl;
	//displays temperature
	t.print_temperature();
	//displays wind
	w.print_wind();
	cout << endl;
}