#include "gamebook.h"
#include "controller.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// How should each game be recorded? 
// Record the white player, black player, date. 
// (Other information can be added later.)
// Obviously the unique game id should also be 
// created which will be the filename. 

string int2str(int input) {
	stringstream s;
	string output;
	s << input;
	s >> output;
	return output;
}

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
	while(getline(cin, input)) {
//		cout << "The line we got is: " << input << endl;
		stringstream ss(input);
		string command;
		ss >> command;
		if(command == "q" || command == "quit") {
			return;
		} else if(command == "open") {
			string file;
			ss >> file;
			fstream f;
			f.open(file.c_str());
			Controller k(f, f, "gamebook");
			k.buildList();
			k.traverse();
		} else if(command == "new") {
			// run the newgame function which will initialize the players
			// and the played moves. Thsi should be done half in the 
			// GameBook file and half ain the controller file. 
			// Ie, make a dedicated "record main moves" function in 
			// Controller that records the moves that were played, 
			// jumps to the start node and then calls traverse so that 
			// the player can analyze the game. 
			string white;
			string black;
			string date;
			ss >> white >> black >> date;
			numGames++;
			GameRecord *addMe = new GameRecord(numGames, white, black, date);
			games.push_back(addMe);
			
			string myfile = int2str(numGames) + ".txt";
			ofstream init(myfile.c_str());
			init.open(myfile.c_str());
			init << flush;
			init.close();
			fstream f(myfile.c_str());
			Controller k(f, f, "gamebook");
			k.buildGame();
			k.traverse();
			f.close();
			save();
		} else if(command == "help") {
			// run the help function.
			cout << "quit, open, new, help, display." << endl;
		} else if(command == "display") {
			displayGames();
		} else if(command == "") {
			// do nothing, really hacky fix here.
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

void GameBook::save() {
	fstream f;
	f.open(gamesFile.c_str());
	vector<GameRecord *>::iterator i;
	int j = 1;
	f << numGames << endl;
	for(i = games.begin(); i != games.end(); i++) {
		f << j << " " << (*i)->getWhite() << " " << (*i)->getBlack();
		f << " " << (*i)->getDate() << endl;
		j++;
	}
}
		
		

GameBook::~GameBook() {
	vector<GameRecord *>::iterator i;
	for(i = games.begin(); i != games.end(); i++) {
		delete (*i);
	}
}
