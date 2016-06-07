#include "stringServer.h"
#include "helperfuncs.h"

stringServer* stringServer::m_pInstance = NULL;
/* 
This function is called to create an instance of the class.
Calling the constructor publicly is not allowed.
The constructoris private and is only called by this Instance function.
*/

//Returns a pointer to the instance of stringServer if it exists
stringServer* stringServer::Instance()
{
	if (!m_pInstance)
		m_pInstance = new stringServer;

	return m_pInstance;
}

//sets the language in which all strings ought to be displayed
void stringServer::set_Language(){
	string s, thouHastSpoken;
	bool content = false;
	cout << "Do you want to choose a different language? Type Y for yes, N for No\nY/N: ";
	//gets user input
	getline(cin, thouHastSpoken);
	//if input is yes
	if (thouHastSpoken == "Y" || thouHastSpoken == "y")
	{
		//loops through language input
		do {
			s = "0-English\n1-Pig Latin\nLanguage: ";
			OutputText(s);

			//gets user input
			getline(cin, thouHastSpoken);

			//if user input is 0
			if (thouHastSpoken == "0"){
				content = true;
				filename = "englishway.txt";
				stringstream(thouHastSpoken) >> lang;
			}
			//if user input is 1
			else if (thouHastSpoken == "1"){
				content = true;
				filename = "Pig_Latin.txt";
				stringstream(thouHastSpoken) >> lang;
			}
			//displays error message if user input cannot be processed
			else {
				s = "Have mercy great ruler we cannot process this information!\n";
				OutputText(s);
			}
		//breaks out of loop if content is input was a number
		} while (content == false);
	}
	//displays default
	else
		cout << endl << "Default" << endl;
}

//returns language selected and opens the correspodning file
void stringServer::get_Language(){
	int i = 0;
	ifstream myfile;
	if (lang == 0)
	{
		cout << "Selected English" << endl << endl;
		myfile.open("englishway.txt");
	}
	else if (lang == 1)
	{
		cout << "Selected Pig Latin" << endl;
		myfile.open("Pig_Latin.txt");
	}
	if (myfile.is_open()){
		while (!myfile.eof())
		{
			getline(myfile, fLines[i]);
			i++;
		}
	}
	myfile.close();
}

//prints a line based on a given number
void stringServer::line(int i){
	OutputText(fLines[i]);
}
