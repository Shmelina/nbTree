#include "TREE.h"
#include <iostream>

using namespace std;

int main()
{
	tree<double> tree(7);
	tree += 1;
	tree[0].add_child(2);
	tree[0].add_child(1);
	tree[0].add_child(3);
	tree += 777;
	if (tree[0] == 776)
		cout << "true" << endl;
	cout << tree;
	cout << endl;
	return 0;
}