#ifndef __TREE_H__
#define __TREE_H__

#include <vector>
#include <string>
#include <iostream>
struct Tree {
	std::string name;
	std::vector<Tree *> children;
public:
	Tree(std::string name);
	void addChild(Tree *);
	std::string getName(void);
	Tree *step(std::string);
	~Tree();
	void printTree();
};

#endif
