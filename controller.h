#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "tree.h"
#include <map>
#include <fstream>
#include <string>

class Controller {
	std::fstream &read;
	std::fstream &write;
	int numNodes;
	std::string player;
	Tree *root;
	std::map<std::string, Tree *> nodeList;
	std::string inputDescription(bool);
	void switchPlayer();
public: 
	void buildList();
	void printTree();
	void printNodes();
	void traverse();
	void save();
	Controller(std::fstream &, std::fstream &);
	~Controller();
};

#endif
