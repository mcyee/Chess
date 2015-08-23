#include "controller.h"
#include "tree.h"
using namespace std;

int main(int argc, char *argv[]) {
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


	Controller k;
	fstream f;
	f.open(file.c_str());
	k.buildList(f);
	k.traverse(ofile);
	return 0;
}
