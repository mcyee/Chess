#include "controller.h"
#include <stack>
#include <sstream>
#include <fstream>

using namespace std;

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
