	



	int inputVal0;
	int inputVal1;
	int inputVal2;
	int inputVal3;


	int intKeyboardOutputToPlugBoardInput;
	int intPlugBoardOutputToFixedRotorInput;
	int intFixedRotorOutputToFastRotorInput;
	int intFastRotorOutputToMediumRotorInput;
	int intMediumRotorOutputToSlowRotorInput;
	int intSlowRotorOutputToReflectorInput;

	
	int intReflectorOutputToSlowRotorInput;
	int intSlowOutputToMediumRotorInput;
	int intMediumOutputToFastRotorInput;
	int intFastOutputToFixedRotorInput;
	int intFixedRotorOutputToPlugBoardInput;
	int intPlugBoardOutputToDisplayInput;


	
	const int N = 4;
	
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
	
	int intFixedRotorFwd[N] = {0, 1, 2, 3};
	int intFixedRotorRev[N];
	
	int intReflector[N] = {3, 2, 1, 0};

	
	int intSlowRotorFwd[N];
	int intMediumRotorFwd[N];
	int intFastRotorFwd[N];

	int intSlowRotorNotchPosition;
	int intMediumRotorNotchPosition;
	int intFastRotorNotchPosition;

	int intSlowRotorRev[N];
	int intMediumRotorRev[N];
	int intFastRotorRev[N];

	
	int FastTopIndex;
	int MediumTopIndex;
	int SlowTopIndex;
	
	int TempFastTopIndex;
	int TempMediumTopIndex;
	int TempSlowTopIndex;


	
	int intFastRotorStepCounter = 0;
	int intMediumRotorStepCounter = 0;
	int intSlowRotorStepCounter = 0;

	//bool boolInputFormatIsCorrect = false;
	int intTempIndex;
	int intTemp = 1;

	
	int intSlow = 3;
	int intMedium = 2;
	int intFast = 1;

	
	int intSlowRingSetting = 0;
	int intMediumRingSetting = 0;
	int intFastRingSetting = 0;

	 
	int intPlugBoard[N] = {0, 1, 2, 3};

	


void setup()
{

	pinMode(9, INPUT_PULLUP);
	pinMode(10, INPUT_PULLUP);
	pinMode(11, INPUT_PULLUP);
	pinMode(12, INPUT_PULLUP);

	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);

	FastTopIndex = 0;
	MediumTopIndex = 0;
	SlowTopIndex = 0;



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
			//cout << "Error: Slow Rotor\n";
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
			//cout << "Error: Medium Rotor\n";
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
			//cout << "Error: Fast Rotor\n";
			break;
	}

	
	for(int i = 0; i < N; i++)
	{
		intFastRotorRev[intFastRotorFwd[i]] = i;
		intMediumRotorRev[intMediumRotorFwd[i]] = i;
		intSlowRotorRev[intSlowRotorFwd[i]] = i;
		intFixedRotorRev[intFixedRotorFwd[i]] = i;
	}
}

	
void loop()
{
				
		if(digitalRead(9) == 0 || digitalRead(10) == 0 || digitalRead(11) == 0 || digitalRead(12) == 0)
		{
				
				inputVal0 = digitalRead(9);
				inputVal1 = digitalRead(10);
				inputVal2 = digitalRead(11);
				inputVal3 = digitalRead(12);
				if(inputVal0 == 0)
				{
					intKeyboardOutputToPlugBoardInput = 0;
				}
				if(inputVal1 == 0)
				{
					intKeyboardOutputToPlugBoardInput = 1;
				}
				if(inputVal2 == 0)
				{
					intKeyboardOutputToPlugBoardInput = 2;
				}
				if(inputVal3 == 0)
				{
					intKeyboardOutputToPlugBoardInput = 3;
				}
				
	

				
				intPlugBoardOutputToFixedRotorInput = intPlugBoard[intKeyboardOutputToPlugBoardInput];

				
				intFixedRotorOutputToFastRotorInput = intFixedRotorFwd[intPlugBoardOutputToFixedRotorInput];

				
				FastTopIndex = (++FastTopIndex)%N;
				intFastRotorStepCounter++;
				intFastRotorOutputToMediumRotorInput = intFastRotorFwd[(FastTopIndex + intFixedRotorOutputToFastRotorInput)%N];
	
				
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
				
				if(MediumTopIndex == (intMediumRotorNotchPosition + 1)%N && 
					FastTopIndex == (intFastRotorNotchPosition + 1)%N)
				{
					SlowTopIndex = (++SlowTopIndex)%N;
					intSlowRotorStepCounter++;
				}
				else
				{
					
				}

				if((SlowTopIndex + intMediumRotorOutputToSlowRotorInput - MediumTopIndex)%N < 0)
				{
					
					intTempIndex = N + (SlowTopIndex + intMediumRotorOutputToSlowRotorInput - MediumTopIndex)%N;
				}
				else
				{
					
					intTempIndex = (SlowTopIndex + intMediumRotorOutputToSlowRotorInput - MediumTopIndex)%N;
				}
				intSlowRotorOutputToReflectorInput = intSlowRotorFwd[intTempIndex];
				
				if((intSlowRotorOutputToReflectorInput - SlowTopIndex)%N < 0)
				{
					intTempIndex = N + (intSlowRotorOutputToReflectorInput - SlowTopIndex)%N;
				}
				else
				{
					intTempIndex = (intSlowRotorOutputToReflectorInput - SlowTopIndex)%N;
				}
				intReflectorOutputToSlowRotorInput = intReflector[intTempIndex];

				intSlowOutputToMediumRotorInput = intSlowRotorRev[(SlowTopIndex + intReflectorOutputToSlowRotorInput)%N];

				
				if((MediumTopIndex + intSlowOutputToMediumRotorInput - SlowTopIndex)%N < 0)
				{
					intTempIndex = N + (MediumTopIndex + intSlowOutputToMediumRotorInput - SlowTopIndex)%N;
				}
				else
				{
					intTempIndex = (MediumTopIndex + intSlowOutputToMediumRotorInput - SlowTopIndex)%N;
				}
				intMediumOutputToFastRotorInput = intMediumRotorRev[intTempIndex];

				
				if((FastTopIndex + intMediumOutputToFastRotorInput - MediumTopIndex)%N < 0)
				{
					intTempIndex = N + (FastTopIndex + intMediumOutputToFastRotorInput - MediumTopIndex)%N;
				}
				else
				{
					intTempIndex = (FastTopIndex + intMediumOutputToFastRotorInput - MediumTopIndex)%N;
				}
				intFastOutputToFixedRotorInput = intFastRotorRev[intTempIndex];

				if((intFastOutputToFixedRotorInput - FastTopIndex)%N < 0)
				{
					intTempIndex = N + (intFastOutputToFixedRotorInput - FastTopIndex)%N;
				}
				else
				{
					// Index greater than or equal to zero
					intTempIndex = (intFastOutputToFixedRotorInput - FastTopIndex)%N;
				}
				intFixedRotorOutputToPlugBoardInput = intFixedRotorRev[intTempIndex];
		

				intPlugBoardOutputToDisplayInput = intPlugBoard[intFixedRotorOutputToPlugBoardInput];


				//cout << "\n" << "Input character: " << charInputLetter << "\n";
				//cout << "Slow Key: " << convertNumberToString(SlowTopIndex) << "  Medium Key: " << convertNumberToString(MediumTopIndex) << "  Fast Key: " << convertNumberToString(FastTopIndex) << "\n";
				//cout << "Output character: " << convertNumberToString(intPlugBoardOutputToDisplayInput) << endl;
				if(intPlugBoardOutputToDisplayInput == 0)
				{
					digitalWrite(5, HIGH);
				}
				if(intPlugBoardOutputToDisplayInput == 1)
				{
					digitalWrite(6, HIGH);
				}
				if(intPlugBoardOutputToDisplayInput == 2)
				{
					digitalWrite(7, HIGH);
				}
				if(intPlugBoardOutputToDisplayInput == 3)
				{
					digitalWrite(8, HIGH);
				}
                                delay(2000);
 			        digitalWrite(5, LOW);
			        digitalWrite(6, LOW);
			        digitalWrite(7, LOW);
			        digitalWrite(8, LOW);                               
		}
		else
		{
			digitalWrite(5, LOW);
			digitalWrite(6, LOW);
			digitalWrite(7, LOW);
			digitalWrite(8, LOW);
		}
		
} // End of loop loop.
