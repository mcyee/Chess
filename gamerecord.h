#ifndef __GAMERECORD_H__
#define __GAMERECORD_H__

#include <string>

class GameRecord {
	int id;
	std::string white;
	std::string black;
	std::string date;
public:
	GameRecord(int, std::string, std::string, std::string);
	void printInfo();
};

#endif
