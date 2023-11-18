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
		cout << "Select from the following options: " << endl<<endl;
		cout << "---------------------------------------------------------------------------------------------------------|" << endl;
		cout << "1.List the file directory tree                                                                            " << endl<<endl;
		cout << "2.Add new file                                                                                           |" << endl<<endl;
		cout << "3.Add new directory                                                                                      |" << endl<<endl;
		cout << "4.Delete File                                                                                            |" << endl<<endl;
		cout << "5.Delete Directory                                                                                       |" << endl<<endl;
		cout << "6.Rename File or Directory                                                                               |" << endl<<endl;
		cout << "7.Search by name                                                                                         |" << endl<<endl;
		cout << "8.Copy File                                                                                              |" << endl<<endl;
		cout << "9.Move File                                                                                              |" << endl<<endl;
		cout << "10.Merge Directory                                                                                        " << endl;
		cout << "---------------------------------------------------------------------------------------------------------|" << endl<<endl;
		cout << "Input: ";
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

		case 6://Rename any directory or file by searching name and renaming it
		{
			system("cls");
			tree.rename_any();
			temp = _getch();
			continue;
		}

		case 7://Search any file or directory by name
		{
			system("cls");
			cout << "Enter the name of the file or folder you want to search: ";
			string name;
			cin >> name;
			tree.search(name);
			temp = _getch();
			continue;
		}

		case 8://Used to copy a file from one folder to another
		{
			system("cls");
			tree.copy_file();
			continue;
		}
		case 9:
		{
			system("cls");
			tree.move_file();
			continue;
		}

		}
	}
}