#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Converter
{
public:
		//Constructor
	Converter();
		//Char to Int/ Int to Char functions
	void convertString(string);			//reads the string and turns it into its corresponding numbers
	int charToInt(char);				//turns a Char into an Int equivalent
	char intToChar(int);				//turns an Int into a Char equivalent
	void setString(string);				//used to set the Converter private string
	string getString();					//used to get the Converter private string
		//plug board functions
	void setPlugBoard(char, char);		//sets the plug board data
	char readPlugBoard(char);			//gets the plug board data
	void showPlugBoard();				//shows the plugboard settings

private:
	char charArray[25];					//for use with plug board
	string input;
	int outPut;
};