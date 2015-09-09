#ifndef __GAMEBOOK_H__
#define __GAMEBOOK_H__

#include "gamerecord.h"
#include <string>
#include <vector>

// The puropse of this class is to deal with the gamesbook. Saving, 

class GameBook {
	std::string gamesFile;
	std::vector<GameRecord *> games;
	int numGames;
public:
	GameBook(std::string);
	void displayGames();
	void run();
};

#endif
