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
	cout << "And display all the current games. Type in \"help\" for more options." << endl;
	string input;
	cout << "~> ";
	string command;
	while(getline(cin, input)) {
		stringstream ss(input);
		ss >> command;
		if(command == "q" || command == "quit") {
			return;
		} else if(command == "open") {
			string file;
			ss >> file;
			cout << "opening " << file << endl;
			// initialize the controller and such. 
			cout << "closing " << file << endl;
		} else if(command == "new") {
			// run the newgame function which will initialize the players
			// and the played moves. Thsi should be done half in the 
			// GameBook file and half ain the controller file. 
			// Ie, make a dedicated "record main moves" function in 
			// Controller that records the moves that were played, 
			// jumps to the start node and then calls traverse so that 
			// the player can analyze the game. 
			cout << "tried to initialize a new game." << endl;
		} else if(command == "help") {
			// run the help function.
			cout << "quit, open, new, help, display." << endl;
		} else if(command == "display") {
			displayGames();
		} else {
			cout << "unrecognized command." << endl;
		}
		cout << "~> ";
	}
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
