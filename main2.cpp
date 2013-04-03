#include <iostream>
#include <string>
#include "converter.h"
using namespace std;

//main function
int main()
{

Converter convertor;
string words;

//for use with plug board settings
char plug1;
char plug2;
int iPlug1;
int iPlug2;

//Instructions on how to input into plug board
cout << "please set the plug board, press \".\" to begin encoding" << endl;
cout << "enter the first letter, press enter, then the second letter" << endl;

do
{
	//Accepts both Plug board inputs
	cout << "\tFirst Plug setting : ";
	cin >> plug1;
	cout << "\tSecond Plug setting : ";
	cin >> plug2;

	//Converts both plugs to ints to check for exit controller
	iPlug1 = convertor.charToInt(plug1);
	iPlug2 = convertor.charToInt(plug2);

	//sets Plug Board according to inputs if their set correctly
	if(iPlug1 != 0 && iPlug1 != 27 && iPlug2 != 0 && iPlug2 != 27)
	{
	convertor.setPlugBoard(plug1,plug2);
	}

}while( iPlug1 != 0 && iPlug1 != 27 && iPlug2 != 0 && iPlug2 != 27 );

cout << "Plug Board settings ::" << endl;
convertor.showPlugBoard();

cout << endl << endl;

cout << "Beginning encrypting now" << endl;
cout << "Please enter a statement to encrypt" << endl;

//clears the cin and allows the program to accept a string
cin.clear();
cin.sync();

//get the string and convert it as needed
getline(cin, words);
convertor.convertString(words);

//here as a place holder to stop Engima program from closing
int item;
cin >> item;
}