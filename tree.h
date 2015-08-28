#ifndef __TREE_H__
#define __TREE_H__

#include <vector>
#include <string>
#include <iostream>

struct Tree {
	int id;
	std::string move;
	std::string description;
	std::vector<Tree *> children;
public:
	Tree(int id, std::string move, std::string description="");
	Tree *isChild(std::string);
	void addChild(Tree *);
	std::string getName(void);
	int getId(void);
	std::string getDescription(void);
	void setDescription(std::string);
	Tree *step(std::string);
	~Tree();
	void printTree();
};

#endif
