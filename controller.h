#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "tree.h"
#include <map>
#include <fstream>
#include <string>

class Controller {
	int numNodes;
	std::string player;
	Tree *root;
	std::map<std::string, Tree *> nodeList;
	std::string inputDescription();
	std::string inputDescription(std::fstream &);
	void switchPlayer(void);
public: 
	void buildList(std::fstream &);
	void printTree();
	void printNodes();
	void traverse(std::string);
	void save(std::string);
	~Controller();
};

#endif
