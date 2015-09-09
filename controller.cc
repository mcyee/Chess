#include "controller.h"
#include <stack>
#include <sstream>
#include <fstream>
#include <time.h>

using namespace std;

Controller::Controller(fstream &read, fstream &write, string type): read(read), write(write), type(type) {}

void Controller::buildGame() {
	numNodes = 1;
	write << numNodes << endl;
	write << "m start \"the start node.\"" << endl;
	Tree *addme = new Tree(0, 'm', "start", "the start node");
	nodeList.push_back(addme);
	root = nodeList[0];
	string move;
	Tree *current = root;
	cout << "Enter the moves. Press Ctrl-D when done." << endl;
	while(cin >> move) {
		addme = new Tree(numNodes, 'm', move, "");
		current->addChild(addme);
		nodeList.push_back(addme);
		numNodes++;
		current = addme;
	}
	save();
}

void Controller::buildList() {
	string nodeName;
	char nodeType;
	string nodeDescription;
	read >> numNodes;
	for(int i = 0; i < numNodes; i++) {
		read >> nodeType >> nodeName;	
		nodeDescription = inputDescription(true);
		Tree *addme = new Tree(i, nodeType, nodeName, nodeDescription);
		nodeList.push_back(addme);
	}
	
	root = nodeList[0]; // Go with the convention that the first node listed is the root.
	// For the productions, we'll just use the id's instead of the moves. That way 
	// Everything is unique.  
	stack<Tree *> myStack;
	string production;
	int token;
	int theRoot;
	myStack.push(root);
//	getline(read, production);
//	cout << production << endl;
	while(getline(read, production)) {
//		cout << production << endl;
		stringstream ss(production);
		vector<Tree *> myVec;
		ss >> theRoot;
		while(ss >> token) {
			myVec.push_back(nodeList[token]);
		}
		Tree *currentRoot = myStack.top();
		while(currentRoot->getId() != theRoot) {  // In case a node is a leaf. 
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
	cout << "PRINTING NODES" << endl;
	cout << root << endl;
	cout << root->getName() << " is the root." << endl;
	vector<Tree *>::iterator i;
	for(i = nodeList.begin(); i != nodeList.end(); i++) {
		cout <<  (*i)->getId() << " " << (*i)->getName() << endl;
	}
}

void Controller::printTree() {
	root->printTree();
}

string Controller::inputDescription(bool fromFile) {
	string desc;
	string input;
	if(fromFile) {
		getline(read, input);
	} else {
		getline(cin, input);
	}
	int i = 0;
	while(input[i] != '"') {
		i++;
	}
	i++;
	int start = i;
	int j = 0;
	while(input[i] != '"') {
		i++;
		j++;
	}
	desc = input.substr(start, j);
	return desc;
}

void Controller::switchPlayer(void) {
	if(player == "black") {
		player = "white";
	} else {
		player = "black";
	}
}

void Controller::showMessage() {
	if(type == "gamebook") {
		cout << "You should have recorded the game by now." << endl;
		cout << "You are at the start of the game you just recorded." << endl;
	} else if(type == "opening") {
		cout << "This is the chess opening book tool." << endl;
		cout << "Type in \"h\" to see command options." << endl;
	}
}

void Controller::traverse() {
	player = "black";
	bool saved = true;
	showMessage();
	stack<Tree *> position;
	position.push(root);
	char action = '0';
	Tree *current = position.top();
	string next;
	Tree *nextStep;
	char ans = 'n';
	string newDescription;
	vector<Tree *>::iterator i;
	Tree *addme;
	do {
		current = position.top();
		cout << "~> ";
		cin >> action;
		switch(action) {
			case 'j':
				switchPlayer();
				cin >> next;
				if(current->isChild(next) == NULL) {
					addme = new Tree(numNodes, 'o', next, "");
					current->addChild(addme);
					nodeList.push_back(addme);
					numNodes++;
					saved = false;
					nextStep = addme;
				} else {
					nextStep = current->isChild(next);
				}
				position.push(nextStep);
				cout << player << " plays " << nextStep->getName() << endl;
				break;
			case 'b':
				if(current == root) {
					cout << "Already at root node." << endl;
				} else {
					switchPlayer();
					position.pop();
					current = position.top();
					if (current != root) {
						cout << player << " plays " << current->getName() << endl;
					} else {
						cout << "At beginning of game." << endl;
					}
				}	
				break;
			case 'd':
				cout << current->getDescription() << endl;
				break;
			case 'a':
				newDescription = inputDescription(false);
				newDescription = current->getDescription() + newDescription;
				current->setDescription(newDescription);
				break;
			case 'r':
				newDescription = inputDescription(false);
				cin >> newDescription;
				current->setDescription(newDescription);
				break;
			case 'c':
				for(i = current->children.begin(); i != current->children.end(); i++) {
					cout << (*i)->getName() << " ";
				}
				cout << endl;
				break;
			case 's':
				cout << "This option cannot be undone. Are you sure you want to save? (y/n): ";
				cin >> ans;
				if(ans == 'y') {
					cout << "Saved changes." << endl;
					//printNodes();
					save();
				}
				saved = true;
				break;
			case 'q':
				if (!saved) {
					cout << "There are unsaved changes. Are you sure you want to quit without saving? (y/n): ";
					cin >> ans;
					if(ans == 'y') {
						return;
					} else {
				   		// Do nothing;
					}	   
				} else {
					return;
				}
				break;
			case 'h':
				cout << "a = append a description on the current node." << endl;
				cout << "r = replace a description on the current node." << endl;
				cout << "j = jump to a node that is a child." << endl;
				cout << "d = view the description on the current node" << endl;
				cout << "b = go back to the parent node." << endl;
				cout << "c = display the \"names\" of all children." << endl;
				cout << "s = save the current changes." << endl;
				break;
			default:
				cout << "Command not recognized. Type 'h' to see a list of possible commands." << endl;
				break;
			
		} 
	} while (true);
}


void Controller::save() {
	write << numNodes << endl;
	vector<Tree * >::iterator ii;
	for(ii = nodeList.begin(); ii != nodeList.end(); ii++) {
		//cout << ii->second->getName() << endl;
		//cout << ii->second->getDescription() << endl;
		write << (*ii)->getName() << " \"" << (*ii)->getDescription() << "\"" << endl;
	}
	stack<Tree *> myStack;
	myStack.push(root);
	Tree *current;
	vector<Tree *>::iterator i;
	vector<Tree *>::reverse_iterator j;
	//write << root->getId() << endl; 		Since we assume the root to be the first node listed. 
	while(!myStack.empty()) {
		current = myStack.top();
		myStack.pop();
		if(current->children.size() > 0) {
			write << current->getId() << " ";
			for(i = current->children.begin(); i != current->children.end(); i++) {
				write << (*i)->getId() << " ";
			}
			write << endl;
			for(j = current->children.rbegin(); j != current->children.rend(); j++) {
				myStack.push(*j);
			}
		} else {
			// Do nothing, since it's a terminal. 
		}		
	}
	write.close();
}

Controller::~Controller() {
	delete root;
}
