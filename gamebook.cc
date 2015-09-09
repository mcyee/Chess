#include "gamebook.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// How should each game be recorded? 
// Record the white player, black player, date. 
// (Other information can be added later.)
// Obviously the unique game id should also be 
// created which will be the filename. 

GameBook::GameBook(string gamesFile): gamesFile(gamesFile) {
	fstream f;
	f.open(gamesFile.c_str());
	f >> numGames;
	string input;
	getline(f, input);
	int id;
	string black;
	string white;
	string date;
	for(int i = 0; i < numGames; i++) {
		getline(f, input);
		stringstream ss(input);
		ss >> id >> white >> black >> date;
		GameRecord *addMe = new GameRecord(id, white, black, date);
		games.push_back(addMe);
	}
}

void GameBook::run() {
	cout << "This will have more capabilities, but right now it will just print this." << endl;
	cout << "And display all the current games." << endl;
	displayGames();
}

void GameBook::displayGames() {
	vector<GameRecord *>::iterator i;
	for(i = games.begin(); i != games.end(); i++) {
		(*i)->printInfo();
	}
}

GameBook::~GameBook() {
	vector<GameRecord *>::iterator i;
	for(i = games.begin(); i != games.end(); i++) {
		delete (*i);
	}
}
