// Karishma Hirani
// 1024042

#include "inclusions.h"
#include "stringServer.h"
#include "helperfuncs.h"
#include "measurement.h"
#include "temper.h"
#include "wind.h"
#include "station.h"

//runs the option to interact with a particular weather station
void weatherStation::modify_station(vector<weatherStation>& aws)
{
	string thouHastSpoken;
	bool content = false;
	int i = 0;
	
	//initiates list of created stations with matching numbers and gives user option to choose one to interact with.
	for (vector<weatherStation>::iterator it = aws.begin(); it != aws.end(); it++, i++)
	{
		weatherStation cws = *it;
		cout << "    " << i << " " << cws.nmeas.get_name() << endl;
	}

	//loops through station input
	do{
		//gets user input
		stringServer::Instance()->line(input_menu_1_2);
		getline(cin, thouHastSpoken);
		cin.clear();
		cout << endl;

		//checks if input is a number
		content = is_number(thouHastSpoken);

		//if it is a number and it's within the vector of stations, run the submenu for that station
		if (content == true){
			stringstream(thouHastSpoken) >> i;
			if (i >= 0 && i < aws.size()){
				system("color F0");
				cout << "		" << aws[i].nmeas.get_name() << endl;
				aws[i].sub_menu();
				system("color 0F");
			}
			else{
				content = false;
			}
		}
	//breaks loop if input was a number
	} while (content == false);
}

//runs printer for current weather of all created stations
void weatherStation::print_stations(vector<weatherStation> aws)
{
	//displays all weather message
	stringServer::Instance()->line(all_weather_msg);
	cout << endl;

	int i = 0;
	//iterates through the weather stations to print their most current measurement
	for (vector<weatherStation>::iterator it = aws.begin(); it != aws.end(); it++, i++)
	{
		weatherStation cws = *it;
		if (cws.get_history().size() > 0)
		{
			cws.nmeas.print_measurement();
		}
		else if (cws.get_history().size() == 0)
		{
			cout << endl;
			stringServer::Instance()->line(output_name);
			cout << cws.nmeas.get_name() << endl;
			stringServer::Instance()->line(error_no_history);
			cout << endl;
		}
			
	}
}

//prints weather measurements
void weatherStation::printer(bool& flag)
{
	//prints most current measurement
	if (flag == false)
	{
		nmeas.print_measurement();
	}
	//prints history of measurements
	else
	{
		for (int i = pmetrics.size()-1; i > -1; i--)
		{
				nmeas = pmetrics[i];
				nmeas.print_measurement();
		}
	}
}

//sets a name for the weather station
void weatherStation::make_name()
{
	nmeas.set_name();
}

//runs the submenu of options
void weatherStation::sub_menu()
{
	bool content = false, flag = false;
	string thouHastSpoken;
	int x = 0;
	
	//loops through submenu
	do{
		stringServer::Instance()->line(menu_2_1_msg);
		cout << endl;
		stringServer::Instance()->line(menu_2_2_msg);
		cout << endl;
		stringServer::Instance()->line(menu_2_3_msg);
		cout << endl;
		stringServer::Instance()->line(menu_2_4_msg);
		cout << endl;
		
		//gets user input
		stringServer::Instance()->line(input_menu);
		getline(cin, thouHastSpoken);
		cin.clear();
		cout << endl;

		//checks if input is a number
		content = is_number(thouHastSpoken);

		//if it is, enter the switch statement
		if (content == true)
		{
			stringstream(thouHastSpoken) >> x;
			switch (x){
			//enter weather reading
			case 1:
				nmeas.set_measurement();
				pmetrics.push_back(nmeas);
				break;
			//print the reading
			case 2:
				if (pmetrics.empty())
				{
					stringServer::Instance()->line(error_no_weather);
					cout << endl;
				}
				else
				{
					printer(flag);
				}
				break;
			//print the history of readings
			case 3:
				if (pmetrics.empty())
				{
					stringServer::Instance()->line(error_no_weather);
					cout << endl;
				}
				else
				{
					flag = true;
					printer(flag);
					flag = false;
				}
				break;
			//quit the station
			case 4:
				break;
			//displays error message if user input doesn't match any of the cases
			default:
				stringServer::Instance()->line(error_input_wrong_number);
				cout << endl;
			}
		}
		//displays error message if user input cannot be processed
		else {
			cin.clear();
			stringServer::Instance()->line(error_input_cannot_process);
			cout << endl;
		}
	//breaks out of loop if option 4 was selected
	} while (x != 4);
}