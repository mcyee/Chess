#include "controller.h"
#include <stack>
#include <sstream>
#include <fstream>

using namespace std;

Controller::Controller(fstream &read, fstream &write): read(read), write(write) {}

void Controller::buildList() {
	string nodeName;
	string nodeDescription;
	read >> numNodes;
	for(int i = 0; i < numNodes; i++) {
		read >> nodeName;
		nodeDescription = inputDescription();
		Tree *addme = new Tree(nodeName, nodeDescription);
		nodeList[nodeName] = addme;
	}

	string myRoot;
	read >> myRoot;
	root = nodeList[myRoot];
	stack<Tree *> myStack;
	string production;
	string token;
	string theRoot;
	myStack.push(root);
	getline(read, production);
	while(getline(read, production)) {
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

string Controller::inputDescription() {
	string desc;
	string input;
	getline(read, input);
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

string Controller::inputDescription2() {
	string desc;
	string input;
	getline(cin, input);
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

void Controller::traverse() {
	player = "black";
	bool saved = true;
	cout << "This is the chess opening book tool." << endl;
	cout << "Type in \"h\" to see command options." << endl;
	stack<Tree *> position;
	position.push(root);
	char action = '0';
	Tree *current = position.top();
	string next;
	Tree *nextStep;
	char ans = 'n';
	string newDescription;
	vector<Tree *>::iterator i;
	do {
		current = position.top();
		cout << "~> ";
		cin >> action;
		switch(action) {
			case 'j':
				switchPlayer();
				cin >> next;
				nextStep = current->step(next);
				if(nodeList[next] == NULL) {
					nodeList[next] = nextStep;
					numNodes++;
					saved = false;
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
				newDescription = inputDescription2();
				newDescription = current->getDescription() + newDescription;
				current->setDescription(newDescription);
				break;
			case 'r':
				newDescription = inputDescription2();
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
				cout << "This option cannot be undone. Are you sure you want to save?" << endl;
				cin >> ans;
				if(ans == 'y') {
					cout << "Saved changes." << endl;
					save();
				}
				saved = true;
				break;
			case 'q':
				if (!saved) {
					cout << "There are unsaved changes. Are you sure you want to quit without saving? (y/n)" << endl;
					cout << "~> ";
					cin >> ans;
					if(ans == 'y') {
						return;
					} else {
				   		// Do nothing;
					}	   
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
	} while (action != 'q');
}

void Controller::save() {
	write << numNodes << endl;
	map<string , Tree *>::iterator ii;
	for(ii = nodeList.begin(); ii != nodeList.end(); ii++) {
		write << ii->second->getName() << " \"" << ii->second->getDescription() << "\"" << endl;
	}
	stack<Tree *> myStack;
	myStack.push(root);
	Tree *current;
	vector<Tree *>::iterator i;
	vector<Tree *>::reverse_iterator j;
	write << root->getName() << endl;
	while(!myStack.empty()) {
		current = myStack.top();
		myStack.pop();
		if(current->children.size() > 0) {
			write << current->getName() << " ";
			for(i = current->children.begin(); i != current->children.end(); i++) {
				write << (*i)->getName() << " ";
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
