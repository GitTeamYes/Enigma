#include "enigma.h"
using namespace std;


int main()
{
	char letterToBeEncrypted;
	int rotor1Counter=0, rotor2Counter=0,rotor3Counter=0;
	char ROTOR1[26]={'j','g','d','q','o','x','u','s','c','a','m','i','f','r','v','t','p','n','e','w','k','b','l','z','y','h'};
	char ROTOR2[26]={'n','t','z','p','s','f','b','o','k','m','w','r','c','j','d','i','v','l','a','e','y','u','x','h','g','q'};
	char ROTOR3[26]={'j','v','i','u','b','h','t','c','d','y','a','k','e','q','z','p','o','s','g','x','n','r','m','w','f','l'};
	char REFLECTOR[26]={'q','y','h','o','g','n','e','c','v','p','u','z','t','f','d','j','a','x','w','m','k','i','s','r','b','l'};
	char firstSwap,secondSwap,thirdSwap,forthSwap,fithSwap;

	//counter control
	rotor1Counter++;
	if(rotor1Counter==26){
	rotor1Counter=0;
	}
	else if(rotor2Counter==26){
	rotor2Counter=0;
	}
	else if(rotor3Counter==26){
	rotor3Counter=0;
	}
	else if(rotor1Counter==17){
		rotor2Counter++;
		if(rotor2Counter==5){
			rotor3Counter++;
		}
	}

	cout<<"Enter a letter to encrypt or decrypt"<<endl;
	cin<<letterToBeEncrypted<<endl;
	
	//initial static substitution
	if(letterToBeEncrypted=='a'){
		firstSwap='q';
	}
	else if(letterToBeEncrypted=='b'){
		firstSwap='w';
	}
	else if(letterToBeEncrypted=='c'){
		firstSwap='e';
	}
	else if(letterToBeEncrypted=='d'){
		firstSwap='r';
	}
	else if(letterToBeEncrypted=='e'){
		firstSwap='t';
	}
	else if(letterToBeEncrypted=='f'){
		firstSwap='z';
	}
	else if(letterToBeEncrypted=='g'){
		firstSwap='u';
	}
	else if(letterToBeEncrypted=='h'){
		firstSwap='i';
	}
	else if(letterToBeEncrypted=='i'){
		firstSwap='o';
	}
	else if(letterToBeEncrypted=='j'){
		firstSwap='a';
	}
	else if(letterToBeEncrypted=='k'){
		firstSwap='s';
	}
	else if(letterToBeEncrypted=='l'){
		firstSwap='d';
	}
	else if(letterToBeEncrypted=='m'){
		firstSwap='f';
	}
	else if(letterToBeEncrypted=='n'){
		firstSwap='g';
	}
	else if(letterToBeEncrypted=='o'){
		firstSwap='h';
	}
	else if(letterToBeEncrypted=='p'){
		firstSwap='j';
	}
	else if(letterToBeEncrypted=='q'){
		firstSwap='k';
	}
	else if(letterToBeEncrypted=='r'){
		firstSwap='p';
	}
	else if(letterToBeEncrypted=='s'){
		firstSwap='y';
	}
	else if(letterToBeEncrypted=='t'){
		firstSwap='x';
	}
	else if(letterToBeEncrypted=='u'){
		firstSwap='c';
	}
	else if(letterToBeEncrypted=='v'){
		firstSwap='v';
	}
	else if(letterToBeEncrypted=='w'){
		firstSwap='b';
	}
	else if(letterToBeEncrypted=='x'){
		firstSwap='n';
	}
	else if(letterToBeEncrypted=='y'){
		firstSwap='m';
	}
	else if(letterToBeEncrypted=='z'){
		firstSwap='l';
	}

	//rotor1 swap to be added

	//rotor2 swap to be added

	//rotor3 swap to be added

	//reflector swap to be added

}
