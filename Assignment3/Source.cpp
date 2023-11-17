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
		cout << "5.Delete File" << endl;
		cout << "6.Delete Directory" << endl;
		cout << "7.Rename File" << endl;
		cout << "8.Rename Directory" << endl;
		cout << "9.Search by name" << endl;
		cout << "10.Copy File" << endl;
		cout << "11.Copy Folder" << endl;
		cout << "10.Merge Directory" << endl;
		int select;
		cin >> select;

		switch (select)
		{

		case 1:
		{
			system("cls");
			tree.levelorder_print();
			cout << endl << endl << "Press any button to continue...";

			temp = _getch();
			continue;
		}

		case 2:
		{
			system("cls");
			tree.add_file();
			
			continue;
		}

		case 3:
		{
			system("cls");
			tree.add_dir();
			continue;
		}

		case 4:
		{
			continue;
		}

		case 5:
		{
			continue;
		}

		case 6:
		{
			continue;
		}

		case 9:
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