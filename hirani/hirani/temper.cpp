#include "temper.h"
#include "helperfuncs.h"

// checks if input is a number (can be signed)
bool temperature::is_number(const string q)
{
	string::const_iterator it = q.begin();
	if (q[0] == '-' || q[0] == '+'){
		it++;
	}
	while (it != q.end() && isdigit(*it)){
		++it;
	}
	return !q.empty() && it == q.end();
}

// checks if input is a temperature // is_number // saves it to the variable
void temperature::set_temperature()
{
	bool content = false;
	string s, thouHastSpoken;

	cout << string(50, '\n');
	do {
		s = "\nPlease enter the temperature in farenheit using the number keys on your keyboard: ";
		OutputText(s);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		getline(cin, thouHastSpoken);//Get user input
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		content = is_number(thouHastSpoken); //checks if user input is a number
		if (content == true){ //if userinput is a number, transfer it to temperature.
			stringstream(thouHastSpoken) >> temp;
		}
		/*else if (thouHastSpoken == "exit"){ //if userinput is 'exit' break out and return to menu
			break;
		}*/
		else {
			cin.clear();
			s = "Have mercy great ruler we cannot process this information!\n";
			OutputText(s);
		}
	} while (content == false);
}

void temperature::print_temperature(){
	cout << "Temperature: " << temp << " " << scale << endl;
}