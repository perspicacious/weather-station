#include "wind.h"
#include "helperfuncs.h"
#include "inclusions.h"
#include "stringServer.h"

//compares a given string with a list of directions and returns true if it's a match
bool windy::is_Direction(string w)
{
	string wordsToFind[8] =
	{ "north", "south", "west", "east", "northeast", "northwest", "southwest", "southeast" };

	string test = make_lowercase(w);

	bool answer;
	for (int i = 0; i < 8; i++)
	{
		if (test == wordsToFind[i]){
			answer = true;
			break;
		}
		else{
			answer = false;
		}
	}
	return answer;
}

//makes a given string lowercase and returns it
string windy::make_lowercase(const string in)
{
	string out;

	transform(in.begin(), in.end(), back_inserter(out), tolower);
	return out;
}

//sets wind
void windy::set_wind()
{
	bool content = false;
	string s, thouHastSpoken;

	//loops through windspeed input
	do
	{
		//gets user input
		stringServer::Instance()->line(input_wind_speed);
		getline(cin, thouHastSpoken); //get user input
		cin.clear();
		cout << endl;

		//checks if input is a number
		content = is_number(thouHastSpoken);

		//if it is pass it 
		if (content == true)
		{
			stringstream(thouHastSpoken) >> wspeed;
			if (wspeed < 0)
			{
				wspeed = NULL;
				content = false;
				stringServer::Instance()->line(error_input_cannot_process);
				cout << endl;
			}
		}
		//displays error message if user input cannot be processed
		else
		{
			stringServer::Instance()->line(error_input_cannot_process);
			cout << endl;
		}
	//breaks out of loop if input was a number
	} while (content == false);

	//sets content to false again
	content = false;

	//loops through wind direction input
	do {
		//gets user input
		stringServer::Instance()->line(input_wind_direction);
		getline(cin, thouHastSpoken);
		cin.clear();
		cout << endl;

		//checks if input is a direction
		content = is_Direction(thouHastSpoken);

		//if it is pass it
		if (content == true){
			stringstream(thouHastSpoken) >> wdir;
		}
		//displays error message if user input cannot be processed
		else {
			cin.clear();
			stringServer::Instance()->line(error_input_cannot_process);
			cout << endl;
		}
	//breaks out of loop if input was a direction
	} while (content == false);

}

//prints the wind
void windy::print_wind()
{
	stringServer::Instance()->line(output_wind);
	cout << wspeed << " " << wdir << endl;
}