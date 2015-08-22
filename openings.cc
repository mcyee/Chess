#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <sstream>
#include <map>
#include <fstream>
using namespace std;

// Problem: If someone enters a node that doesn't exist on that level, but exists somewhere
// else in the tree, then the program doesn't stop the user from accidentally adding that 
// node. This is bad. We can perhaps add a second parameter to the "step" function so that 
// it knows whether it should be adding a node or not. This means we would need to access
// the map first to know if we should be adding a node or not. So, in the case that we 
// should not be adding a node and the node doesn't yet exist, we'll know there is a problem. 
// Of course, this would never be a problem in the actual chess program since the function 
// that creates unique id's will take care of it and it would be literally impossible to 
// add a move that has already been added before because the node id will be generated. 
// Done. 

struct Tree {
	string name;
	vector<Tree *> children;
public:
	Tree(string name);
	void addChild(Tree *);
	string getName(void);
	Tree *step(string);
	~Tree();
	void printTree();
};

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

struct Controller {
	int numNodes;
	Tree *root;
	map<string, Tree *> nodeList;
public: 
	void buildList(fstream &);
//	void buildTree();
	void printTree();
	void printNodes();
	void traverse();
	void save(string);
	~Controller();
};

void Controller::buildList(fstream &f) {
	string nodeName;
	f >> numNodes;
	for(int i = 0; i < numNodes; i++) {
		f >> nodeName;
		Tree *addme = new Tree(nodeName);
		nodeList[nodeName] = addme;
	}
	string myRoot;
	f >> myRoot;
	root = nodeList[myRoot];
	// Now we build the tree.
	stack<Tree *> myStack;
	string production;
	string token;
	string theRoot;
	myStack.push(root);
	getline(f, production);
	while(getline(f, production)) {
		stringstream ss(production);
		vector<Tree *> myVec;
		ss >> theRoot;
		while(ss >> token) {
			myVec.push_back(nodeList[token]);
		}
		Tree *currentRoot = myStack.top();
		while(currentRoot->getName() != theRoot) {
			myStack.pop();
			currentRoot = myStack.top();
		}
		myStack.pop();
		vector<Tree *>::reverse_iterator i;
		for(i = myVec.rbegin(); i != myVec.rend(); i++) {
			myStack.push(*i);
		}
		vector<Tree *>::iterator j;
		for(j = myVec.begin(); j != myVec.end(); j++) {
			currentRoot->addChild(*j);
		}
	}
}

void Controller::printNodes() {
	cout << root->getName() << " is the root." << endl;
	map<string, Tree *>::iterator i;
	for(i = nodeList.begin(); i != nodeList.end(); i++) {
		cout << (*i).first << " " << (*i).second << endl;
	}
}

void Controller::printTree() {
	root->printTree();
}

void Controller::traverse() {
	stack<Tree *> position;
	position.push(root);
	char action = '0';
	while(action != 'q') {
		cin >> action;
		if(action == 'j') {
			string next;
			cin >> next;
			Tree *current = position.top();
			Tree *nextStep = current->step(next);
			if(nodeList[next] == NULL) {
				nodeList[next] = nextStep;
				numNodes++;
			}
			position.push(nextStep);
		} else if(action == 'b') {
			position.pop();
			Tree *current = position.top();
			cout << "now at node: " << current->getName() << endl;
		} 
	}
}

void Controller::save(string file) {
	ofstream k;
	k.open(file.c_str());
	k << numNodes << endl;
	map<string , Tree *>::iterator ii;
	for(ii = nodeList.begin(); ii != nodeList.end(); ii++) {
		k << ii->first << endl;
	}
	stack<Tree *> myStack;
	myStack.push(root);
	Tree *current;
	vector<Tree *>::iterator i;
	vector<Tree *>::reverse_iterator j;
	k << root->getName() << endl;
	while(!myStack.empty()) {
		current = myStack.top();
		myStack.pop();
		if(current->children.size() > 0) {
			k << current->getName() << " ";
			for(i = current->children.begin(); i != current->children.end(); i++) {
				k << (*i)->getName() << " ";
			}
			k << endl;
			for(j = current->children.rbegin(); j != current->children.rend(); j++) {
				myStack.push(*j);
			}
		} else {
			// Do nothing, since it's a terminal. 
		}		
	}
	k.close();
}

Controller::~Controller() {
	delete root;
}

int main(int argc, char *argv[]) {
	if (argc > 4) {
		cout << "Huh!?" << endl;
	}
	Controller k;
	fstream f;
	string file = argv[1];
	f.open(file.c_str());
	k.buildList(f);
	//k.printNodes();
//	k.buildTree();
	k.printTree();
	k.traverse();
	string ofile = argv[2];
	k.save(ofile);
	return 0;
}
