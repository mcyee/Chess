#include "gamerecord.h"
#include <iostream>

using namespace std;

GameRecord::GameRecord(int id, string white, string black, string date): 
	id(id), white(white), black(black), date(date) {}

void GameRecord::printInfo() {
	cout << id << " " << white << " " << black << " " << date << endl;
}
