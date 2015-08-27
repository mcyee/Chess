#ifndef __TREE_H__
#define __TREE_H__

#include <vector>
#include <string>
#include <iostream>

struct Tree {
	std::string id;
	std::string description;
	std::vector<Tree *> children;
public:
	Tree(std::string id, std::string description="");
	bool isChild(Tree *);
	void addChild(Tree *);
	std::string getName(void);
	std::string getDescription(void);
	void setDescription(std::string);
	Tree *step(std::string);
	~Tree();
	void printTree();
};

#endif
