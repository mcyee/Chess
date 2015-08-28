#include "tree.h"
using namespace std;

Tree::Tree(int id, string move, string description): 
	id(id), move(move), description(description) {}
	
void Tree::addChild(Tree *t) {
	children.push_back(t);
}

int Tree::getId(void) {
	return id;
}

Tree *Tree::isChild(std::string s) {
	vector<Tree *>::iterator i;
	for(i = children.begin(); i != children.end(); i++) {
		if((*i)->getName() == s) {
			return (*i);
		} 
	}
	return NULL;
}

string Tree::getName(void) {
	return move;
}

string Tree::getDescription(void) {
	return description;
}

void Tree::setDescription(string s) {
	description = s;
}

Tree::~Tree() {
	vector<Tree *>::iterator i;
	for(i = children.begin(); i != children.end(); i++) {
		delete (*i);
	}
}

void Tree::printTree(void) {
	cout << id << endl;
	vector<Tree *>::iterator i;
	for(i = children.begin(); i != children.end(); i++) {
		(*i)->printTree();
	}
}
