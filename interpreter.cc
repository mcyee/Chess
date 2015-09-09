#include "interpreter.h"
#include "controller.h"
#include "gamebook.h"
#include <sstream>

using namespace std;	
Interpreter::Interpreter(): openingBook("prepfile.txt"), gameBook("games.txt") {}

void Interpreter::initiate() {
	cout << "Welcome to this chess program!" << endl;
	cout << "Type \"help\" or \"help <cmd>\"" << endl;
	cout << "For general instructions or help" << endl;
	cout << "on a specific command." << endl;
	cout << "~> ";
	string input;
	while(getline(cin, input)) {
//		cout << input << endl; 		// ERASE THIS LATER
		stringstream ss(input);
		string command;
		ss >> command;
//		cout << command << endl; // ERASE THIS LATER TOO
		if(command == "q" || command == "quit") {
			cout << "Exiting." << endl;
			return;
		} else if(command == "help") {
			string arg;
			if(ss >> arg) {
				help(arg);	// This should be made into a default parameter and such to avoid: 
			} else {
				help("");	// this hacky thing. 
			}
		} else if(command == "openings") {
			fstream f;
			f.open(openingBook.c_str());
		   	fstream g;
			g.open(openingBook.c_str());
			cout << "Point A" << endl;
			Controller k(f, g, "opening");
			cout << "Point B" << endl;
			k.buildList();
			cout << "Point C" << endl;
			k.traverse();
			cout << "Point D" << endl;
			cout << "Done running the openings tool." << endl;
		} else if(command == "gamebook") {
			cout << "Running the gamebook tool" << endl;
			GameBook gb = GameBook(gameBook);
			gb.run();
			cout << "Done running the tool" << endl;
		} else if(command == "play") {
			cout << "Initiating a game." << endl;
			cout << "Done playing." << endl;
		} else {
			cout << "Command not recognized. Please type" << endl;
			cout << "\"help\" to see possible commands." << endl;
		}
		cout << "~> ";
	}
	cout << "Left while loop." << endl;
}

void Interpreter::help(string arg) {
	if(arg == "") {
		cout << "These are the current possible commands:" << endl;
		cout << "\"openings\": Use the opening book tool." << endl;
		cout << "\"gamebook\": Use the gamebook tool." << endl;
		cout << "\"play\": Play a game of chess." << endl;
	} // Have a bunch of else ifs to explain each possible command in detail.
}
