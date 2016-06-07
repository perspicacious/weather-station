// Karishma Hirani
// 1024042

#include "inclusions.h"
#include "helperfuncs.h"
#include "measurement.h"
#include "temper.h"
#include "wind.h"

//Project 7

// checks if input is a name and enters it into station name if it is
string name()
{
	string s;
	string thouHastSpoken;
	string stationName;

	do
	{
		s = "\nName: ";
		OutputText(s);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		getline(cin, thouHastSpoken);//Get user input
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		if (thouHastSpoken.length() < 50)//Checks length of string to see if it's too long. If it is under the projected length, enter the menu loop with instructions.
		{
			stationName = thouHastSpoken; //Initializes stationName with the userinput
		}
		else //general error message displays if the user input for the station name is too long
		{
			s = "Your words are far too long for us to read!";
			OutputText(s);
		}
	} while (stationName == ""); //keeps looping the station name question if station name is still blank

	return stationName;
}

// checks if input is a number (can be signed)
bool is_number(const string& q)
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

// determines size of the array // is_number // returns number if it is
int determineSize()
{
	bool content = false;
	string s;
	string thouHastSpoken;
	int size;

	do {
		s = "\nPlease enter a number between 1 and 50.\nSize: ";
		OutputText(s);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		getline(cin, thouHastSpoken);//Get user input
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		content = is_number(thouHastSpoken); //checks if user input is a number
		if (content == true){ //if userinput is a number, transfer it to size.
			stringstream(thouHastSpoken) >> size;
			if (size < 1 || size > 50){
				size = 0;
				content = false;
				s = "Have mercy great ruler we cannot process this information!\n";
				OutputText(s);
			}
			else {
				return size;
			}
		}
		else {
			cin.clear();
			s = "Have mercy great ruler we cannot process this information!\n";
			OutputText(s);
		}
	} while (content == false);
}

// populates the array
void populate(measure nmeas, measure pmetrics[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		pmetrics[i] = pmetrics[i + 1];
	}
	pmetrics[size - 1] = nmeas;
	
}

// prints the weather measurements 
void printer(string name, measure nmeas, measure pmetrics[], bool& flag, int size, int tick)
{
	string complete;
	if (flag == false)
	{
		cout << name << endl;
		nmeas.print_measurement();
		/*complete = "\nWeather Station: " + name + "\nCurrent temperature: " + to_string(nmeas.t.temp) + "\370 " + nmeas.t.scale + "\nCurrent windspeed and direction: " + to_string(nmeas.w.wspeed) + " " + nmeas.w.wdir + "\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << complete;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);*/

	}
	else
	{
		cout << name << endl;
		for (int i = size - 1; i >= 0; i--)
		{
			if (i > tick)
			{
				nmeas = pmetrics[i];
				nmeas.print_measurement();
			}/*complete = "\nWeather Station: " + name + "\nCurrent temperature: " + to_string(pmetrics[i].t.temp) + "\370 " + pmetrics[i].t.scale + "\nCurrent windspeed and direction: " + to_string(pmetrics[i].w.wspeed) + " " + pmetrics[i].w.wdir + "\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			cout << complete;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			flag = false;*/
		}
	}
}

// runs the menu of options
void menu(string name, int size, temperature& ntemp, windy& nwind, measure& nmeas, measure pmetrics[])
{
	bool content = false;
	string s;

	string thouHastSpoken;
	int tick = size - 1, x = 0;
	bool flag = false;

	do{
		s = "    1 -- input a complete weather reading\n    2 -- print your information\n    3 -- Print weather history\n    4 -- Exit the program\n\nEnter 1, 2, 3, or 4: ";
		OutputText(s);//Start the menu for the first time
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		getline(cin, thouHastSpoken);//Get user input
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cin.clear();
		content = is_number(thouHastSpoken); //Checks what has been entered to see if it's a number. If it is, enter the switch statement. If it's not a number, 
		if (content == true)
		{//if user input is a number, enter the switch statement providing the menu options that correspond with that they input
			stringstream(thouHastSpoken) >> x;
			switch (x){
			case 1: // enter weather reading
				nmeas.set_measurement();
				/*if (thouHastSpoken == "exit"){ //if userinput is 'exit' break out and return to menu
					{break;}*/
				populate(nmeas, pmetrics, size);
				tick--;
				break;
			case 2: // print the reading
				if (tick == 0)
				{
					s = "\nGreat One, you have not entered all of the information. Please select a menu option to enter the corresponding information or press 3, to exit this application.\n";
					OutputText(s);
				}
				else
				{
					printer(name, nmeas, pmetrics, flag, size, tick);
				}
				break;
			case 3: // print the history of readings
				if (tick == 0)
				{
					s = "\nGreat One, you have not entered all of the information. Please select a menu option to enter the corresponding information or press 3, to exit this application.\n";
					OutputText(s);
				}
				else
				{
					flag = true;
					printer(name, nmeas, pmetrics, flag, size, tick);
				}
				break;
			case 4: // quit the program
				s = "\nThank you for gracing us with your brilliance, merciful ruler!";
				OutputText(s);
				break;
			default: //general error message if the user input doesnt match any of the cases
				s = "\nI apologise merciful one, but we require any of the following numbers 1, 2, 3, or 4 from you in order to select a menu option.\n";
				OutputText(s);
			}
		}
		else {
			cin.clear();
			s = "Have mercy great ruler we cannot process this information!\n"; //general error message if the user input is not a number
			OutputText(s);
		}
	} while (x != 4); //checks to see if the menu option is 4, if not keep looping back into the menu
	s = "\n\nYou have exited. We will delete the history of readings you have asked us to store. It may take a few moments.";
	OutputText(s);
}

int main()
{
	string s;

	//Welcome
	s = "   Welcome to the weather station app!\nYou are our mighty overlord and saviour. Please give this weather station a name that is less than 50 characters, O great ruler!";
	OutputText(s);

	string thyname = name(); //runs name function. Once evaluated, enter menu.
	cout << string(50, '\n');

	s = "   We are devoted to your service! We can store a history of weather readings containing up to 50 records. You may decide how many histories you would like us to store.";
	OutputText(s);

	int size = determineSize(); //function call

	temperature ntemp;
	windy nwind;
	measure nmeas;
	measure *pmetrics = new measure[size]; // creates an array of the type 'measurement'

	s = "Thou hast spoken! Now that you have given us a name and the amount of records you'd like to keep, we can follow through with our destiny. We will give you 4 choices. You may perform any of the following input actions by entering the corresponding number and pressing the ENTER key.\nRemember O mighty one, you must use the number keys in order to choose which option you want. I hope we have performed in a way most pleasing to you.\n"; //Introduction
	OutputText(s);

	menu(thyname, size, ntemp, nwind, nmeas, pmetrics); // passes name, size of array, all structures, and the array of measurements to the menu

	delete[] pmetrics; // deletes the history


	/*
	//Project 6.1

	// Get the console window buffer Width
	int GetBufferWidth()
	{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	int bufferWidth, result;

	result = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);

	if (result)
	{
	bufferWidth = bufferInfo.dwSize.X;
	}

	return bufferWidth;
	}

	// output text with word wrap
	void OutputText(string s)
	{
	int bufferWidth = GetBufferWidth();

	for (unsigned int i = 1; i <= s.length(); i++)
	{
	char c = s[i - 1];

	int spaceCount = 0;

	// Add whitespace if newline detected.
	if (c == '\n')
	{
	int charNumOnLine = ((i) % bufferWidth);
	spaceCount = bufferWidth - charNumOnLine;
	s.insert((i - 1), (spaceCount), ' ');			//insert space before newline break
	i += (spaceCount);							//jump forward in string to character at beginning of next line
	continue;
	}

	if ((i % bufferWidth) == 0)
	{
	if (c != ' ')
	{
	for (int j = (i - 1); j > -1; j--)
	{
	if (s[j] == ' ')
	{
	s.insert(j, spaceCount, ' ');
	break;
	}
	else spaceCount++;
	}
	}
	}
	}

	// Output string to console
	cout << s;
	}

	// makes the string lowercase in order to pass to the function that checks wind direction
	string make_lowercase(const string& in)
	{
	string out;

	transform(in.begin(), in.end(), back_inserter(out), tolower);
	return out;
	}

	// checks if a string is equivalent to a wind direction
	bool is_Direction(string w)
	{
	string wordsToFind[8] =
	{ "north", "south", "west", "east", "northeast", "northwest", "southwest", "southeast" };

	string test = make_lowercase(w);

	bool answer;
	for (int i = 0; i < 8; i++)
	{
	if (test == wordsToFind[i]){
	answer = TRUE;
	break;
	}
	else{
	answer = FALSE;
	}
	}
	return answer;
	}

	// checks if input is a number (can be signed)
	bool is_number(const string& q)
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

	// checks if input is a name and enters it into station name if it is
	string name()
	{
	string s;
	string thouHastSpoken;
	string stationName;

	do
	{
	s = "\nName: ";
	OutputText(s);
	getline(cin, thouHastSpoken);//Get user input
	if (thouHastSpoken.length() < 50)//Checks length of string to see if it's too long. If it is under the projected length, enter the menu loop with instructions.
	{
	stationName = thouHastSpoken; //Initializes stationName with the userinput
	}
	else //general error message displays if the user input for the station name is too long
	{
	s = "Your words are far too long for us to read!";
	OutputText(s);
	}
	} while (stationName == ""); //keeps looping the station name question if station name is still blank

	return stationName;
	}

	// checks if input is a temperature and enters it if it is
	void temperature(string& thouHastSpoken, int& ctemp)
	{
	bool content = FALSE;
	string s;

	cout << string(50, '\n');
	do {
	s = "\nPlease enter the temperature in farenheit using the number keys on your keyboard: ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_number(thouHastSpoken); //checks if user input is a number
	if (content == TRUE){ //if userinput is a number, transfer it to temperature.
	stringstream(thouHastSpoken) >> ctemp;
	}
	else if (thouHastSpoken == "exit"){ //if userinput is 'exit' break out and return to menu
	break;
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	// checks if input is a wind speed and enters it if it is
	void windspeed(string& thouHastSpoken, int& wspeed)
	{
	bool content = FALSE;
	string s;

	cout << string(50, '\n');
	do {
	s = "\nPlease enter the wind speed to the nearest whole number: ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_number(thouHastSpoken); //checks if user input is a number
	if (content == TRUE){ //if userinput is a number, transfer it to wind speed.
	stringstream(thouHastSpoken) >> wspeed;
	if (wspeed < 0){
	wspeed = NULL;
	content = FALSE;
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	// checks if input is a wind direction and enters it if it is
	void winddirection(string& thouHastSpoken, string& wdir)
	{
	bool content = FALSE;
	string s;

	cout << string(50, '\n');
	do {
	s = "\nPlease enter the wind direction using any of the 4 cardinal or the 4 intercardinal directions (example-northeast): ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_Direction(thouHastSpoken); //checks if user input contains whole cardinal words
	if (content == TRUE){ //if userinput passes the check, transfer it to wind direction
	stringstream(thouHastSpoken) >> wdir;
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	// creates a full reading
	string fullReading(string& stationName, int& ctemp, int& wspeed, string& wdir)
	{
	string complete = "\nWeather Station: " + stationName + "\nCurrent temperature: " + to_string(ctemp) + "\370 \nCurrent windspeed and direction: " + to_string(wspeed) + " " + wdir + "\n";
	return complete;
	}

	int determineSize()
	{
	bool content = FALSE;
	string s;
	string thouHastSpoken;
	int size;

	do {
	s = "\nPlease enter a number between 1 and 50.\nSize: ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_number(thouHastSpoken); //checks if user input is a number
	if (content == TRUE){ //if userinput is a number, transfer it to size.
	stringstream(thouHastSpoken) >> size;
	if (size < 1 || size > 50){
	size = 0;
	content = FALSE;
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	else {
	return size;
	}
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	void populate(int tempRecs[], int speedRecs[], string direcRecs[], int& ctemp, int& wspeed, string& wdir, string& complete, int& size)
	{
	for (int i = 0; i < size-1; i++)
	{
	tempRecs[i] = tempRecs[i + 1];
	speedRecs[i] = speedRecs[i + 1];
	direcRecs[i] = direcRecs[i + 1];
	}
	tempRecs[size-1] = ctemp;
	speedRecs[size - 1] = wspeed;
	direcRecs[size - 1] = wdir;
	}

	// prints the weather measurements
	void printer(int tempRecs[], int speedRecs[], string direcRecs[], string& stationName, string& complete, bool& flag, int size, int count)
	{
	if (flag == FALSE)
	{
	cout << complete;
	}
	else
	{
	for (int i = size-1; i >= 0; i--)
	{
	if (i >= size-count)
	{
	cout << "\nWeather Station: " << stationName << "\nCurrent temperature: " << to_string(tempRecs[i]) << "\370 \nCurrent windspeed and direction: " << to_string(speedRecs[i]) << " " << direcRecs[i] << "\n";
	flag = FALSE;
	}
	}
	}
	}

	// runs the menu of options
	void menu(string& stationName, int tempRecs[], int speedRecs[], string direcRecs[], int& size)
	{
	bool content = FALSE;
	string s;

	string thouHastSpoken, wdir, complete;
	int ctemp = 'word';
	int wspeed = 'word';
	int x = 0, count = 0;
	bool flag = FALSE;

	do{
	s = "    1 -- input a complete weather reading\n    2 -- print your information\n    3 -- Print weather history\n    4 -- Exit the program\n\nEnter 1, 2, 3, or 4: ";
	OutputText(s);//Start the menu for the first time
	getline(cin, thouHastSpoken);
	cin.clear();
	content = is_number(thouHastSpoken); //Checks what has been entered to see if it's a number. If it is, enter the switch statement. If it's not a number,
	if (content == TRUE){//if user input is a number, enter the switch statement providing the menu options that correspond with that they input
	stringstream(thouHastSpoken) >> x;
	switch (x){
	case 1: // enter weather reading
	temperature(thouHastSpoken, ctemp);
	if (thouHastSpoken == "exit"){ //if userinput is 'exit' break out and return to menu
	break;
	}
	else{
	windspeed(thouHastSpoken, wspeed);
	winddirection(thouHastSpoken, wdir);
	complete = fullReading(stationName, ctemp, wspeed, wdir);
	count++;
	populate(tempRecs, speedRecs, direcRecs, ctemp, wspeed, wdir, complete, size);
	}
	break;
	case 2: // print the reading
	if ((ctemp == 'word') || (wspeed == 'word') || (wdir == "")){
	s = "\nGreat One, you have not entered all of the information. Please select a menu option to enter the corresponding information or press 3, to exit this application.\n";
	OutputText(s);
	}
	else{
	printer(tempRecs, speedRecs, direcRecs, stationName,complete, flag, size, count);
	}
	break;
	case 3: // print the history of readings
	flag = TRUE;
	printer(tempRecs, speedRecs, direcRecs, stationName, complete, flag, size, count);
	break;
	case 4: // quit the program
	s = "\nThank you for gracing us with your brilliance, merciful ruler!";
	OutputText(s);
	break;
	default: //general error message if the user input doesnt match any of the cases
	s = "\nI apologise merciful one, but we require any of the following numbers 1, 2, 3, or 4 from you in order to select a menu option.\n";
	OutputText(s);
	}
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n"; //general error message if the user input is not a number
	OutputText(s);
	}
	} while (x != 4); //checks to see if the menu option is 4, if not keep looping back into the menu
	s = "\n\nYou have exited. We will delete the history of readings you have asked us to store. It may take a few moments.";
	OutputText(s);
	}

	int main()
	{
	string s;

	//Welcome
	s = "   Welcome to the weather station app!\nYou are our mighty overlord and saviour. Please give this weather station a name that is less than 50 characters, O great ruler!";
	OutputText(s);

	string thyname = name(); //runs name function. Once evaluated, enter menu.
	cout << string(50, '\n');

	s = "   We are devoted to your service! We can store a history of weather readings containing up to 50 records. You may decide how many histories you would like us to store.";
	OutputText(s);

	int size = determineSize();
	int *tempRecs = new int[size];
	int *speedRecs = new int[size];
	string *direcRecs = new string[size];

	s = "Thou hast spoken! Now that you have given us a name and the amount of records you'd like to keep, we can follow through with our destiny. We will give you 4 choices. You may perform any of the following input actions by entering the corresponding number and pressing the ENTER key.\nRemember O mighty one, you must use the number keys in order to choose which option you want. I hope we have performed in a way most pleasing to you.\n"; //Introduction
	OutputText(s);

	menu(thyname, tempRecs, speedRecs, direcRecs, size);

	delete[] tempRecs; // deletes the history
	delete[] speedRecs; // deletes the history
	delete[] direcRecs; // deletes the history

	/*
	//Project 6

	// Get the console window buffer Width
	int GetBufferWidth()
	{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	int bufferWidth, result;

	result = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);

	if (result)
	{
	bufferWidth = bufferInfo.dwSize.X;
	}

	return bufferWidth;
	}

	// output text with word wrap
	void OutputText(string s)
	{
	int bufferWidth = GetBufferWidth();

	for (unsigned int i = 1; i <= s.length(); i++)
	{
	char c = s[i - 1];

	int spaceCount = 0;

	// Add whitespace if newline detected.
	if (c == '\n')
	{
	int charNumOnLine = ((i) % bufferWidth);
	spaceCount = bufferWidth - charNumOnLine;
	s.insert((i - 1), (spaceCount), ' ');			//insert space before newline break
	i += (spaceCount);							//jump forward in string to character at beginning of next line
	continue;
	}

	if ((i % bufferWidth) == 0)
	{
	if (c != ' ')
	{
	for (int j = (i - 1); j > -1; j--)
	{
	if (s[j] == ' ')
	{
	s.insert(j, spaceCount, ' ');
	break;
	}
	else spaceCount++;
	}
	}
	}
	}

	// Output string to console
	cout << s;
	}

	// makes the string lowercase in order to pass to the function that checks wind direction
	string make_lowercase(const string& in)
	{
	string out;

	transform(in.begin(), in.end(), back_inserter(out), tolower);
	return out;
	}

	// checks if a string is equivalent to a wind direction
	bool is_Direction(string w)
	{
	string wordsToFind[8] =
	{ "north", "south", "west", "east", "northeast", "northwest", "southwest", "southeast" };

	string test = make_lowercase(w);

	bool answer;
	for (int i = 0; i < 8; i++)
	{
	if (test == wordsToFind[i]){
	answer = TRUE;
	break;
	}
	else{
	answer = FALSE;
	}
	}
	return answer;
	}

	// checks if input is a number (can be signed)
	bool is_number(const string& q)
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

	// checks if input is a name and enters it into station name if it is
	string name()
	{
	string s;
	string thouHastSpoken;
	string stationName;

	do
	{
	s = "\nName: ";
	OutputText(s);
	getline(cin, thouHastSpoken);//Get user input
	if (thouHastSpoken.length() < 50)//Checks length of string to see if it's too long. If it is under the projected length, enter the menu loop with instructions.
	{
	stationName = thouHastSpoken; //Initializes stationName with the userinput
	}
	else //general error message displays if the user input for the station name is too long
	{
	s = "Your words are far too long for us to read!";
	OutputText(s);
	}
	} while (stationName == ""); //keeps looping the station name question if station name is still blank

	return stationName;
	}

	// checks if input is a temperature and enters it if it is
	void temperature(string& thouHastSpoken, int& ctemp)
	{
	bool content = FALSE;
	string s;

	cout << string(50, '\n');
	do {
	s = "\nPlease enter the temperature in farenheit using the number keys on your keyboard: ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_number(thouHastSpoken); //checks if user input is a number
	if (content == TRUE){ //if userinput is a number, transfer it to temperature.
	stringstream(thouHastSpoken) >> ctemp;
	}
	else if (thouHastSpoken == "exit"){ //if userinput is 'exit' break out and return to menu
	break;
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	// checks if input is a wind speed and enters it if it is
	void windspeed(string& thouHastSpoken, int& wspeed)
	{
	bool content = FALSE;
	string s;

	cout << string(50, '\n');
	do {
	s = "\nPlease enter the wind speed to the nearest whole number: ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_number(thouHastSpoken); //checks if user input is a number
	if (content == TRUE){ //if userinput is a number, transfer it to wind speed.
	stringstream(thouHastSpoken) >> wspeed;
	if (wspeed < 0){
	wspeed = NULL;
	content = FALSE;
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	// checks if input is a wind direction and enters it if it is
	void winddirection(string& thouHastSpoken, string& wdir)
	{
	bool content = FALSE;
	string s;

	cout << string(50, '\n');
	do {
	s = "\nPlease enter the wind direction using any of the 4 cardinal or the 4 intercardinal directions (example-northeast): ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_Direction(thouHastSpoken); //checks if user input contains whole cardinal words
	if (content == TRUE){ //if userinput passes the check, transfer it to wind direction
	stringstream(thouHastSpoken) >> wdir;
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	// creates a full reading
	string fullReading(string& stationName, int& ctemp, int& wspeed, string& wdir)
	{
	string complete = "\nWeather Station: " + stationName + "\nCurrent temperature: " + to_string(ctemp) + "\370 \nCurrent windspeed and direction: " + to_string(wspeed) + " " + wdir + "\n";
	return complete;
	}

	int determineSize()
	{
	bool content = FALSE;
	string s;
	string thouHastSpoken;
	int size;

	do {
	s = "\nPlease enter a number between 1 and 50.\nSize: ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_number(thouHastSpoken); //checks if user input is a number
	if (content == TRUE){ //if userinput is a number, transfer it to size.
	stringstream(thouHastSpoken) >> size;
	if (size < 1 || size > 50){
	size = 0;
	content = FALSE;
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	else {
	return size;
	}
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	void populate(string pmetrics[], string& complete, int size)
	{
	for (int i = 0; i < size-1; i++)
	{
	pmetrics[i] = pmetrics[i + 1];
	}
	pmetrics[size-1] = complete;
	}

	// prints the weather measurements
	void printer(string pmetrics[], string& complete, bool& flag, int& size)
	{
	if (flag == FALSE)
	{
	cout << complete;
	}
	else
	{
	for (int i = size-1; i >= 0; i--)
	{
	cout << pmetrics[i];
	flag = FALSE;
	}
	}
	}

	// runs the menu of options
	void menu(string& stationName, string pmetrics[], int& size)
	{
	bool content = FALSE;
	string s;

	string thouHastSpoken, wdir, complete;
	int ctemp = 'word';
	int wspeed = 'word';
	int x = 0;
	bool flag = FALSE;
	int i = 3;

	do{
	s = "    1 -- input a complete weather reading\n    2 -- print your information\n    3 -- Print weather history\n    4 -- Exit the program\n\nEnter 1, 2, 3, or 4: ";
	OutputText(s);//Start the menu for the first time
	getline(cin, thouHastSpoken);
	cin.clear();
	content = is_number(thouHastSpoken); //Checks what has been entered to see if it's a number. If it is, enter the switch statement. If it's not a number,
	if (content == TRUE){//if user input is a number, enter the switch statement providing the menu options that correspond with that they input
	stringstream(thouHastSpoken) >> x;
	switch (x){
	case 1: // enter weather reading
	temperature(thouHastSpoken, ctemp);
	if (thouHastSpoken == "exit"){ //if userinput is 'exit' break out and return to menu
	break;
	}
	else{
	windspeed(thouHastSpoken, wspeed);
	winddirection(thouHastSpoken, wdir);
	complete = fullReading(stationName, ctemp, wspeed, wdir);
	populate(pmetrics, complete, size);
	}
	break;
	case 2: // print the reading
	if ((ctemp == 'word') || (wspeed == 'word') || (wdir == "")){
	s = "\nGreat One, you have not entered all of the information. Please select a menu option to enter the corresponding information or press 3, to exit this application.\n";
	OutputText(s);
	}
	else{
	printer(pmetrics, complete, flag, size);
	}
	break;
	case 3: // print the history of readings
	flag = TRUE;
	printer(pmetrics, complete, flag, size);
	break;
	case 4: // quit the program
	s = "\nThank you for gracing us with your brilliance, merciful ruler!";
	OutputText(s);
	break;
	default: //general error message if the user input doesnt match any of the cases
	s = "\nI apologise merciful one, but we require any of the following numbers 1, 2, 3, or 4 from you in order to select a menu option.\n";
	OutputText(s);
	}
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n"; //general error message if the user input is not a number
	OutputText(s);
	}
	} while (x != 4); //checks to see if the menu option is 4, if not keep looping back into the menu
	s = "\n\nYou have exited. We will delete the history of readings you have asked us to store. It may take a few moments.";
	OutputText(s);
	}

	int main()
	{
	string s;

	//Welcome
	s = "   Welcome to the weather station app!\nYou are our mighty overlord and saviour. Please give this weather station a name that is less than 50 characters, O great ruler!";
	OutputText(s);

	string thyname = name(); //runs name function. Once evaluated, enter menu.
	cout << string(50, '\n');

	s = "   We are devoted to your service! We can store a history of weather readings containing up to 50 records. You may decide how many histories you would like us to store.";
	OutputText(s);

	int size = determineSize();
	string *pmetrics = new string[size];

	s = "Thou hast spoken! Now that you have given us a name and the amount of records you'd like to keep, we can follow through with our destiny. We will give you 4 choices. You may perform any of the following input actions by entering the corresponding number and pressing the ENTER key.\nRemember O mighty one, you must use the number keys in order to choose which option you want. I hope we have performed in a way most pleasing to you.\n"; //Introduction
	OutputText(s);

	menu(thyname, pmetrics, size);

	delete[] pmetrics; // deletes the history

	/*
	//Project 5

	// Get the console window buffer Width
	int GetBufferWidth()
	{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	int bufferWidth, result;

	result = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);

	if (result)
	{
	bufferWidth = bufferInfo.dwSize.X;
	}

	return bufferWidth;
	}

	// output text with word wrap
	void OutputText(string s)
	{
	int bufferWidth = GetBufferWidth();

	for (unsigned int i = 1; i <= s.length(); i++)
	{
	char c = s[i - 1];

	int spaceCount = 0;

	// Add whitespace if newline detected.
	if (c == '\n')
	{
	int charNumOnLine = ((i) % bufferWidth);
	spaceCount = bufferWidth - charNumOnLine;
	s.insert((i - 1), (spaceCount), ' ');			//insert space before newline break
	i += (spaceCount);							//jump forward in string to character at beginning of next line
	continue;
	}

	if ((i % bufferWidth) == 0)
	{
	if (c != ' ')
	{
	for (int j = (i - 1); j > -1; j--)
	{
	if (s[j] == ' ')
	{
	s.insert(j, spaceCount, ' ');
	break;
	}
	else spaceCount++;
	}
	}
	}
	}

	// Output string to console
	cout << s;
	}

	// makes the string lowercase in order to pass to the function that checks wind direction
	string make_lowercase(const string& in)
	{
	string out;

	transform(in.begin(), in.end(), back_inserter(out), tolower);
	return out;
	}

	// checks if a string is equivalent to a wind direction
	bool is_Direction(string w)
	{
	string wordsToFind[8] =
	{ "north", "south", "west", "east", "northeast", "northwest", "southwest", "southeast" };

	string test = make_lowercase(w);

	bool answer;
	for (int i = 0; i < 8; i++)
	{
	if (test == wordsToFind[i]){
	answer = TRUE;
	break;
	}
	else{
	answer = FALSE;
	}
	}
	return answer;
	}

	// checks if input is a number (can be signed)
	bool is_number(const string& q)
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

	// checks if input is a name and enters it into station name if it is
	string name()
	{
	string s;
	string thouHastSpoken;
	string stationName;

	do
	{
	s = "\nName: ";
	OutputText(s);
	getline(cin, thouHastSpoken);//Get user input
	if (thouHastSpoken.length() < 50)//Checks length of string to see if it's too long. If it is under the projected length, enter the menu loop with instructions.
	{
	stationName = thouHastSpoken; //Initializes stationName with the userinput
	}
	else //general error message displays if the user input for the station name is too long
	{
	s = "Your words are far too long for us to read!";
	OutputText(s);
	}
	} while (stationName == ""); //keeps looping the station name question if station name is still blank

	return stationName;
	}

	// checks if input is a temperature and enters it if it is
	void temperature(string& thouHastSpoken, int& ctemp)
	{
	bool content = FALSE;
	string s;

	cout << string(50, '\n');
	do {
	s = "\nPlease enter the temperature in farenheit using the number keys on your keyboard: ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_number(thouHastSpoken); //checks if user input is a number
	if (content == TRUE){ //if userinput is a number, transfer it to temperature.
	stringstream(thouHastSpoken) >> ctemp;
	}
	else if (thouHastSpoken == "exit"){ //if userinput is 'exit' break out and return to menu
	break;
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	// checks if input is a wind speed and enters it if it is
	void windspeed(string& thouHastSpoken, int& wspeed)
	{
	bool content = FALSE;
	string s;

	cout << string(50, '\n');
	do {
	s = "\nPlease enter the wind speed to the nearest whole number: ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_number(thouHastSpoken); //checks if user input is a number
	if (content == TRUE){ //if userinput is a number, transfer it to wind speed.
	stringstream(thouHastSpoken) >> wspeed;
	if (wspeed < 0){
	wspeed = NULL;
	content = FALSE;
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	// checks if input is a wind direction and enters it if it is
	void winddirection(string& thouHastSpoken, string& wdir)
	{
	bool content = FALSE;
	string s;

	cout << string(50, '\n');
	do {
	s = "\nPlease enter the wind direction using any of the 4 cardinal or the 4 intercardinal directions (example-northeast): ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_Direction(thouHastSpoken); //checks if user input contains whole cardinal words
	if (content == TRUE){ //if userinput passes the check, transfer it to wind direction
	stringstream(thouHastSpoken) >> wdir;
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	// creates a full reading
	string fullReading(string& stationName, int& ctemp, int& wspeed, string& wdir)
	{
	string complete = "\nWeather Station: " + stationName + "\nCurrent temperature: " + to_string(ctemp) + "\370 \nCurrent windspeed and direction: " + to_string(wspeed) + " " + wdir + "\n";
	return complete;
	}

	void populate(string pmetrics[], string& complete)
	{
	for (int i = 0; i < 3; i++)
	{
	pmetrics[i] = pmetrics[i + 1];
	}
	pmetrics[3] = complete;
	}

	// prints the weather measurements
	void printer(string pmetrics[], string& complete, bool& flag)
	{
	if (flag == FALSE)
	{
	cout << complete;
	}
	else
	{
	for (int i = 3; i >= 0; i--)
	{
	cout << pmetrics[i];
	flag = FALSE;
	}
	}
	}

	// runs the menu of options
	void menu(string& stationName)
	{
	bool content = FALSE;
	string s;

	string thouHastSpoken, wdir, complete;
	int ctemp = 'word';
	int wspeed = 'word';
	string pmetrics[4];
	int x = 0;
	bool flag = FALSE;
	int i = 3;

	do{
	s = "    1 -- input a complete weather reading\n    2 -- print your information\n    3 -- Print weather history\n    4 -- Exit the program\n\nEnter 1, 2, 3, or 4: ";
	OutputText(s);//Start the menu for the first time
	getline(cin, thouHastSpoken);
	cin.clear();
	content = is_number(thouHastSpoken); //Checks what has been entered to see if it's a number. If it is, enter the switch statement. If it's not a number,
	if (content == TRUE){//if user input is a number, enter the switch statement providing the menu options that correspond with that they input
	stringstream(thouHastSpoken) >> x;
	switch (x){
	case 1: // enter weather reading
	temperature(thouHastSpoken, ctemp);
	if (thouHastSpoken == "exit"){ //if userinput is 'exit' break out and return to menu
	break;
	}
	else{
	windspeed(thouHastSpoken, wspeed);
	winddirection(thouHastSpoken, wdir);
	complete = fullReading(stationName, ctemp, wspeed, wdir);
	populate(pmetrics, complete);
	}
	break;
	case 2: // print the reading
	if ((ctemp == 'word') || (wspeed == 'word') || (wdir == "")){
	s = "\nGreat One, you have not entered all of the information. Please select a menu option to enter the corresponding information or press 3, to exit this application.\n";
	OutputText(s);
	}
	else{
	printer(pmetrics, complete, flag);
	}
	break;
	case 3: // print the history of readings
	flag = TRUE;
	printer(pmetrics, complete, flag);
	break;
	case 4: // quit the program
	s = "\nThank you for gracing us with your brilliance, merciful ruler!";
	OutputText(s);
	break;
	default: //general error message if the user input doesnt match any of the cases
	s = "\nI apologise merciful one, but we require any of the following numbers 1, 2, 3, or 4 from you in order to select a menu option.\n";
	OutputText(s);
	}
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n"; //general error message if the user input is not a number
	OutputText(s);
	}
	} while (x != 4); //checks to see if the menu option is 4, if not keep looping back into the menu
	s = "\n\nYou have exited.";
	OutputText(s);
	}

	int main()
	{
	string s;

	//Welcome
	s = "   Welcome to the weather station app!\nYou are our mighty overlord and saviour. Please give this weather station a name that is less than 50 characters, O great ruler!";
	OutputText(s);

	string thyname = name(); //runs name function. Once evaluated, enter menu.
	cout << string(50, '\n');

	s = "Thou hast spoken! Now that you have given us a name, we can follow through with our destiny. We will give you 4 choices. You may perform any of the following input actions by entering the corresponding number and pressing the ENTER key.\nRemember O mighty one, you must use the number keys in order to choose which option you want. I hope we have performed in a way most pleasing to you.\n"; //Introduction
	OutputText(s);

	menu(thyname);

	/*
	//Project 4

	//Define the variables
	bool content = FALSE;
	string s;
	string thouHastSpoken;
	string stationName, wdir;
	int ctemp = NULL;
	int wspeed = NULL;
	int x = 0;


	// Get the console window buffer Width
	int GetBufferWidth()
	{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	int bufferWidth, result;

	result = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);

	if (result)
	{
	bufferWidth = bufferInfo.dwSize.X;
	}

	return bufferWidth;
	}

	void OutputText(string s)
	{
	int bufferWidth = GetBufferWidth();

	for (unsigned int i = 1; i <= s.length(); i++)
	{
	char c = s[i - 1];

	int spaceCount = 0;

	// Add whitespace if newline detected.
	if (c == '\n')
	{
	int charNumOnLine = ((i) % bufferWidth);
	spaceCount = bufferWidth - charNumOnLine;
	s.insert((i - 1), (spaceCount), ' ');			//insert space before newline break
	i += (spaceCount);							//jump forward in string to character at beginning of next line
	continue;
	}

	if ((i % bufferWidth) == 0)
	{
	if (c != ' ')
	{
	for (int j = (i - 1); j > -1; j--)
	{
	if (s[j] == ' ')
	{
	s.insert(j, spaceCount, ' ');
	break;
	}
	else spaceCount++;
	}
	}
	}
	}

	// Output string to console
	cout << s;
	}

	string make_lowercase(const string& in) //makes input lowercase so it can be used to compare direction
	{
	string out;

	transform(in.begin(), in.end(), back_inserter(out), tolower);
	return out;
	}

	bool is_Direction(string w) ///checks if input is a direction
	{
	string wordsToFind[8] =
	{ "north", "south", "west", "east", "northeast", "northwest", "southwest", "southeast" };

	string test = make_lowercase(w);

	bool answer;
	for (int i = 0; i < 8; i++)
	{
	if (test == wordsToFind[i]){
	answer = TRUE;
	break;
	}
	else{
	answer = FALSE;
	}
	}
	return answer;
	}

	bool is_number(const string& q) //checks if input is a number (can be signed)
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

	void name()
	{
	s = "\nName: ";
	OutputText(s);
	getline(cin, thouHastSpoken);//Get user input
	do
	{
	if (thouHastSpoken.length() < 50)//Checks length of string to see if it's too long. If it is under the projected length, enter the menu loop with instructions.
	{
	stringstream(thouHastSpoken) >> stationName; //Initializes stationName with the userinput
	}
	else //general error message displays if the user input for the station name is too long
	{
	s = "Your words are far too long for us to read!";
	OutputText(s);
	}
	} while (stationName == ""); //keeps looping the station name question if station name is still blank
	}

	void temperature()
	{
	cout << string(50, '\n');
	do {
	s = "\nPlease enter the temperature in farenheit using the number keys on your keyboard: ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_number(thouHastSpoken); //checks if user input is a number
	if (content == TRUE){ //if userinput is a number, transfer it to temperature.
	stringstream(thouHastSpoken) >> ctemp;
	}
	else if (thouHastSpoken == "exit"){ //if userinput is 'exit' break out and return to menu
	break;
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	void winddirection()
	{
	cout << string(50, '\n');
	do {
	s = "\nPlease enter the wind direction using any of the 4 cardinal or the 4 intercardinal directions (example-northeast): ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_Direction(thouHastSpoken); //checks if user input contains whole cardinal words
	if (content == TRUE){ //if userinput passes the check, transfer it to wind direction
	stringstream(thouHastSpoken) >> wdir;
	}
	else if (thouHastSpoken == "exit"){ //if userinput is 'exit' break out of the case and return to menu
	break;
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	void windspeed()
	{
	cout << string(50, '\n');
	do {
	s = "\nPlease enter the wind speed to the nearest whole number: ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_number(thouHastSpoken); //checks if user input is a number
	if (content == TRUE){ //if userinput is a number, transfer it to wind speed.
	stringstream(thouHastSpoken) >> wspeed;
	if (wspeed < 0){
	wspeed = NULL;
	content = FALSE;
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	}
	else if (thouHastSpoken == "exit"){ //if userinput is 'exit' break out of the case and return to menu
	break;
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	void printer()
	{
	if ((ctemp == NULL) || (wspeed == NULL) || (wdir == "")){
	s = "\nGreat One, you have not entered all of the information. Please select a menu option to enter the corresponding information or press 3, to exit this application.\n";
	OutputText(s);
	}
	else{
	cout << "\nWeather Station: " << stationName << fixed << setprecision(1) << "\nCurrent temperature: " << ctemp << "\370 \nCurrent windspeed and direction: " << wspeed << " " << wdir << endl;
	}
	}

	void menu()
	{
	do{
	s = "    1 -- input a complete weather reading\n    2 -- print your information\n    3 -- Exit the program\nIf you find that you have chosen the wrong menu option, type exit to return to the menu.\nEnter 1, 2, or 3: ";
	OutputText(s);//Start the menu for the first time
	getline(cin, thouHastSpoken);
	content = is_number(thouHastSpoken); //Checks what has been entered to see if it's a number. If it is, enter the switch statement. If it's not a number,
	if (content == TRUE){//if user input is a number, enter the switch statement providing the menu options that correspond with that they input
	stringstream(thouHastSpoken) >> x;
	switch (x){
	case 1:
	temperature();
	if (thouHastSpoken == "exit"){
	break;
	}
	winddirection();
	if (thouHastSpoken == "exit"){
	break;
	}
	windspeed();
	if (thouHastSpoken == "exit"){
	break;
	}
	break;
	case 2:
	printer();
	break;
	case 3:
	s = "\nThank you for gracing us with your brilliance, merciful ruler!";
	OutputText(s);
	break;
	default:
	s = "\nI apologise merciful one, but we require any of the following numbers 1, 2, or 3 from you in order to select a menu option.\n"; //general error message if the user input doesnt match any of the cases
	OutputText(s);
	}
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n"; //general error message if the user input is not a number
	OutputText(s);
	}
	} while (x != 3); //checks to see if the menu option is 5, if not keep looping back into the menu
	s = "\n\nYou have exited.";
	OutputText(s);
	}

	int main()
	{
	//Welcome
	s = "   Welcome to the weather station app!\nYou are our mighty overlord and saviour. Please give this weather station a name that is less than 50 characters, O great ruler!";
	OutputText(s);

	name(); //runs name function. Once evaluated, enter menu.
	cout << string(50, '\n');

	s = "Thou hast spoken! Now that you have given us a name, we can follow through with our destiny. We will give you 3 choices. You may perform any of the following input actions by entering the corresponding number and pressing the ENTER key.\nRemember O mighty one, you must use the number keys in order to choose which option you want. I hope we have performed in a way most pleasing to you.\n"; //Introduction
	OutputText(s);

	menu();

	/*
	//Project 3
	// Get the console window buffer Width
	int GetBufferWidth()
	{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	int bufferWidth, result;

	result = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);

	if (result)
	{
	bufferWidth = bufferInfo.dwSize.X;
	}

	return bufferWidth;
	}

	void OutputText(string s)
	{
	int bufferWidth = GetBufferWidth();

	for (unsigned int i = 1; i <= s.length(); i++)
	{
	char c = s[i - 1];

	int spaceCount = 0;

	// Add whitespace if newline detected.
	if (c == '\n')
	{
	int charNumOnLine = ((i) % bufferWidth);
	spaceCount = bufferWidth - charNumOnLine;
	s.insert((i - 1), (spaceCount), ' ');			//insert space before newline break
	i += (spaceCount);							//jump forward in string to character at beginning of next line
	continue;
	}

	if ((i % bufferWidth) == 0)
	{
	if (c != ' ')
	{
	for (int j = (i - 1); j > -1; j--)
	{
	if (s[j] == ' ')
	{
	s.insert(j, spaceCount, ' ');
	break;
	}
	else spaceCount++;
	}
	}
	}
	}

	// Output string to console
	cout << s;
	}

	string make_lowercase(const string& in) //makes input lowercase so it can be used to compare direction
	{
	string out;

	transform(in.begin(), in.end(), back_inserter(out), tolower);
	return out;
	}

	bool is_Direction(string w) ///checks if input is a direction
	{
	string wordsToFind[8] =
	{ "north", "south", "west", "east", "northeast", "northwest", "southwest", "southeast" };

	string test = make_lowercase(w);

	bool answer;
	for (int i = 0; i < 8; i++)
	{
	if (test == wordsToFind[i]){
	answer = TRUE;
	break;
	}
	else{
	answer = FALSE;
	}
	}
	return answer;
	}

	bool is_number(const string& q) //checks if input is a number (can be signed)
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

	void name()
	{
	s = "\nName: ";
	OutputText(s);
	getline(cin, thouHastSpoken);//Get user input
	do
	{
	if (thouHastSpoken.length() < 50)//Checks length of string to see if it's too long. If it is under the projected length, enter the menu loop with instructions.
	{
	stringstream(thouHastSpoken) >> stationName; //Initializes stationName with the userinput
	}
	else //general error message displays if the user input for the station name is too long
	{
	s = "Your words are far too long for us to read!";
	OutputText(s);
	}
	} while (stationName == ""); //keeps looping the station name question if station name is still blank
	}

	void temperature()
	{
	cout << string(50, '\n');
	do {
	s = "\nPlease enter the temperature in farenheit using the number keys on your keyboard: ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_number(thouHastSpoken); //checks if user input is a number
	if (content == TRUE){ //if userinput is a number, transfer it to temperature.
	stringstream(thouHastSpoken) >> ctemp;
	}
	else if (thouHastSpoken == "exit"){ //if userinput is 'exit' break out of the case and return to menu
	break;
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	void winddirection()
	{
	cout << string(50, '\n');
	do {
	s = "\nPlease enter the wind direction using any of the 4 cardinal or the 4 intercardinal directions (example-northeast): ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_Direction(thouHastSpoken); //checks if user input contains whole cardinal words
	if (content == TRUE){ //if userinput passes the check, transfer it to wind direction
	stringstream(thouHastSpoken) >> wdir;
	}
	else if (thouHastSpoken == "exit"){ //if userinput is 'exit' break out of the case and return to menu
	break;
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	void windspeed()
	{
	cout << string(50, '\n');
	do {
	s = "\nPlease enter the wind speed to the nearest whole number: ";
	OutputText(s);
	getline(cin, thouHastSpoken);
	content = is_number(thouHastSpoken); //checks if user input is a number
	if (content == TRUE){ //if userinput is a number, transfer it to wind speed.
	stringstream(thouHastSpoken) >> wspeed;
	if (wspeed < 0){
	wspeed = NULL;
	content = FALSE;
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	}
	else if (thouHastSpoken == "exit"){ //if userinput is 'exit' break out of the case and return to menu
	break;
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n";
	OutputText(s);
	}
	} while (content == FALSE);
	}

	void printer()
	{
	if ((ctemp == NULL) && (wspeed == NULL) && (wdir == "")){
	s = "\nGreat One, you have not entered any of the information. Please select a menu option to enter the corresponding information or press 5, to exit this application.\n";
	OutputText(s);
	}
	else{
	cout << "\nWeather Station: " << stationName << fixed << setprecision(1) << "\nCurrent temperature: " << ctemp << "\370 \nCurrent windspeed and direction: " << wspeed << " " << wdir << endl;
	}
	}

	void menu()
	{
	do{
	s = "Enter 1, 2, 3, 4, or 5: ";
	OutputText(s);//Start the menu for the first time
	getline(cin, thouHastSpoken);
	content = is_number(thouHastSpoken); //Checks what has been entered to see if it's a number. If it is, enter the switch statement. If it's not a number,
	if (content == TRUE){//if user input is a number, enter the switch statement providing the menu options that correspond with that they input
	stringstream(thouHastSpoken) >> x;
	switch (x){
	case 1:
	temperature();
	break;
	case 2:
	winddirection();
	break;
	case 3:
	windspeed();
	break;
	case 4:
	printer();
	break;
	case 5:
	s = "\nThank you for gracing us with your brilliance, merciful ruler!";
	OutputText(s);
	break;
	default:
	s = "\nI apologise merciful one, but we require any of the following numbers 1,2,3,4 or 5 from you in order to select a menu option.\n"; //general error message if the user input doesnt match any of the cases
	OutputText(s);
	}
	}
	else {
	cin.clear();
	s = "Have mercy great ruler we cannot process this information!\n"; //general error message if the user input is not a number
	OutputText(s);
	}
	} while (x != 5); //checks to see if the menu option is 5, if not keep looping back into the menu
	s = "\n\nYou have exited.";
	OutputText(s);
	}

	int main()
	{
	bool content = FALSE;
	string s;
	string thouHastSpoken;
	string stationName, wdir;
	int ctemp = NULL;
	int wspeed = NULL;
	int x = 0;
	//Project 3

	//Welcome
	s = "   Welcome to the weather station app!\nYou are our mighty overlord and saviour. Please give this weather station a name that is less than 50 characters, O great ruler!";
	OutputText(s);

	name(); //runs name function. Once evaluated, enter menu.
	cout << string(50, '\n');

	s = "Thou hast spoken! Now that you have given us a name, we can follow through with our destiny. We will give you 5 choices. You may perform any of the following input actions by entering the corresponding number and pressing the ENTER key.\n    1 -- temperature\n    2 -- wind direction\n    3 -- wind speed\n    4 -- print current information\n    5 -- Exit the program\nIf you find that you have chosen the wrong menu option, type exit to return to the menu.\nRemember O mighty one, you must use the number keys in order to choose which option you want. I hope we have performed in a way most pleasing to you.\n"; //Introduction
	OutputText(s);

	menu();


	int main()
	{
	//Project 2
	string stationName = "", wdir = "";
	float ctemp = 0.0f;
	int wspeed = 0;
	cout << "I will ask you a series of inputs, please press enter after each input.\n\nPlease give the name of the weather station: ";
	getline(cin, stationName);
	cout << "\nthe temperature in farenheit to the nearest 10th of a degree?: ";
	cin >> ctemp;
	cout << "\nthe wind direction?: ";
	cin >> wdir;
	cout << "\nand then the wind speed to the nearest whole number?: ";
	cin >> wspeed;
	cout << "\n\nWeather Station: " << stationName << fixed << setprecision(1) << "\nCurrent temperature: " << ctemp << "\nCurrent windspeed and direction: " << wspeed << " " << wdir << endl;

	/*
	//Project 1
	/*string stationName = "Fangorn Weathercast";
	float ctemp = 43.0f;
	int wspeed = 13;
	string wdir = "NE";
	cout << "Hello World!" << endl;
	cout << stationName << endl;
	cout << fixed << setprecision(1) << "Current temperature: " << ctemp << endl;
	cout << "Current windspeed and direction: " << wspeed << " " << wdir << endl;*/

	return 0;
}

