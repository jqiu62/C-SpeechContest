#include "speechManager.h"
#include <iostream>

SpeechManager::SpeechManager() 
{
	//initiate
	this->initSpeech();
	this->createSpeaker();	//12 speakers
	this->loadRecord();		//load record of past matches
}

void SpeechManager::showMenu()
{
	cout << "****WELCOME To Speech Manager*******" << endl;
	cout << "************1 Start*****************" << endl;
	cout << "************2 Check*****************" << endl;
	cout << "************3 Clear*****************" << endl;
	cout << "************0 Exit******************" << endl;
	cout << "************************************" << endl;
	cout << endl;

}

void SpeechManager::initSpeech()
{
	//empty all competitors
	this->vAll.clear();
	this->vRound1.clear();
	this->vRound2.clear();
	this->pairedSpeaker.clear();

	this->record.clear();	//clear the record of past contest

	//initiate the round of speech
	this->roundIndex = 0;
}

void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i<nameSeed.size(); i++)
	{
		string name = "Speaker ";	// "Speaker A" ~ "Speaker L"
		name += nameSeed[i];

		Speaker speaker;
		speaker.speakerName = name;
		for (int j = 0; j < 2; j++) //intiate two round scores
		{
			speaker.speakerScore[j] = 0;
		}

		//initiate speaker vector
		this->vAll.push_back(i + 10001);	//all speakers before first round
		this->pairedSpeaker.insert(make_pair(i + 10001, speaker));	//all speakers stored as "number, speaker"
	}
}

void SpeechManager::startSpeech()
{
	//Round1 - draw-speech-show result - 6 out of 12
	this->speechDraw();
	this->speechContest();
	this->showScore();


	//Round2 - draw-speech-show result-save - 3 out of 6
	this->roundIndex++;
	this->speechDraw();
	this->speechContest();
	this->showScore();
	this->saveRecord();	//store top 3 winners

	//end of match
	cout << "*** End of the match! ***" << endl;

	//reset match and load record
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	system("pause");
	system("cls");
}

void SpeechManager::speechDraw()
{
	
	cout << "**************************" << endl;
	cout << "*** Round" << (this->roundIndex + 1) << " Draw ***" << endl;
	cout << "*** The result after draw: " << " ***" << endl;

	if (this->roundIndex == 0)
	{
		//Round1
		random_shuffle(vAll.begin(), vAll.end());	//draw		
		for (vector<int>::iterator it = vAll.begin(); it != vAll.end(); it++ )
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//Round2
		random_shuffle(vRound1.begin(), vRound1.end());
		for (vector<int>::iterator it = vRound1.begin(); it != vRound1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "**************************" << endl;
	system("pause");
	cout << endl;

}

void SpeechManager::speechContest()
{
	cout << "*** Round" << (this->roundIndex + 1) << "starts ***" << endl;

	multimap<double, int, greater<double>> groupScore; 
	/*stores each score in the same group as "average score - speaker number"
	and sort from highest to lowest of scores*/
	int numberOfGroupMember = 0; //index of group members
	vector<int> vTemp; //stores all qualified competitors

	if (this->roundIndex == 0)	
	{
		vTemp = vAll;	//round1
	}
	else
	{
		vTemp = vRound1;	//round2
	}

	int halfNumber = vAll.size()/2; //every 6 competitors form one group

	//iterate all qualified competitors
	for (vector<int>::iterator it = vTemp.begin(); it != vTemp.end(); it++)
	{
		numberOfGroupMember++;
		
		cout << "Scores of: " << *it << endl;
		//every competitor scored by 10 committee members
		deque<double> d;
		for (int i = 0; i<10; i++)
		{
			double score = (rand() % 200 + 800) / 10.f; //random score from 80-100
			cout << score << " ";
			d.push_back(score);
		}
		cout << endl;

		//rank, remove the highest and lowest
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();

		cout << "*** After removing highest and lowest ***" << endl;
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		cout << "Speaker number: " << *it << " Name: " << pairedSpeaker[*it].speakerName << " Average score: " << avg << endl;
		cout << endl;

		//store average score into map
		this->pairedSpeaker[*it].speakerScore[this->roundIndex] = avg;
		//store each score in one group, sort and show the top 3 out of 6
		groupScore.insert(make_pair(avg, *it));
		//show qualified speakers from each group
		if (numberOfGroupMember % halfNumber == 0)	//every 6 speakers form one group
		{
			cout << "*** List of speakers from Group" << numberOfGroupMember / halfNumber << ": ***" << endl;
			//print group scores
			for (multimap<double, int, greater<double>>::iterator groupIt = groupScore.begin(); groupIt!= groupScore.end(); groupIt++) 
			{
				cout << "Speaker number: " << groupIt->second << " Name: " << this->pairedSpeaker[groupIt->second].speakerName << " Score: " << groupIt->first << endl;
			}
			//store top 3 from each group as the qualifiers
			int top3Index = 0;
			for (multimap<double, int, greater<double>>::iterator groupIt = groupScore.begin(); groupIt != groupScore.end() && top3Index < 3; groupIt++, top3Index++)
			{
				if(this->roundIndex == 0)
				{
					vRound1.push_back((*groupIt).second);
				}
				else
				{
					vRound2.push_back((*groupIt).second);
				}
			}
			
			groupScore.clear(); //clear group score
			cout << endl;
			system("pause");
		}
	}
	cout << "*** End of Round" << this->roundIndex + 1 << "! ***" << endl;
	cout << endl;
	system("pause");
}

void SpeechManager::showScore()
{
	cout << "*** Round" << (this->roundIndex + 1) << " qualified speakers: ***" << endl;
	vector<int> vTemp2;
	if (this->roundIndex == 0)
	{
		vTemp2 = vRound1;
	}
	else
	{
		vTemp2 = vRound2;
	}

	for (vector<int>::iterator it = vTemp2.begin(); it != vTemp2.end(); it++)
	{
		cout << "Speaker number: " << *it << " Name: " << this->pairedSpeaker[*it].speakerName << " Score: " << this->pairedSpeaker[*it].speakerScore[this->roundIndex] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->showMenu();
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	//write record of top 3 (Round 2 winners)
	for (vector<int>::iterator it = vRound2.begin(); it!=vRound2.end(); it++) 
	{
		ofs << *it << "," << this->pairedSpeaker[*it].speakerScore[1] << ",";
	}
	ofs<<endl;
	ofs.close();
	cout << "*** Record saved! ***" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);	//read file
	if(!ifs.is_open())	//file not exist
	{
		this->fileIsEmpty = true;
		//cout << "*** File doesn't exist. ***" << endl;
		ifs.close();
		return;
	}
	//empty file with no content
	char ch;
	ifs >> ch;
	if(ifs.eof())
	{
		//cout << "*** Empty file! ***" << endl;
		this->fileIsEmpty = true;
		ifs.close();
	}

	//continue reading if the file is not empty
	this->fileIsEmpty = false;
	ifs.putback(ch);	//put back the character

	string data;
	int indexOfMatch = 0;	//index of match
	while (ifs >> data) 
	{
		int pos = -1;	//the position of "," in a string
		int start = 0;	//the position to start searching
		vector<string>v;	//store strings of each line

		while(true)	//break only when line ends (no "," found)
		{
			pos = data.find(",", start);
			if (pos == -1) 
			{
				//"," not found in file
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		
		this->record.insert(make_pair(indexOfMatch, v));	//load data into record
		indexOfMatch++;
	}

	ifs.close();
	cout << "*** 1st place of past matches: ***" << endl;
	for(map<int, vector<string>>::iterator it = record.begin(); it!=record.end(); it++)
	{
		cout << "*** Match " << it->first << " 1st Prize Winner: Speaker number: " << it->second[0] << " Score: " << it->second[1] << endl;
		//it->second refers to winners
	}

}

void SpeechManager::showRecord()
{
	cout << "*** Record of past matches: ***" << endl;
	if (this->fileIsEmpty) 
	{
		cout << "*** Empty file or file not exist! ***" << endl;
	}
	else 
	{
		for (int i = 0; i < this->record.size(); i++)
		{
			cout << "*** Match " << i + 1 << " 1st prize: " << this->record[i][0] << " Score: " << this->record[i][1] << " "
				<< " 2nd prize: " << this->record[i][2] << " Score: " << this->record[i][3] << " "
				<< " 3rd prize: " << this->record[i][4] << " Score: " << this->record[i][5] << endl;
		}
	}

	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()
{
	cout << "******* Clear all record? *******" << endl;
	cout << "************ 1 YES **************" << endl;
	cout << "************ 2 NO ***************" << endl;

	int choice = 0;
	cin >> choice;
	if (choice == 1) 
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//initialize
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();

		cout << "*** Successfully clear all record! ***" << endl;
	}

	system("pause");
	system("cls");
}

void SpeechManager::exitSystem()
{
	cout << "*** Thank you for using SpeechManager.***" << endl;
	system("pause");
	exit(0);

}

SpeechManager::~SpeechManager()
{
}