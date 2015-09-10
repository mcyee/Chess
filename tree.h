#ifndef __TREE_H__
#define __TREE_H__

#include <vector>
#include <string>
#include <iostream>

struct Tree {
	int id;
	char type; // Can be either "derivative", "main" or "opening". Opening will be used for 
				// just the opening book while "main" and "derivative" will be used in files
				// for game analysis. 
	std::string move;
	std::string description;
	std::vector<Tree *> children;
public:
	Tree(int id, char type, std::string move, std::string description) ;
	Tree *isChild(std::string);
	void addChild(Tree *);
	std::string getName(void);
	int getId(void);
	char getType(void);
	std::string getDescription(void);
	void setDescription(std::string);
	~Tree();
	void printTree();
};

#endif
