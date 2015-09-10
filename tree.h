#ifndef __TREE_H__
#define __TREE_H__

#include <vector>
#include <string>
#include <iostream>

struct Tree {
	int id;
	char type; // Can be either "main" or "opening". Opening will be used for 
				// opening book and derivatives in games, while main will be 
				// used for recording what was actually played in game. 
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
