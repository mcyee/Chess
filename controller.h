#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "tree.h"
#include <map>
#include <fstream>
#include <string>

class Controller {
	std::fstream &read;
	std::fstream &write;
	std::string type;
	int numNodes;
	std::string player;
	Tree *root;
	std::vector<Tree * > nodeList;
	std::string inputDescription(bool);
	void switchPlayer();
public: 
	void buildList();
	void printTree();
	void printNodes();
	void traverse();
	void showMessage(); 
	void save();
	Controller(std::fstream &, std::fstream &, std::string);
	~Controller();
};

#endif
