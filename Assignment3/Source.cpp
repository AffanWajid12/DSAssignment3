//Muhammad_Affan_Wajid_22i-2567
#include<iostream>
#include "FileTree.h"
using namespace std;

int main()
{
	FileTree tree;
	tree.levelorder_print();
	cout << endl;
	tree.print_path();
}