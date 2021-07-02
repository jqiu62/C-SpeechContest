#include "speechManager.h"
#include <string>
#include <iostream>
#include <ctime>
using namespace std;


int main()
{
	//generate random seed
	srand((unsigned int)time(NULL));

	SpeechManager speechManager;
	int choice = 0; // customer's choice

	while (true)
	{
		speechManager.showMenu();
		cin >> choice;
		switch (choice)
		{
		case(1):	//start
			speechManager.startSpeech();
			break;
		case(2):	//check record
			speechManager.showRecord();
			break;
		case(3):	//clear record
			speechManager.clearRecord();
			break;
		case(0):	//exit
			speechManager.exitSystem();
			break;
		default:
			system("cls");
		}
	}

	system("pause");
	return 0;
}