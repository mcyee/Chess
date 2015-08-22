#include "tree.h"
using namespace std;

Tree::Tree(string name): name(name) {}

Tree *Tree::step(string next) {
	vector<Tree *>::iterator i;
	for(i = children.begin(); i != children.end(); i++) {
		if ((*i)->getName() == next) {
			cout << "moving to: " << next << endl;
			return *i;
		}
	}
	cout << "adding child: " << next << " to: " << name << endl;
	Tree *addMe = new Tree(next);
	children.push_back(addMe);
	return addMe;
}
	

void Tree::addChild(Tree *t) {
	children.push_back(t);
}

string Tree::getName(void) {
	return name;
}

Tree::~Tree() {
	vector<Tree *>::iterator i;
	for(i = children.begin(); i != children.end(); i++) {
		delete (*i);
	}
}

void Tree::printTree(void) {
	cout << name << endl;
	vector<Tree *>::iterator i;
	for(i = children.begin(); i != children.end(); i++) {
		(*i)->printTree();
	}
}
