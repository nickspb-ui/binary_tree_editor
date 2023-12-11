#include "Tree.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	Tree* tree = nullptr;
	int iter = 0, x = 0;
	for (int i = 1; i <= 10; i++) {
		add(&tree, i);
	}
	del(tree, 1, tree);
	del(tree, 2, tree);
	del(tree, 3, tree);
	add(&tree, 1);
	print_tree(tree, &x, 0);
	cout << endl << endl << endl;
	print_nodes(tree);
}