#include "wind.h"
#include "helperfuncs.h"
#include "inclusions.h"

// checks if input is a number (can be signed)
bool windy::is_number(const string q)
{
	string::const_iterator it = q.begin();
	if (q[0] == '-' || q[0] == '+'){
		it++;
	}
	while (it != q.end() && isdigit(*it)){
		++it;
	}
	return !q.empty() && it == q.end();
}//*
bool windy::is_Direction(string w)// makes the string lowercase in order to pass to the function that checks wind direction
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
string windy::make_lowercase(const string in)// makes a given string lowercase and returns it in the lowercase format
{
	string out;

	transform(in.begin(), in.end(), back_inserter(out), tolower);
	return out;
}
void windy::set_wind()
{
	bool content = false;
	string s, thouHastSpoken;

	cout << string(50, '\n');
	do
	{
		s = "\nPlease enter the wind speed to the nearest whole number: ";
		OutputText(s);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		getline(cin, thouHastSpoken);//Get user input
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		content = is_number(thouHastSpoken); //checks if user input is a number
		if (content == true)
		{ //if userinput is a number, transfer it to wind speed.
			stringstream(thouHastSpoken) >> wspeed;
			if (wspeed < 0)
			{
				wspeed = NULL;
				content = false;
				s = "Have mercy great ruler we cannot process this information!\n";
				OutputText(s);
			}
		}
		else
		{
			cin.clear();
			s = "Have mercy great ruler we cannot process this information!\n";
			OutputText(s);
		}
	} while (content == false);


	content = false;

	cout << string(50, '\n');
	do {
		s = "\nPlease enter the wind direction using any of the 4 cardinal or the 4 intercardinal directions (example-northeast): ";
		OutputText(s);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		getline(cin, thouHastSpoken);//Get user input
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		content = is_Direction(thouHastSpoken); //checks if user input contains whole cardinal words
		if (content == true){ //if userinput passes the check, transfer it to wind direction
			stringstream(thouHastSpoken) >> wdir;
		}
		else {
			cin.clear();
			s = "Have mercy great ruler we cannot process this information!\n";
			OutputText(s);
		}
	} while (content == false);

}
void windy::print_wind()
{
	cout << "Wind: " << wspeed << " " << wdir << endl;
}