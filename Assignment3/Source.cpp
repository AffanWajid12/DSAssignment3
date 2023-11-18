//Muhammad_Affan_Wajid_22i-2567
#include<iostream>
#include<conio.h>
#include<Windows.h>
#include "FileTree.h"
using namespace std;

int main()
{
	FileTree tree;
	char temp;
	while (1)
	{
		system("cls");
		cout << "Welcome to the File Managment System!" << endl;
		cout << "Select from the following options: " << endl;
		cout << "1.List the file directory tree" << endl;
		cout << "2.Add new file" << endl;
		cout << "3.Add new directory" << endl;
		cout << "4.Delete File" << endl;
		cout << "5.Delete Directory" << endl;
		cout << "6.Rename File" << endl;
		cout << "7.Rename Directory" << endl;
		cout << "8.Search by name" << endl;
		cout << "9.Copy File" << endl;
		cout << "10.Copy Folder" << endl;
		cout << "11.Merge Directory" << endl;
		int select;
		cin >> select;

		switch (select)
		{

		case 1://Print level order of the file tree
		{
			system("cls");
			tree.levelorder_print();
			cout << endl << endl << "Press any button to continue...";

			temp = _getch();
			continue;
		}

		case 2://Add a file to path by specifying name
		{
			system("cls");
			tree.add_file();
			
			continue;
		}

		case 3://Add a directory to path by specifying name
		{
			system("cls");
			tree.add_dir();
			continue;
		}

		case 4://Del a specific file by giving the path of that file
		{
			system("cls");
			tree.del_file();
			continue;
		}

		case 5://Del a specific directory by giving the path of that directory
		{
			system("cls");
			tree.del_dir();
			continue;
		}

		case 6:
		{
			continue;
		}

		case 8:
		{
			system("cls");
			cout << "Enter the name of the file or folder you want to search: ";
			string name;
			cin >> name;
			tree.search(name);
			temp = _getch();
			continue;
		}

		}
	}
}