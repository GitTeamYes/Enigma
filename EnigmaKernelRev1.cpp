#include <iostream> // Standard Library Header for cout and cin.
#include <stdio.h> // Standard Library Header for the printf() command. 
#include <regex> // Standard Library Header for regular expressions.
#include <string>   // Standard Library Header for string functions.
#include <sstream>  // Standard Library Header for string stream processing.
#include <cctype>  // Standard Library Header for character-handling functions.
using namespace std;

int intTempNum;
inline int convertCharToNumber(char charInput)
{
	// Transform the input letter into its corresponding integer.
	switch(charInput)
	{
		case 'A':
			intTempNum = 0;
			break;
		case 'B':
			intTempNum = 1;
			break;
		case 'C':
			intTempNum = 2;
			break;
		case 'D':
			intTempNum = 3;
			break;
		default:
			cout << "Error Input Character\n";
			break;
		}
	return intTempNum;
}

string stringTempString;
inline string convertNumberToString(int intInput)
{
	// Transform the output number into its corresponding character as a string.
	switch(intInput)
	{
		case 0:
			stringTempString = "A";
			break;
		case 1:
			stringTempString = "B";
			break;
		case 2:
			stringTempString = "C";
			break;
		case 3:
			stringTempString = "D";
			break;
		default:
			cout << "Error Output Number\n";
			break;
		}
	return stringTempString;
}


void main()
{
	// Declaration section
	
	// For the sake of completeness, the German language names for the various parts of the 
	// Enigma machine are detailed here:
	// Eintrittwalze {Abbreviated as ETW} [Entry wheel, a.k.a., fixed rotor]
	// Walzen [Wheels, a.k.a., stepping rotors]
	// Umkehrwalze {Abbreviated as UKW} [Reversing wheel, a.k.a., reflector]
	// Gluehlampenfeld [Lampboard, a.k.a., display]
	// Tastatur [Keyboard]
	// Steckerbrett [Plugboard]
	// Steckerverbindungen [Plug connection, patch cords?]
	//
	// Outputs going in the followling direction:
	// keyboard -> plug board -> fixed rotor -> fast rotor -> medium rotor -> slow rotor -> reflector
	int intKeyboardOutputToPlugBoardInput;
	int intPlugBoardOutputToFixedRotorInput;
	int intFixedRotorOutputToFastRotorInput;
	int intFastRotorOutputToMediumRotorInput;
	int intMediumRotorOutputToSlowRotorInput;
	int intSlowRotorOutputToReflectorInput;

	// Outputs going in the followling direction:
	// reflector -> slow rotor -> medium rotor -> fast rotor -> fixed rotor -> plug board -> display
	int intReflectorOutputToSlowRotorInput;
	int intSlowOutputToMediumRotorInput;
	int intMediumOutputToFastRotorInput;
	int intFastOutputToFixedRotorInput;
	int intFixedRotorOutputToPlugBoardInput;
	int intPlugBoardOutputToDisplayInput;


	// Declare the modulo constant for this particular Enigma machine.
	const int N = 4;
	// Declare the fixed rotor, stepping rotors (hereafter simply called rotors), 
	// reflector & plug board.  Note, the fixed rotor is just a rotor that does not 
	// turn and usually, but not always, has the identity mapping, i.e., {0, 1, 2, 3}.
	// CAUTION: the German Railway Enigma, which is the machine we are supposed 
	// to simulate, employs a fixed rotor that does NOT use the identity mapping. 
	// For this reason, the fixed rotor will have to have both a forward and reverse 
	// version, just like the stepping rotors.
	// Note, the plug board can be thought of as a fixed rotor where some of the 
	// mappings are not the identity mapping, and only pairwise swaps (mappings) are 
	// allowed.
	// Definition: Pairwise Mapping - a pairwise mapping is a mapping wherein only the 
	// following transformations are allowed: [i] = j and [j] = i.  This transformation 
	// represents a single patch cord.  A second patch cord would be represented as 
	// follows: [k] = l and [l] = k, where k and l are different from i and j.  In the 
	// case where a patch cord is not present or has been removed the mapping reverts to 
	// the identity mapping, e.g., suppose the patch cord swapping k and l were removed, 
	// then the mapping would become [k] = k and [l] = l.  In other words, it would 
	// becomes a pairwise identity mapping. Therefore, the only allowed configurations 
	// are pairwise swaps or pairwise identity transformations - nothing else.
	//
	// Cache of five (5) possible stepping rotors.
	// The integers in the arrays are aliases for the letters from the alphabet:
	// 0 = A, 1 = B, 2 = C, 3 = D, 4 = E, 5 = F, 6 = G, 7 = H, 8 = I, 9 = J, etc.
	// In addition to providing the mapping for each of the available stepping rotors,
	// it is also required that we indicate the notch position associated with each 
	// stepping rotor.  
	// Definiton: Notch Position - The position on the stepping rotor, which when reached,
	// causes the next slowest rotor in the rotor stack to advance.
	// The default notch position for a stepping rotor with a four (4) letter alphabet would 
	// be array location [3], i.e., when the stepping rotor makes the transition 
	// from [3] to [0], the next slowest rotor in the rotor stack advances.
	int intRotor1[N] = {2, 3, 1, 0};
	int intRotor2[N] = {1, 3, 2, 0};
	int intRotor3[N] = {0, 3, 1, 2};
	int intRotor4[N] = {2, 1, 3, 0};
	int intRotor5[N] = {3, 2, 1, 0};
	int intNotchPositionOfRotor1 = 1;
	int intNotchPositionOfRotor2 = 3;
	int intNotchPositionOfRotor3 = 3;
	int intNotchPositionOfRotor4 = 3;
	int intNotchPositionOfRotor5 = 3;
	// 
	// Single fixed rotor.
	// Identity transformation.  NOTE, the German Railway Enigma uses a non-identity mapping.
	int intFixedRotorFwd[N] = {0, 1, 2, 3};
	int intFixedRotorRev[N];
	//
	// Single reflector.
	// Reflector Rules:
	// No index is allowed to map back to itself, i.e., the following is not allowed 
	// [i] = i, and, and this is equally important, for each [i] = j there must be a [j] = i, 
	// i.e., each pair [i] = j & [j] = i must exist and be unique.
	// Here are all the allowed Reflectors for a 4-letter Enigma machine:
	//   {1, 0, 3, 2}
	//   {2, 3, 0, 1}
	//   {3, 2, 1, 0}
	// In this case, the first pair has three (3) possible choices because one (1) of the four (4) 
	// choices is the identity mapping, [i] = i.  The second pair has only one (1) possible choice 
	// because one (1) of the two (2) choices is the identity mapping, [j] = j.  Therefore, the 
	// total possible number of Reflectors is 3 x 1 = 3.
	int intReflector[N] = {3, 2, 1, 0};

	// Declare the stepping rotor slots or positions, and their respective notch positions.
	int intSlowRotorFwd[N];
	int intMediumRotorFwd[N];
	int intFastRotorFwd[N];

	int intSlowRotorNotchPosition;
	int intMediumRotorNotchPosition;
	int intFastRotorNotchPosition;

	int intSlowRotorRev[N];
	int intMediumRotorRev[N];
	int intFastRotorRev[N];

	// Declare the indices to the top position of the rotors.  The top position is the position 
	// showing through the window in the top panel of the Enigma machine.  The initial top positions 
	// correspond to the key code.
	int FastTopIndex;
	int MediumTopIndex;
	int SlowTopIndex;
	// The following indices will be used to remember the initial value of their respective top 
	// position indices.
	int TempFastTopIndex;
	int TempMediumTopIndex;
	int TempSlowTopIndex;

	// Remember the values of the top position pointers.
	TempFastTopIndex = FastTopIndex;
	TempMediumTopIndex = MediumTopIndex;
	TempSlowTopIndex = SlowTopIndex;

	// Declare and initialize the step counters for each rotor poisition.
	int intFastRotorStepCounter = 0;
	int intMediumRotorStepCounter = 0;
	int intSlowRotorStepCounter = 0;

	bool boolInputFormatIsCorrect = false;
	string stringInput;
	char charInputLetter;
	int intTempIndex;
	int intTemp = 1;

	// Steps to setting up the Enigma machine:
	//   1) Choose the three (3) rotors from the available 5 rotors.
	//   2) Choose the slots (Slow, Medium & Fast) in which to place rotors.
	//   3) Set ring settings for the Slow, Medium & fast rotors.
	//   4) Setup the plug board.
	//   5) Set the key code of the rotors.
	
	// Steps #1 & 2 - Select the rotors and their respective slots.
	int intSlow = 3;
	int intMedium = 2;
	int intFast = 1;

	// Step #3 - Set the ring settings for the Slow, Medium & Fast rotors.
	// Ring Setting Rules:
	// The ring settings do not affect the notch position or the key code positions, the ring 
	// settings only change the mappings.
	int intSlowRingSetting = 0;
	int intMediumRingSetting = 0;
	int intFastRingSetting = 0;

	// Step #4 - Setup the plug board.
	// Plug Board Rules:
	// The plug board interchanges pairs of letters, and only pairs of letters.  Because of this 
	// restriction to pairwise interchanges, the array representing the plug board is bidirectional  
	// unlike the stepping rotors, which might not be unidirectional, i.e., since the mappings of 
	// the stepping rotors are not necessarily pairwise, we must create both a forward and reverse 
	// version of the stepping rotor.  The forward version of the stepping rotor is used when the 
	// signal is propagating from the fixed rotor to the reflector, while the reverse version is 
	// used when the signal is propagating from the reflector to the fixed rotor. 
	int intPlugBoard[N] = {0, 1, 2, 3};

	// Step #5 - Set the key code.
	// Set the top position indices to initially point to the first element of the Fast, Medium and 
	// Slow rotors.  Later, these will be changed from the default key code, 000, to the required 
	// key code.
	FastTopIndex = 0;
	MediumTopIndex = 0;
	SlowTopIndex = 0;

	// Assign rotors to the Slow, Medium & Fast slots and set the ring settings.
	switch(intSlow)
	{
		case 1:
			for(int i = 0; i < N; i++)
			{
				intSlowRotorFwd[i] = intRotor1[(intSlowRingSetting + i)%N];
			}
			intSlowRotorNotchPosition = intNotchPositionOfRotor1;
			break;
		case 2:
			for(int i = 0; i < N; i++)
			{
				intSlowRotorFwd[i] = intRotor2[(intSlowRingSetting + i)%N];
			}
			intSlowRotorNotchPosition = intNotchPositionOfRotor2;
			break;
		case 3:
			for(int i = 0; i < N; i++)
			{
				intSlowRotorFwd[i] = intRotor3[(intSlowRingSetting + i)%N];
			}
			intSlowRotorNotchPosition = intNotchPositionOfRotor3;
			break;
		case 4:
			for(int i = 0; i < N; i++)
			{
				intSlowRotorFwd[i] = intRotor4[(intSlowRingSetting + i)%N];
			}
			intSlowRotorNotchPosition = intNotchPositionOfRotor4;
			break;
		case 5:
			for(int i = 0; i < N; i++)
			{
				intSlowRotorFwd[i] = intRotor5[(intSlowRingSetting + i)%N];
			}
			intSlowRotorNotchPosition = intNotchPositionOfRotor5;
			break;
		default:
			cout << "Error: Slow Rotor\n";
			break;
	}


	switch(intMedium)
	{
		case 1:
			for(int i = 0; i < N; i++)
			{
				intMediumRotorFwd[i] = intRotor1[(intMediumRingSetting + i)%N];
			}
			intMediumRotorNotchPosition = intNotchPositionOfRotor1;
			break;
		case 2:
			for(int i = 0; i < N; i++)
			{
				intMediumRotorFwd[i] = intRotor2[(intMediumRingSetting + i)%N];
			}
			intMediumRotorNotchPosition = intNotchPositionOfRotor2;
			break;
		case 3:
			for(int i = 0; i < N; i++)
			{
				intMediumRotorFwd[i] = intRotor3[(intMediumRingSetting + i)%N];
			}
			intMediumRotorNotchPosition = intNotchPositionOfRotor3;
			break;
		case 4:
			for(int i = 0; i < N; i++)
			{
				intMediumRotorFwd[i] = intRotor4[(intMediumRingSetting + i)%N];
			}
			intMediumRotorNotchPosition = intNotchPositionOfRotor4;
			break;
		case 5:
			for(int i = 0; i < N; i++)
			{
				intMediumRotorFwd[i] = intRotor5[(intMediumRingSetting + i)%N];
			}
			intMediumRotorNotchPosition = intNotchPositionOfRotor5;
			break;
		default:
			cout << "Error: Medium Rotor\n";
			break;
	}

	switch(intFast)
	{
		case 1:
			for(int i = 0; i < N; i++)
			{
				intFastRotorFwd[i] = intRotor1[(intFastRingSetting + i)%N];
			}
			intFastRotorNotchPosition = intNotchPositionOfRotor1;
			break;
		case 2:
			for(int i = 0; i < N; i++)
			{
				intFastRotorFwd[i] = intRotor2[(intFastRingSetting + i)%N];
			}
			intFastRotorNotchPosition = intNotchPositionOfRotor2;
			break;
		case 3:
			for(int i = 0; i < N; i++)
			{
				intFastRotorFwd[i] = intRotor3[(intFastRingSetting + i)%N];
			}
			intFastRotorNotchPosition = intNotchPositionOfRotor3;
			break;
		case 4:
			for(int i = 0; i < N; i++)
			{
				intFastRotorFwd[i] = intRotor4[(intFastRingSetting + i)%N];
			}
			intFastRotorNotchPosition = intNotchPositionOfRotor4;
			break;
		case 5:
			for(int i = 0; i < N; i++)
			{
				intFastRotorFwd[i] = intRotor5[(intFastRingSetting + i)%N];
			}
			intFastRotorNotchPosition = intNotchPositionOfRotor5;
			break;
		default:
			cout << "Error: Fast Rotor\n";
			break;
	}

	// Create the reverse versions of the forward stepping and fixed rotors.
	// Definition: a reverse rotor Rev[Fwd[i]] = i.
	for(int i = 0; i < N; i++)
	{
		intFastRotorRev[intFastRotorFwd[i]] = i;
		intMediumRotorRev[intMediumRotorFwd[i]] = i;
		intSlowRotorRev[intSlowRotorFwd[i]] = i;
		intFixedRotorRev[intFixedRotorFwd[i]] = i;
	}

	// Invoke the regex Contructor to create a regular expression object.
	// The following regular expression accepts only a single letter, A 
	// through D or a semicolon.   
	regex expression1("[a-dA-D;]{1}");
	cout << "*******************************************************************************\n";
	cout << "*******************   Welcome to the Enigma Program   *************************\n";
	cout << "*******************************************************************************\n";
	cout << "\n\n";
	cout << "Initial Key Code:\n";
	cout << "Slow Key: " << convertNumberToString(SlowTopIndex) << "  Medium Key: " << convertNumberToString(MediumTopIndex) << "  Fast Key: " << convertNumberToString(FastTopIndex) << "\n\n";
	cout << "Enter the character [a-d,A-D] to be encrypted or decrypted.\n";
	cout << "To exit the Enigma program, enter the sentinel character ';'.\n";
	while(boolInputFormatIsCorrect == false)
	{
		cout << "Enter the single letter here: ";
		// Note, we are using the getline() Function, cf. pp. 69-70 of 
		// Deitel, instead of the cin Function so that we can read 
		// even erroneous inputs with imbedded spaces.
		// cin >> stringInput;
		getline(cin, stringInput);
		if(regex_match(stringInput,expression1))
		{
			// Format of input is correct.
			// Use string Class functions to perform conversions 
			// between Type string and primitive types such as 
			// int, double, etc.  See pp. 714-717 of Chapter 18
			// in Deitel.
			istringstream inputString(stringInput);
			inputString >> charInputLetter;

			// Check for the sentinel character.
			if(charInputLetter == ';')
			{
				// The input is the sentinel character.
				// Reset the boolean flag to exit the while loop.
				boolInputFormatIsCorrect = true;
			}
			else
			{
				// The input is not the sentinel character.
				// Convert the letter to uppercase if it is lowercase.
				charInputLetter = toupper(charInputLetter);
				// Continue with the Enigma program.

				// Invoke the inline function to convert a character to an integer
				intKeyboardOutputToPlugBoardInput =  convertCharToNumber(charInputLetter);

	
				// Interface Descriptions:
				// 1) Fixed Entity to Fixed Entity, e.g., Keyboard to Plug Board, or Plug Board to Fixed Rotor
				//		Input1 index maps to output1 index, input2 index [= output1] maps to output2 index.
				//		Expanation: This is the most obvious of all the interfaces because there is no relative
				//		motion between the two parts of the interface.  A signal applied to the nth contact on the 
				//		input side connects directly to the nth contact on the output side.
				// 2) Fixed Entity to Rotating Entity, e.g., Fixed Rotor to Forward Fast Rotor.
				//		Input1 index maps to output1 index, input2 index [= (topIndex2 + output1)%N] maps to output2 index.
				//		Explanation: In this interface, the second part rotates with respect to the first,
				//		which is fixed, and so a signal leaving the nth contact on the output (fixed) side 
				//		connects to a contact displaced forward by the key code of the stepping rotor in question.
				// 3) Rotating Entity to Rotating Entity, e.g., Forward Fast Rotor to Foward Medium Rotor.
				//		Input1 index maps to output1 index, input2 index [= (topIndex2 + output1 - topIndex1)%N] maps to output2 index.
				//		Explanation: In this interface, both parts rotate, which means that the nth contact on the 
				//		first stepping rotor is displaced backward by its key code and then displaced 
				//		forward by the key code of the second rotor.
				// 4) Rotating Entity to Fixed Entity, e.g., Forward Slow Rotor to Reflector.
				//		Input1 index maps to output1 index, input2 index [= (output1 - topIndex1)%N] maps to output2 index.
				//		Explanation: In this interface, the first part rotates with respect to the second,
				//		which is fixed, and so a signal leaving the nth contact on the output (rotating) side 
				//		is displaced backward by the key code of the stepping rotor in question. 
				//		

				// Plug Board 
				// Direction: input from the Keyboard, output to Plug Board.
				intPlugBoardOutputToFixedRotorInput = intPlugBoard[intKeyboardOutputToPlugBoardInput];

				// Fixed Rotor
				// Direction: input from the Plug Board, output to Fixed Rotor.
				intFixedRotorOutputToFastRotorInput = intFixedRotorFwd[intPlugBoardOutputToFixedRotorInput];

				// Forward Fast Rotor
				// Direction: input from Fixed Rotor, output to Forward Medium Rotor.
				// Pre-increment the top index, but do so without pointing beyond the end index of the array.
				FastTopIndex = (++FastTopIndex)%N;
				intFastRotorStepCounter++;
				intFastRotorOutputToMediumRotorInput = intFastRotorFwd[(FastTopIndex + intFixedRotorOutputToFastRotorInput)%N];
	
				// Forward Medium Rotor
				// Direction: input from the Forward Fast Rotor, output to Forward Slow Rotor.
				// Check if the Fast Rotor has reached a notch position.
				//
				// The following approach will work, but only in the case of the default initial 
				// key code, 000 [or AAA] and default notch position, 25 [or Z].  The problem is 
				// that the counter's value must be adjusted if the key code is a non-default 
				// value and the notch position is non-default value.  For example, assume the 
				// default notch position, but set the initial key code to 003 [or AAD].  In 
				// this case, it will only take a single key stroke to cause the Fast rotor to 
				// advance the Medium rotor, i.e., the counter should have been pre-incremented 
				// to the value of 3, and not left at 0.
				//if(intFastRotorStepCounter%N == 0)
				//{
				//	// Notch position reached.
				//	MediumTopIndex = (++MediumTopIndex)%N;
				//	intMediumRotorStepCounter++;
				//}
				//else
				//{
				//	// Notch position not reached.
				//	// Do nothing.
				//}
				// A far easier way to advanced the Medium rotor is to simply test the state 
				// of the Fast rotor for the transition from the notch position to the position
				// after it.
				if(FastTopIndex == (intFastRotorNotchPosition + 1)%N)
				{
					// Notch position reached.
					MediumTopIndex = (++MediumTopIndex)%N;
					intMediumRotorStepCounter++;
				}
				else
				{
					// Notch position not reached.
					// Do nothing.
				}
				// Check if the modulo index is negative.
				if((MediumTopIndex + intFastRotorOutputToMediumRotorInput - FastTopIndex)%N < 0)
				{
					// Index less than zero.
					intTempIndex = N + (MediumTopIndex + intFastRotorOutputToMediumRotorInput - FastTopIndex)%N;
				}
				else
				{
					// Index greater than or equal to zero
					intTempIndex = (MediumTopIndex + intFastRotorOutputToMediumRotorInput - FastTopIndex)%N;
				}
				intMediumRotorOutputToSlowRotorInput = intMediumRotorFwd[intTempIndex];
				// Forward Slow Rotor
				// Direction: input from the Forward Medium Rotor, output to the Reflector.
				// Check if the Medium Rotor has reached a notch position.
				//
				// WARNING, the following if statement will not work properly due to a subtle problem with 
				// its conditional clause.  The conditional clause in the following if statement will create 
				// a race condition in the Slow Rotor, i.e., when intMediumRotorStepCounter reaches a value 
				// such that intMediumRotorStepCounter%N == 0 [AND intMediumRotorStepCounter != 0], each 
				// time one gets to this if statement, the first block will be executed.  The reason this 
				// is a problem is that the first block of the if statement should only execute the first 
				// time intMediumRotorStepCounter reaches a particular value such that its modulus is zero. 
				// Since intMediumRotorStepCounter will stay at a given value for many steps of the Fast 
				// rotor, the first block of the if statement will keep executing if the given value of 
				// intMediumRotorStepCounter is such that intMediumRotorStepCounter%N == 0.  if one insists 
				// on using the variable intMediumRotorStepCounter, then the only way to prevent a race 
				// condition is not to check for the value of the variable but, instead, check for the 
				// transition to that value.  This is akin, in digital electronics, to the difference 
				// between a level triggered clock input to a flip-flop versus an edge triggered clock 
				// input to a flip-flop.
				// Definition: Race condition - if the Slow rotor key code changes fast than that of 
				// the Medium rotor, for example, that is a race condition.
				//  if((intMediumRotorStepCounter%N == 0) && (intMediumRotorStepCounter != 0))
				//  {
				//	  // Notch position reached.
				//	  SlowTopIndex = (++SlowTopIndex)%N;
				//	  intSlowRotorStepCounter++;
				//  }
				//  else
				//  {
				//	  // Notch position not reached.
				//	  // Do nothing.
				//  }
				// The following if statement eliminates the race condition by examining the variable 
				// intFastRotorStepCounter, which always changes each time a key on the keyboard is 
				// pressed.  Because intFastRotorStepCounter always changes, it never dwells at a 
				// given value for more than one step [key press].  
				//
				// The following approach will work, but only in the case of the default initial 
				// key code, 000 [or AAA] and default notch position, 25 [or Z].  The problem is 
				// that the counter's value must be adjusted if the key code is a non-default 
				// value and the notch position is non-default value.
				//if((intFastRotorStepCounter%(N*N) == 0))
				//{
				//	// Notch position reached.
				//	SlowTopIndex = (++SlowTopIndex)%N;
				//	intSlowRotorStepCounter++;
				//}
				//else
				//{
				//	// Notch position not reached.
				//	// Do nothing.
				//}
				// A far easier way to advanced the Slow rotor is to simply test the state 
				// of the Medium rotor and the Fast rotor for the transition from the notch 
				// position to the position after them.  In other words, by checking the state 
				// of both the Medium and Fast rotors, we avoid the race condition that happens 
				// when we check just the state of the Medium rotor.  
				if(MediumTopIndex == (intMediumRotorNotchPosition + 1)%N && 
					FastTopIndex == (intFastRotorNotchPosition + 1)%N)
				{
					// Notch position reached.
					SlowTopIndex = (++SlowTopIndex)%N;
					intSlowRotorStepCounter++;
				}
				else
				{
					// Notch position not reached.
					// Do nothing.
				}
				// Check if the modulo index is negative.
				if((SlowTopIndex + intMediumRotorOutputToSlowRotorInput - MediumTopIndex)%N < 0)
				{
					// Index less than zero.
					intTempIndex = N + (SlowTopIndex + intMediumRotorOutputToSlowRotorInput - MediumTopIndex)%N;
				}
				else
				{
					// Index greater than or equal to zero
					intTempIndex = (SlowTopIndex + intMediumRotorOutputToSlowRotorInput - MediumTopIndex)%N;
				}
				intSlowRotorOutputToReflectorInput = intSlowRotorFwd[intTempIndex];
				// Reflector
				// Direction: input from the Forward Slow Rotor, output to the Reverse Slow Rotor.
				// Check if the modulo index is negative.
				if((intSlowRotorOutputToReflectorInput - SlowTopIndex)%N < 0)
				{
					// Index less than zero.
					intTempIndex = N + (intSlowRotorOutputToReflectorInput - SlowTopIndex)%N;
				}
				else
				{
					// Index greater than or equal to zero
					intTempIndex = (intSlowRotorOutputToReflectorInput - SlowTopIndex)%N;
				}
				intReflectorOutputToSlowRotorInput = intReflector[intTempIndex];

				// Reverse Slow Rotor
				// Direction: input from the Reflector, output to the Reverse Medium Rotor.
				intSlowOutputToMediumRotorInput = intSlowRotorRev[(SlowTopIndex + intReflectorOutputToSlowRotorInput)%N];

				// Reverse Medium Rotor
				// Direction: input from the Reverse Slow Rotor, output to the Reverse Fast Rotor.
				// Check if the modulo index is negative.
				if((MediumTopIndex + intSlowOutputToMediumRotorInput - SlowTopIndex)%N < 0)
				{
					// Index less than zero.
					intTempIndex = N + (MediumTopIndex + intSlowOutputToMediumRotorInput - SlowTopIndex)%N;
				}
				else
				{
					// Index greater than or equal to zero
					intTempIndex = (MediumTopIndex + intSlowOutputToMediumRotorInput - SlowTopIndex)%N;
				}
				intMediumOutputToFastRotorInput = intMediumRotorRev[intTempIndex];

				// Reverse Fast Rotor
				// Direction: input from Reverse Medium Rotor, output to the Fixed Rotor.
				// Check if the modulo index is negative.
				if((FastTopIndex + intMediumOutputToFastRotorInput - MediumTopIndex)%N < 0)
				{
					// Index less than zero.
					intTempIndex = N + (FastTopIndex + intMediumOutputToFastRotorInput - MediumTopIndex)%N;
				}
				else
				{
					// Index greater than or equal to zero
					intTempIndex = (FastTopIndex + intMediumOutputToFastRotorInput - MediumTopIndex)%N;
				}
				intFastOutputToFixedRotorInput = intFastRotorRev[intTempIndex];

				// Fixed Rotor
				// Direction: input from the Reverse Fast Rotor, output to the Plug Board
				// Check if the modulo index is negative.
				if((intFastOutputToFixedRotorInput - FastTopIndex)%N < 0)
				{
					// Index less than zero.
					intTempIndex = N + (intFastOutputToFixedRotorInput - FastTopIndex)%N;
				}
				else
				{
					// Index greater than or equal to zero
					intTempIndex = (intFastOutputToFixedRotorInput - FastTopIndex)%N;
				}
				intFixedRotorOutputToPlugBoardInput = intFixedRotorRev[intTempIndex];
		
				// Plug Board
				// Direction: input from the Fixed Rotor, output to the Display.
				intPlugBoardOutputToDisplayInput = intPlugBoard[intFixedRotorOutputToPlugBoardInput];

				// Display 
				// Direction: input from the  Plug Board.

				cout << "\n" << "Input character: " << charInputLetter << "\n";
				//printf("%3d %3d %3d\n",  intSlowRotorStepCounter - 1, intMediumRotorStepCounter -1, intFastRotorStepCounter - 1);
				// WARNING, for some weird reason, the following printf() statement causes an access 
				// violation during runtime.
				//printf("%3s %3s %3s\n",  convertNumberToString(SlowTopIndex), convertNumberToString(MediumTopIndex), convertNumberToString(FastTopIndex));
				cout << "Slow Key: " << convertNumberToString(SlowTopIndex) << "  Medium Key: " << convertNumberToString(MediumTopIndex) << "  Fast Key: " << convertNumberToString(FastTopIndex) << "\n";
				/*cout << intFastRotorOutputToMediumRotorInput << intMediumRotorOutputToSlowRotorInput << intSlowRotorOutputToReflectorInput << "\n";
				for(int i = 0; i < N; i++)
				{
					cout << intFastRotorFwd[i] << intMediumRotorFwd[i] << intSlowRotorFwd[i] << "\n";
				}*/
				cout << "Output character: " << convertNumberToString(intPlugBoardOutputToDisplayInput) << endl;


			} // End of the inner if statement.
		}
		else
		{
			// Format of input is incorrect.
			// Do nothing.
			cout << "ERROR: Invalid Format or Character. \n\n";
		} // End of the outer if statement

	} // End of the while loop.
}