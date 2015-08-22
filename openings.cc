#include "controller.h"
#include "tree.h"
using namespace std;

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
//	k.printTree();
	k.traverse();
	string ofile = argv[2];
	k.save(ofile);
	return 0;
}
