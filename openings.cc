#include "controller.h"
#include "tree.h"
using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "Improper number of arguments." << endl;
	}
	Controller k;
	fstream f;
	string file = argv[1];
	f.open(file.c_str());
	k.buildList(f);
	//k.printNodes();
//	k.buildTree();
//	k.printTree();
	
	string ofile = argv[2];
	k.traverse(ofile);
	return 0;
}
