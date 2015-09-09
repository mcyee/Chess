#include "controller.h"
#include "tree.h"
#include "interpreter.h"
using namespace std;

int main(
		//int argc, char *argv[]
		) {
	/*
	string ofile;
	string file;
	if (argc == 1) {
		cout << "Improper number of arguments. At least one file must be specified." << endl;
		return 0;
	}
	if (argc == 2) {
		cout << "Defaulting source file to save file." << endl;
		file = argv[1];
		ofile = argv[1];
	} 
	if(argc == 3) {
		file = argv[1];
		ofile = argv[2];
	}
	if(argc > 3) {
		cout << "Improper number of arguments! Exiting." << endl;
		return 0;
	}
	

	fstream f;
	fstream g;
	f.open(file.c_str());
	g.open(ofile.c_str());
	Controller k(f, g);
	k.buildList();
	k.traverse();
	return 0;
	*/

	Interpreter i;
	i.initiate();
	return 0;
}
