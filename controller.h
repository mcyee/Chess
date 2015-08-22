#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "tree.h"
#include <map>
#include <fstream>
#include <string>

class Controller {
	int numNodes;
	Tree *root;
	std::map<std::string, Tree *> nodeList;
public: 
	void buildList(std::fstream &);
//	void buildTree();
	void printTree();
	void printNodes();
	void traverse();
	void save(std::string);
	~Controller();
};

#endif
