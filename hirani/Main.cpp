// Karishma Hirani
// 1024042

#include "inclusions.h"
#include "stringServer.h"
#include "helperfuncs.h"
#include "station.h"

//Project 10

//runs main menu
void menu()
{
	system("color 0F");
	bool content = false, flag = false;
	string s, thouHastSpoken;
	int tick = 0, x = 0;
	vector<weatherStation> aws;
	weatherStation nws;

	//displays menu message
	stringServer::Instance()->line(menu_msg);
	cout << endl;

	//loops through menu
	do{
		//displays menu options
		stringServer::Instance()->line(menu_1_1_msg);
		cout << endl;
		stringServer::Instance()->line(menu_1_2_msg);
		cout << endl;
		stringServer::Instance()->line(menu_1_3_msg);
		cout << endl;
		stringServer::Instance()->line(menu_1_4_msg);
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
			//create a weather station
			case 1:
				nws = weatherStation();
				system("color F0");
				nws.make_name();
				nws.sub_menu();
				aws.push_back(nws);
				system("color 0F");
				break;
			//interact with a weather station if at least one exists
			case 2:
				if (aws.size() == 0)
				{
					stringServer::Instance()->line(error_no_weather);
					cout << endl;
				}
				else
					nws.modify_station(aws);
				break;
			//print the current weather from all stations even if one or more don't have weather
			case 3:
				if (aws.size() == 0)
				{
					stringServer::Instance()->line(error_no_weather);
					cout << endl;
				}
				else
					nws.print_stations(aws);
				break;
			//quit the program
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
			stringServer::Instance()->line(error_input_cannot_process);
			cout << endl;
		}
	//breaks out of loop if option 4 was selected
	} while (x != 4);
}

//runs main
int main()
{
	//sets up language for the program and returns a message for what was selected
	stringServer::Instance()->set_Language();
	stringServer::Instance()->get_Language();
	menu();

	//DONE Press 1 if you wish to create a weather station.
		//-If yes, create a weather station object, perform the menu function of that weather station object. Add that object to an array. Return to main menu of options.
	//DONE Press 2 if you wish to select a weather station to ineraction with.
		//-If yes, output the names of all weather stations and their numbers. Have the user select the matching number of the weather station they wish to use. Check user input to make sure it is a number and that it is a number which does correspond to a station (not out of bounds). If it is, then access that index of the array of stations, and access the menu for that station. *Turn the sub array of weather measurements (pmetrics) for the station class into a vector which does not need a "delete" at the end of it. It will die when the program dies. Once they press exit on that menu, the prg should break out of that object in the station array and return to the main menu. (enter that object then break; then have some flag to indicate the while is still true and the main menu should keep looping).
	//DONE Press 3 if you want to print out the current weather for all weather stations.
		//-In the array of stations, have an iteration through each object which accesses station.nmeas.print_measurement(); // in case 1 we retrieve a vector and we edit it, but we never pass that vector back to the original class. that means the original class vector is still empty. so modify and printer functions dont really do anything to it. It's also not a good idea to leave a weather station vector inside the weather station class because each time we save a weather station to a spot in the vector, it saves the whole class as an object. Which in memory would = many menus, many of the same variable (newWeatherStation) many of the same method. In reality it doesn't matter since memory addresses are all different and these will never touch each other. But! It's not good to save many copies of a vector that we never use. It wastes memory. So I've moved it outside of that class so it doesnt get saved in every instance of the object. In main we may only instantialize one object and keep recycling it. But after the end of case 1, it is saved as a copy into the vector. 
		//DONE* issue if you made a weather station, when you choose 2 to go back in and modify it, it runs the whole menu. this means the name is erased, as well as the original temperature data. This is because in my code, the sub menu refreshes tick to 0, and pmetrics, name, and size. They are then reprompted and remade... For tick it causes my if statement (tick==0?) to output an error when indeed there would already be data there. For pmetrics, all original temp data is lost... Name and size are both prompted for again when they were already there in the first place. For tick, i can just backspace that variable completely because i changed my printer to be dependent on how many records the professor wants us to show him, i get that number from him when he determines the size of the array. But i don't use size to declare the vector anymore. This means the vector is only either empty or full..This then creates an issue with my case for printing because if nothing has been entered then i will need some error check that sees there are no values in the vectorarray and outputs the corresponding error message. I solved this with pmetrics.empty()
		//DONE * issue with printing and storing in an individual weather station. Pressing 2 does print the most current weather but pressing 3 can print garbage (has to do with how we iterate through the vector. push_back is fine. Problem was in the for loops.
		//DONE * issue with printing station name. station name prints once when press 2, but then if you press 3 station name does not print. This was only a problem if garbage data was printed. Solved by solving the error above this.
		//* issue if a vector isn't as large as what the person inputs, error abort
		//DONE* issue where pressing 3 inside an individual weather station outputs values from the other weatherstations
		//DONE* if pressing 2 in main menu, the list of stations is incorrect
		//DONE* issue if you have multiple weather stations and you press 2 to interact with one, then if you add a new measurement and press 4 to return to main menu. pressing 3 on main menu doesnt show the updated value in that station. only the old one

	return 0;
}