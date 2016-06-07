#include "temper.h"
#include "helperfuncs.h"
#include "stringServer.h"

//sets temperature
void temperature::set_temperature()
{
	bool content = false;
	string s, thouHastSpoken;
	
	//loops through temperature input
	do {
		//gets user input
		stringServer::Instance()->line(input_temp);
		getline(cin, thouHastSpoken);
		cin.clear();
		cout << endl;

		//checks if input is a number
		content = is_number(thouHastSpoken);

		//if it is pass it 
		if (content == true){
			stringstream(thouHastSpoken) >> temp;
		}
		//displays error message if user input cannot be processed
		else {
			stringServer::Instance()->line(error_input_cannot_process);
			cout << endl;
		}
	//breaks out of loop if input was a number
	} while (content == false);
}

//prints the temperature
void temperature::print_temperature(){
	stringServer::Instance()->line(output_temp);
	cout << temp << "\370 " << scale << endl;
}