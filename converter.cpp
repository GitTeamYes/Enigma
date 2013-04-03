#include <iostream>
#include <cstdlib>
#include "converter.h" //has class definitions for converting
using namespace std;

//Constructor that makes the array of characters
Converter::Converter()
{
	char charArray[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
}

//takes a char and converts it to the int equivalent
int Converter::charToInt(char a)
{
	switch(a)
	{
		case 'a' :
			return 1;
			break;
		case 'b' :
			return 2;
			break;
		case 'c' :
			return 3;
			break;
		case 'd' :
			return 4;
			break;
		case 'e' :
			return 5;
			break;
		case 'f' :
			return 6;
			break;
		case 'g' :
			return 7;
			break;
		case 'h' :
			return 8;
			break;
		case 'i' :
			return 9;
			break;
		case 'j' :
			return 10;
			break;
		case 'k' :
			return 11;
			break;
		case 'l' :
			return 12;
			break;
		case 'm' :
			return 13;
			break;
		case 'n' :
			return 14;
			break;
		case 'o' :
			return 15;
			break;
		case 'p' :
			return 16;
			break;
		case 'q' :
			return 17;
			break;
		case 'r' :
			return 18;
			break;
		case 's' :
			return 19;
			break;
		case 't' :
			return 20;
			break;
		case 'u' :
			return 21;
			break;
		case 'v' :
			return 22;
			break;
		case 'w' :
			return 23;
			break;
		case 'x' :
			return 24;
			break;
		case 'y' :
			return 25;
			break;
		case 'z' :
			return 26;
			break;
		//used as the escape char
		case '.' :
			return 0;
			break;
		//for everything else
		default  :
			return 27;
			break;
	}
}

//takes an int and converts it to the char equivalent
char Converter::intToChar(int x)
{
	switch(x)
	{	
		case 1 :
			return 'a';
			break;
		case 2 :
			return 'b';
			break;
		case 3 :
			return 'c';
			break;
		case 4 :
			return 'd';
			break;
		case 5 :
			return 'e';
			break;
		case 6 :
			return 'f';
			break;
		case 7 :
			return 'g';
			break;
		case 8 :
			return 'h';
			break;
		case 9 :
			return 'i';
			break;
		case 10 :
			return 'j';
			break;
		case 11 :
			return 'k';
			break;
		case 12 :
			return 'l';
			break;
		case 13 :
			return 'm';
			break;
		case 14 :
			return 'n';
			break;
		case 15 :
			return 'o';
			break;
		case 16 :
			return 'p';
			break;
		case 17 :
			return 'q';
			break;
		case 18 :
			return 'r';
			break;
		case 19 :
			return 's';
			break;
		case 20 :
			return 't';
			break;
		case 21 :
			return 'u';
			break;
		case 22 :
			return 'v';
			break;
		case 23 :
			return 'w';
			break;
		case 24 :
			return 'x';
			break;
		case 25 :
			return 'y';
			break;
		case 26 :
			return 'z';
			break;
		case 27 :
			return ' ';
			break;
		//Default, for troubleshooting
		default :
			return '!';
			break;
	}
}

void Converter::convertString(string entry)
{
char tmp;

	for(int i = 0; i < entry.size(); i++)
	{
		tmp = entry.at(i);					//gets the character at place i
		outPut = charToInt(tmp);			//turns that character into its number equivalent

		if(outPut == 27 || outPut == 0)		//if the character as something else than a character
		{
										//print nothing 
		}
		else								//for all characters (in number form), do this
		{
		cout << outPut << " ";			//print out the character then put a space.
		}
	}
	cout << endl;
}

void Converter::setString(string a)		//setter for input
{
	input = a;
}
string Converter::getString()			//getter for input
{
	return input;
}
void Converter::setPlugBoard(char cOne, char cTwo)	//used to switch 2 letters in the character array
{
	int tmp1;							//create a place holder for cOne
	int tmp2;							//create a place holder for cTwo
	tmp1 = charToInt(cOne);				//make place holder for tmp1 equal to cOne's number equivalent
	tmp2 = charToInt(cTwo);				//make place holder for tmp2 equal to cTwo's number equivalent

	charArray[(tmp1 - 1)] = cTwo;		//alter Array to have the corresponding number equal to the changed character
	charArray[(tmp2 - 1)] = cOne;		//alter Array to have the corresponding number equal to the changed character

	//Confirmation the switch occured
	cout << "\n" << cOne << " will now print out ";
	cout << charArray[(tmp1 - 1)] << " and ";
	cout << charArray[(tmp2 - 1)] << " will become " << cTwo << "." << endl;
	
}
char Converter::readPlugBoard(char entry)
{
	int tmp = charToInt(entry);		//turn the character into an Int
	return charArray[(tmp - 1)];	//go to Character Array entry Int - 1 and return that.
}
void Converter::showPlugBoard()
{
	for(int i = 0; i < 25; i++)
	{
		char tmp = intToChar(i);

		cout << tmp << " connects to " << charArray[i] << endl;
	}
}