#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>
#include "speaker.h"
using namespace std;

//speech manager
class SpeechManager 
{
public:
	SpeechManager();
	~SpeechManager();

	//initialize
	void showMenu();	//menu
	void initSpeech();	//initiate speech
	void createSpeaker();	//create speaker

	//start speech
	void startSpeech();
	void speechDraw();
	//contest
	void speechContest();
	//show score
	void showScore();
	//write record of top3 into csv file
	void saveRecord();

	//Load record from csv file into "record"
	void loadRecord();

	void showRecord();	//record of top 3 winners
	void clearRecord();

	void exitSystem(); //exit system


	//round index
	int roundIndex;
	//all competitors, round-1 winners, round-2 winners
	vector<int> vAll;
	vector<int> vRound1;
 	vector<int> vRound2;

	//every competitor and his/her code
	map<int, Speaker> pairedSpeaker;

	//file check
	bool fileIsEmpty;
	//record of previous contests and their top 3 winners
	map<int, vector<string>> record;

};
