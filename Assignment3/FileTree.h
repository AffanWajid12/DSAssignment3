//Muhammad_Affan_Wajid_22i-2567
#pragma once
#include<iostream>
#include<string>
using namespace std;


class Node
{
public:
	string name;
	string path;
	bool type;//False means dir and true means file
	Node* left;
	Node* right;
	
	Node()
	{
		name = "";
		path = "";
		type = false;
		left = NULL;
		right = NULL;

	}
	Node(Node* to_copy)
	{
		this->name = to_copy->name;
		this->type = to_copy->type;
		this->left = NULL;
		this->right = NULL;
	}
	Node(string name, bool type, Node* root)
	{
		this->name = name;
		//set_path_auto(root);
		path = set_path(name, root,"");
		this->type = type;
		left = NULL;
		right = NULL;
	}
	Node(string name)
	{
		this->name = name;
		path = "";
		type = false;
		left = NULL;
		right = NULL;
	}
	Node(string name, bool type)
	{
		this->name = name;
		path = "";
		this->type = type;
		left = NULL;
		right = NULL;
	}
	bool contains_sym(string str)
	{
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == '|')
			{
				return true;
			}
		}
		return false;
	}

	string set_path(string name, Node* root,string path)
	{
		string left = "";
		string right = "";
		if (root == NULL)//If the path is not found send an empty string
		{
			return "";
		}
		if (name == root->name)//If the path is found then return the name of file
		{
			return name;

		}

		left = set_path(name, root->left,"");
		right = set_path(name, root->right,"");

		if (left != "")//Sees if file is found if so then add it the left string
		{
			if (root->name != "\\")
			{
			left = root->name + "\\" + left;
			}
			else
			{
				left = root->name  + left;
			}
		}
		else if(right!="")//Sees if file is found if so then add it the right string
		{
			if (root->name != "\\")
			{
				right = root->name + "\\" + right;
			}
			else
			{
				right = root->name + right;
			}
		}
		return left + right;//One of them will be empty since we dont consider duplicate names 
	}

	void set_path_auto(Node* root)
	{
		
		this->path = set_path(name, root,"");
	}

};

//Simple Queue Implimentation for level order traversal 
class Node_Q
{
public:
	Node* data;
	Node_Q* next;
	Node_Q(Node* data)
	{
		this->data = data;
		next = NULL;
	}

};
class Queue
{
private:
	Node_Q* front;
	Node_Q* rear;

public:
	Queue()
	{
		front = NULL;
		rear = NULL;
	}
	bool isEmpty()
	{
		if (front == NULL || rear == NULL)
		{
			return true;
		}
		return false;
	}
	void enqueue(Node* add)
	{
		if (isEmpty())//Check if this is the first data being added
		{
			Node_Q* temp = new Node_Q(add);
			front = temp;

			rear = temp;

		}
		else
		{

			Node_Q* temp = new Node_Q(add);
			rear->next = new Node_Q(add);
			rear = rear->next;


		}
		/*else if (front != NULL) //the next node is NULL
		{
			if (!(front->next))
			{
				rear->next = new Node_Q(add);
				rear = rear->next;
				front->next = rear;
			}
		}
		else
		{

			rear->next = new Node_Q(add);
			rear = rear->next;

		}*/
	}
	Node* get_front()
	{
		if (!(isEmpty()) && front != NULL)
			return front->data;

		return NULL;
	}
	void dequeue()
	{
		if (isEmpty())
		{
			cout << "Queue is empty(Dequeue op)! ";

		}
		/*
		else if( front != NULL)
		{
			if (front->next|| rear)
			{
				front = front->next;
			}
			else
			{
				front = NULL;
			}

		}*/
		else
		{

			front = front->next;

		}

	}

};

//Actual FileTree Implementation
class FileTree
{
private:
	Node* root;

public:
	FileTree()//By default the file tree strcuture will have the root, the Patirents Directory on the left and  the Logs on the right 
	{
		root = new Node("\\", false, root);

		root->left = new Node("Patients");
		root->left->set_path_auto(root);

		root->right = new Node("Logs");
		root->right->set_path_auto(root);
	}

	//Prints the tree in an level order fashion
	void levelorder_print()
	{
		Queue q;
		q.enqueue(root);
		q.enqueue(NULL);
		while (!(q.isEmpty()))
		{
			Node* temp = q.get_front();
			q.dequeue();
			if (temp == NULL)
			{
				cout << endl;
				if (!(q.isEmpty()))
				{
					q.enqueue(NULL);
				}
			}
			else
			{
				cout << temp->name << " ";
				if (temp->left)
				{
					q.enqueue(temp->left);
				}
				if (temp->right)
				{
					q.enqueue(temp->right);
				}
			}
		}
	}
	void print_path()
	{
		cout << root->left->path;
	}//Debugging purposes

	//	Adding/Deleting Files and Directories in the FileTree
	void add_file()
	{
		int a = 1;
		while (1)
		{
			cout << "Do you want to insert the new file in Patients Directory or Logs Directory?" << endl;
			cout << "1.Patients" << endl;
			cout << "2.Logs" << endl << endl;;

			int select;
			cin >> select;
			Node* temp = NULL;
			switch (select)
			{
			case 1:
			{
				temp = root->left;//Select patients
				while (1)
				{
					cout << "Path: " << temp->path << endl;
					if (temp->right == NULL)
					{
						cout << "This dir has space for new file! Do you want to add the new file here? " << endl;
						cout << "1.Yes		2.Goto Sub-Directory of Current Directory			3.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							cout << "Give a name to new file with extension: ";
							string n;
							cin >> n;
							temp->right = new Node(n, true);
							temp->right->set_path_auto(root);
							return;
						}
						else if (select2 == 2)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
					else
					{
						cout << "This dir has a file already. Do you want to go into the sub-dir or cancel this action? " << endl;
						cout << "1.Goto sub-dir			2.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
				}
				return;
			}

			case 2:
			{
				temp = root->right;//Select Logs
				while (1)
				{
					cout << "Path: " << temp->path << endl;
					if (temp->right == NULL)
					{
						cout << "This dir has space for new file! Do you want to add the new file here? " << endl;
						cout << "1.Yes		2.Goto Sub-Directory of Current Directory			3.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							cout << "Give a name to new file with extension: ";
							string n;
							cin >> n;
							temp->right = new Node(n);
							temp->right->set_path_auto(root);
							return;
						}
						else if (select2 == 2)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
					else
					{
						cout << "This dir has a file already. Do you want to go into the sub-dir or cancel this action? " << endl;
						cout << "1.Goto sub-dir			2.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
				}
				return;
			}
			default:
				cout << "Wrong option! ";

				continue;
			}
		}


	}
	void add_dir()
	{
		/*User first selects where they want to put the directory.After that the user traverses throught the tree manually and once he
		reaches the desired location they can add a new directory there if there is space for it.If not user is told they cannot add
		The new directory in that location and function is terminated.*/
		int a = 1;
		while (1)
		{
			cout << "Do you want to insert the new directory in Patients Directory or Logs Directory?" << endl;
			cout << "1.Patients" << endl;
			cout << "2.Logs" << endl << endl;;

			int select;
			cin >> select;
			Node* temp = NULL;
			switch (select)
			{
			case 1:
			{
				temp = root->left;
				while (1)
				{
					cout << "Path: " << temp->path << endl;
					if (temp->left == NULL)
					{
						cout << "This dir has space for new dir! Do you want to add the new directory here? " << endl;
						cout << "1.Yes			2.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							cout << "Give a name to new directory: ";
							string n;
							cin >> n;
							temp->left = new Node(n);
							temp->left->set_path_auto(root);
							return;
						}
						else
						{
							return;
						}
					}
					else
					{
						cout << "This dir has a sub-dir already. Do you want to go into the sub-dir or cancel this action? " << endl;
						cout << "1.Goto sub-dir			2.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							temp = temp->left;
							continue;
						}
						else
						{
							return;
						}
					}
				}




				return;
			}

			case 2:
			{
				temp = root->right;//Goto Logs Folder
				while (1)
				{
					cout << "Path: " << temp->path << endl;
					if (temp->left == NULL)
					{
						cout << "This dir has space for new dir! Do you want to add the new directory here? " << endl;
						cout << "1.Yes			2.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							cout << "Give a name to new directory: ";
							string n;
							cin >> n;
							temp->left = new Node(n);
							temp->left->set_path_auto(root);
							return;
						}
						else
						{
							return;
						}
					}
					else
					{
						cout << "This dir has a sub-dir already. Do you want to go into the sub-dir or cancel this action? " << endl;
						cout << "1.Goto sub-dir			2.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							temp = temp->left;
							continue;
						}
						else
						{
							return;
						}
					}
				}


				return;
			}
			default:
				cout << "Wrong option! ";

				continue;
			}
		}

	}
	void del_file()
	{
		int a = 1;
		while (1)
		{
			cout << "Do you want to delete a file in Patients Directory or Logs Directory?" << endl;
			cout << "1.Patients" << endl;
			cout << "2.Logs" << endl << endl;;

			int select;
			cin >> select;
			Node* temp = NULL;
			switch (select)
			{
			case 1:
			{
				temp = root->left;//Select patients
				while (1)
				{
					cout << "Path: " << temp->path << endl;
					if (temp->right == NULL)
					{
						cout << "This Dir has no file to delete. Do you want to goto a sub-dir or cancel and return to menu? " << endl;
						cout <<"1.Goto Sub - Directory of Current Directory			2.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)//Goto sub-dir
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else//Cancel and return to menu
						{
							return;
						}
					}
					else
					{
						cout << "This dir has a file named "<<temp->right->name<<" Do you want to go into the sub - dir ,delete this file or cacncel this action ? " << endl;
						cout << "1.Goto sub-dir			2.Delete file		3.Cancel deletion" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)//Goto sub dir
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else if (select2 == 2)//Delete File
						{
							delete temp->right;
							temp->right = NULL;
							char c = _getch();
							return;
						}
						else//Cancel operation
						{
							return;
						}
					}
				}
				return;
			}

			case 2:
			{

				temp = root->right;//Select Logs
				while (1)
				{
					cout << "Path: " << temp->path << endl;
					if (temp->right == NULL)
					{
						cout << "This Dir has no file to delete. Do you want to goto a sub-dir or cancel and return to menu? " << endl;
						cout << "1.Goto Sub - Directory of Current Directory			2.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
					else
					{
						cout << "This dir has a file named " << temp->right->name << " Do you want to go into the sub - dir ,delete this file or cacncel this action ? " << endl;
						cout << "1.Goto sub-dir			2.Delete file		3.Cancel deletion" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else if (select2 == 2)
						{
							delete temp->right;
							temp->right = NULL;
							char c = _getch();
							return;
						}
						else
						{
							return;
						}
					}
				}
				return;
			
			}
			default:
				cout << "Wrong option! ";

				continue;
			}
		}

	}
	void del_dir()
	{
		int a = 1;
		while (1)
		{
			cout << "Do you want to delete a directory in Patients Directory or Logs Directory?" << endl;
			cout << "1.Patients" << endl;
			cout << "2.Logs" << endl << endl;;

			int select;
			cin >> select;
			Node* temp = NULL;
			switch (select)
			{
			case 1:
			{
				temp = root->left;//Select patients
				while (1)
				{
					cout << "Path: " << temp->path << endl;
					if (temp->left == NULL)//If directory has a sub-directory
					{
						cout << "This directory doesnt have a sub-directory.Hence nothing can be deleted. Press any button to go back to menu... " << endl;
						char c = _getch();
						return;
					}
					else
					{
						cout << "This dir has a sub-directory named " << temp->left->name << " Do you want to go into the sub - dir ,delete this sub-directory or cacncel this action ? " << endl;
						cout << "1.Goto sub-dir			2.Delete Directory		3.Cancel deletion" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)//Goto sub dir
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else if (select2 == 2)//Delete Directory
						{
							if (temp->left->left || temp->left->right)
							{
								cout << "This directory is not empty.\n1.Delete Directory and it's content			2.Cancel Action" << endl;
								int select3;
								cin >> select3;
								if (select3 == 1)
								{
									delete temp->left;
									temp->left = NULL;
									cout << endl << "Directory deleted!";
									char c = _getch();
									return;
								}
								else
								{
									return;
								}
							}
							else
							{
								delete temp->left;
								temp->left = NULL;
								cout << endl << "Directory deleted!";
								char c = _getch();
							}
							return;
						}
						else//Cancel operation
						{
							return;
						}
					}
				}
				return;
			}

			case 2:
			{

				temp = root->right;//Select Logs
				while (1)
				{
					cout << "Path: " << temp->path << endl;
					if (temp->left == NULL)//If directory has a sub-directory
					{
						cout << "This directory doesnt have a sub-directory.Hence nothing can be deleted. Press any button to go back to menu... " << endl;
						char c = _getch();
						return;
					}
					else
					{
						cout << "This dir has a sub-directory named " << temp->left->name << " Do you want to go into the sub - dir ,delete this sub-directory or cacncel this action ? " << endl;
						cout << "1.Goto sub-dir			2.Delete Directory		3.Cancel deletion" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)//Goto sub dir
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else if (select2 == 2)//Delete Directory
						{
							if (temp->left->left || temp->left->right)
							{
								cout << "This directory is not empty.\n1.Delete Directory and it's content			2.Cancel Action" << endl;
								int select3;
								cin >> select3;
								if (select3 == 1)
								{
									delete temp->left;
									temp->left = NULL;
									cout << endl << "Directory deleted!";
									char c = _getch();
									return;
								}
								else
								{
									return;
								}
							}
							else
							{
								delete temp->left;
								temp->left = NULL;
								cout << endl << "Directory deleted!";
								char c = _getch();
							}
							return;
						}
						else//Cancel operation
						{
							return;
						}
					}
				}
				return;

			}
			default:
				cout << "Wrong option! ";

				continue;
			}
		}

	}

	void rename_any()//File is renamed using levelorder traversal
	{
		cout << "Name the directory or file you want to rename: ";
		string s;
		cin >> s;

		Queue q;
		q.enqueue(root);
		q.enqueue(NULL);
		while (!(q.isEmpty()))
		{
			Node* temp = q.get_front();
			q.dequeue();

			if (temp == NULL)
			{
				cout << endl;
				if (!(q.isEmpty()))
				{
					q.enqueue(NULL);
				}
			}
			else
			{
				if (temp->name == s)
				{
					cout << "Found and path is: " << temp->path<<endl;
					cout << "Type the new name: ";
					string new_name;
					cin >> new_name;
					temp->name = new_name;
					temp->set_path_auto(root);
					cout << "New name set successfully! " << endl;
					return;
				}
				if (temp->left)
				{
					q.enqueue(temp->left);
				}
				if (temp->right)
				{
					q.enqueue(temp->right);
				}
			}
		}
		cout << "The file or folder by name does not exist! ";
	
		return;

	}

	void copy_file()
	{
		cout << "Copy|" << endl;
		Node* to_copy = get_file();
		if (to_copy == NULL)
		{
			return;
		}
		
		system("cls");
		cout << "Paste| " << to_copy->name<<endl;
		//This is copied from the add file func:
		int a = 1;
		while (1)
		{
			cout << "Do you want to insert the new file in Patients Directory or Logs Directory?" << endl;
			cout << "1.Patients" << endl;
			cout << "2.Logs" << endl << endl;;

			int select;
			cin >> select;
			Node* temp = NULL;
			switch (select)
			{
			case 1:
			{
				temp = root->left;//Select patients
				while (1)
				{
					cout << "Path: " << temp->path << endl;
					if (temp->right == NULL)
					{
						cout << "This dir has space for new file! Do you want to add the copy of file here? " << endl;
						cout << "1.Yes		2.Goto Sub-Directory of Current Directory			3.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							temp->right = new Node(to_copy);
							cout << "Select new name for copied file: ";
							string new_name;
							cin >> new_name;
							temp->right->name = new_name;
							temp->right->set_path_auto(root);
							return;
						}
						else if (select2 == 2)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
					else
					{
						cout << "This dir has a file already. Do you want to go into the sub-dir or cancel this action? " << endl;
						cout << "1.Goto sub-dir			2.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
				}
				return;
			}

			case 2:
			{
				temp = root->right;//Select Logs
				while (1)
				{
					cout << "Path: " << temp->path << endl;
					if (temp->right == NULL)
					{
						cout << "This dir has space for new file! Do you want to add the copy of file here? " << endl;
						cout << "1.Yes		2.Goto Sub-Directory of Current Directory			3.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							temp->right = new Node(to_copy);
							cout << "Select new name for copied file: ";
							string new_name;
							cin >> new_name;
							temp->right->name = new_name;
							temp->right->set_path_auto(root);
							return;
						}
						else if (select2 == 2)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
					else
					{
						cout << "This dir has a file already. Do you want to go into the sub-dir or cancel this action? " << endl;
						cout << "1.Goto sub-dir			2.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
				}
				return;
			}
			default:
				cout << "Wrong option! ";

				continue;
			}
		}
	}
	void move_file()
	{
		cout << "Cut|" << endl;
		Node* to_copy = get_file();
		if (to_copy == NULL)
		{
			return;
		}
		
		system("cls");
		cout << "Move| " << to_copy->name << endl;
		//This is copied from the add file func:
		int a = 1;
		while (1)
		{
			cout << "Do you want to insert the new file in Patients Directory or Logs Directory?" << endl;
			cout << "1.Patients" << endl;
			cout << "2.Logs" << endl << endl;;

			int select;
			cin >> select;
			Node* temp = NULL;
			switch (select)
			{
			case 1:
			{
				temp = root->left;//Select patients
				while (1)
				{
					cout << "Path: " << temp->path << endl;
					if (temp->right == NULL)
					{
						cout << "This dir has space for new file! Do you want to add the copy of file here? " << endl;
						cout << "1.Yes		2.Goto Sub-Directory of Current Directory			3.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							temp->right = new Node(to_copy);
							temp->right->set_path_auto(root);
							
							return;
						}
						else if (select2 == 2)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
					else
					{
						cout << "This dir has a file already. Do you want to go into the sub-dir or cancel this action? " << endl;
						cout << "1.Goto sub-dir			2.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
				}
				return;
			}

			case 2:
			{
				temp = root->right;//Select Logs
				while (1)
				{
					cout << "Path: " << temp->path << endl;
					if (temp->right == NULL)
					{
						cout << "This dir has space for new file! Do you want to add the copy of file here? " << endl;
						cout << "1.Yes		2.Goto Sub-Directory of Current Directory			3.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							temp->right = new Node(to_copy);
							
							temp->right->set_path_auto(root);
						
							
							return;
						}
						else if (select2 == 2)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
					else
					{
						cout << "This dir has a file already. Do you want to go into the sub-dir or cancel this action? " << endl;
						cout << "1.Goto sub-dir			2.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
				}
				return;
			}
			default:
				cout << "Wrong option! ";

				continue;
			}
		}
	}
	Node* get_file()
	{

		cout << "Do you want to select the file for copying in Patients Directory or Logs Directory?" << endl;
		cout << "1.Patients" << endl;
		cout << "2.Logs" << endl << endl;;

		int select;
		cin >> select;
		Node* temp = root;
		switch (select)
		{

			case 1:
			{
				temp = root->left;//Select patients
				break;
			}
			case 2:
			{
				temp = root->right;//Select Logs
				break;
			}

		}



		while (1)
		{
			cout << "Path: " << temp->path << endl;
			if (temp->right == NULL)
			{
				cout << "This dir doesnt have a file! Select from the following " << endl;
				cout << "1.Goto Sub-Directory of Current Directory			2.Cancel and return to menu" << endl;
				int select2;
				cin >> select2;
				if (select2 == 1)
				{
					if (temp->left != NULL)
					{
						temp = temp->left;
						continue;
					}
					else
					{
						cout << "It seems that this folder doesn't have a sub-directory! ";
						char c = _getch();
						return NULL;
					}
				}
				else if (select2 == 2)
				{
					return NULL;
				}
			}
			else
			{
				cout << "This dir has a file with name " << temp->right->name << " .Select from the following actions : " << endl;
				cout << "1.Goto sub-dir		2.Copy File	3 .Cancel and return to menu" << endl;
				int select2;
				cin >> select2;
				if (select2 == 1)
				{
					if (temp->left != NULL)
					{
						temp = temp->left;
						continue;
					}
					else
					{
						cout << "It seems that this folder doesn't have a sub-directory!  ";
						char c = _getch();
						return NULL;
					}
				}
				else if (select2 == 2)
				{
					Node t = new Node(temp->right);
					delete temp->right;
					temp->right = NULL;
					Node* temp2 = new Node(t);
					return temp2;
				}
				else
				{
					return NULL;
				}
			}
		}
		
	}
	Node* get_dir()
	{

		cout << "Do you want to select the directory for merging from Patients Directory or Logs Directory?" << endl;
		cout << "1.Patients" << endl;
		cout << "2.Logs" << endl << endl;;

		int select;
		cin >> select;
		Node* temp = root;
		switch (select)
		{

		case 1:
		{
			temp = root->left;//Select patients
			break;
		}
		case 2:
		{
			temp = root->right;//Select Logs
			break;
		}

		}



		while (1)
		{
			cout << "Path: " << temp->path << endl;
			if (temp->left == NULL)
			{
				cout << "This dir doesnt have a sub-directory! Exiting " << endl;
				
			}
			else
			{
				cout << "This dir has a sub-directory with name " << temp->left->name << " .Select from the following actions : " << endl;
				cout << "1.Select sub-directory as source dir	2.Goto Sub-Directory	3 .Cancel and return to menu" << endl;
				int select2;
				cin >> select2;
				if (select2 == 1)
				{
					
						temp = temp->left;
						return temp;
					
					
				}
				else if (select2 == 2)
				{
					if (temp->left != NULL)
					{
						temp = temp->left;
						continue;
					}
					else
					{
						cout << "It seems that this folder doesn't have a sub-directory!  ";
						char c = _getch();
						return NULL;
					}
					
				}
				else
				{
					return NULL;
				}
			}
		}
		return NULL;
	}

	Node* clone_dir(Node* start)//Will be used for copying and moving directory
	{
		if (start == NULL)
		{
			return NULL;
		}
		Node* temp = new Node(start);
		temp->left = clone_dir(start->left);
		temp->right = clone_dir(start->right);
		return temp;
	}
	
	void copy_dir()
	{
		cout << "Copy|" << endl;
		Node* to_copy = get_for_copy_dir();
		if (to_copy == NULL)
		{
			return;
		}
		
		system("cls");
		cout << "Paste| " << to_copy->name<<endl;
		//This is copied from the add dir func:

			cout << "Do you want to insert the new directory in Patients Directory or Logs Directory?" << endl;
			cout << "1.Patients" << endl;
			cout << "2.Logs" << endl << endl;;

			int select;
			cin >> select;
			Node* temp = root;
			switch (select)
			{
				case 1:
				{
					temp = temp->left;
					break;
				}

				case 2:
				{
					temp = temp->right;
					break;
				}
			}

			while (1)
			{
				cout << "Path: " << temp->path << endl;
				if (temp->left == NULL)
				{
					cout << "This dir has space for new dir! Do you want to add the copied directory here? " << endl;
					cout << "1.Yes			2.Cancel and return to menu" << endl;
					int select2;
					cin >> select2;
					if (select2 == 1)
					{
						
						temp->left = clone_dir(to_copy);
						temp->left->set_path_auto(root);
						return;
					}
					else
					{
						return;
					}
				}
				else
				{
					cout << "This dir has a sub-dir already. Do you want to go into the sub-dir or cancel this action? " << endl;
					cout << "1.Goto sub-dir			2.Cancel and return to menu" << endl;
					int select2;
					cin >> select2;
					if (select2 == 1)
					{
						temp = temp->left;
						continue;
					}
					else
					{
						return;
					}
				}
			}
	}

	Node* get_for_copy_dir()
	{
		cout << "Do you want to select the dir for copying in Patients Directory or Logs Directory?" << endl;
		cout << "1.Patients" << endl;
		cout << "2.Logs" << endl << endl;;

		int select;
		cin >> select;
		Node* temp = root;
		switch (select)
		{

		case 1:
		{
			temp = root->left;//Select patients
			break;
		}
		case 2:
		{
			temp = root->right;//Select Logs
			break;
		}

		}



		while (1)
		{
			cout << "Path: " << temp->path << endl;
			if (temp == NULL)//If sub directory doesnt exist exit
			{
				cout << "This dir doesnt have a sub-directory! Returning to menu... " << endl;
				char c = _getch();
				return NULL;
			}
			else
			{//Ask the user to either goto sub-dir or copy the sub dir or cancel and return to menu
				cout << "This directory has sub-directory "<<temp->left->name << " .Select from the following actions : " << endl;
				cout << "1.Goto sub-dir			2.Copy this sub-Dir	and Delete it		3.Cancel and return to menu" << endl;
				int select2;
				cin >> select2;
				if (select2 == 1)
				{
					if (temp->left != NULL)
					{
						temp = temp->left;
						continue;
					}
					else
					{
						cout << "It seems that this folder doesn't have a sub-directory!  ";
						char c = _getch();
						return NULL;
					}
				}
				else if (select2 == 2)
				{
					Node* temp2 = clone_dir(temp->left);
					temp->left = NULL;
					return temp2;
				}
				else
				{
					return NULL;
				}
			}
		}

	}
	void merge_dirs()
	{
		cout << "Merge|" << endl;
		Node* to_copy = get_dir();
		if (to_copy == NULL)
		{
			return;
		}

		system("cls");
		cout << "Merge| " << to_copy->name << endl;

		while (1)
		{
			cout << "Do you want to insert the new file in Patients Directory or Logs Directory?" << endl;
			cout << "1.Patients" << endl;
			cout << "2.Logs" << endl << endl;;

			int select;
			cin >> select;
			Node* temp = NULL;
			switch (select)
			{
			case 1:
			{
				temp = root->left;//Select patients
				while (1)
				{
					cout << "Path: " << temp->path << endl;
					if (temp->right == NULL)
					{
						cout << "This dir has space for new file! Do you want to add the copy of file here? " << endl;
						cout << "1.Yes		2.Goto Sub-Directory of Current Directory			3.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							temp->right = new Node(to_copy);
							temp->right->set_path_auto(root);

							return;
						}
						else if (select2 == 2)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
					else
					{
						cout << "This dir has a file already. Do you want to go into the sub-dir or cancel this action? " << endl;
						cout << "1.Goto sub-dir			2.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
				}
				return;
			}

			case 2:
			{
				temp = root->right;//Select Logs
				while (1)
				{
					cout << "Path: " << temp->path << endl;
					if (temp->right == NULL)
					{
						cout << "This dir has space for new file! Do you want to add the copy of file here? " << endl;
						cout << "1.Yes		2.Goto Sub-Directory of Current Directory			3.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							temp->right = new Node(to_copy);

							temp->right->set_path_auto(root);


							return;
						}
						else if (select2 == 2)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
					else
					{
						cout << "This dir has a file already. Do you want to go into the sub-dir or cancel this action? " << endl;
						cout << "1.Goto sub-dir			2.Cancel and return to menu" << endl;
						int select2;
						cin >> select2;
						if (select2 == 1)
						{
							if (temp->left != NULL)
							{
								temp = temp->left;
								continue;
							}
							else
							{
								cout << "It seems that this folder doesn't have a sub-directory! Going back to menu. Press a button to continue ";
								char c = _getch();
								return;
							}
						}
						else
						{
							return;
						}
					}
				}
				return;
			}
			default:
				cout << "Wrong option! ";

				continue;
			}
		}
	}
	void search(string name)//Function is used to search for the path of a file/Directory by given name by using level order traversal
		{
			Queue q;
			q.enqueue(root);
			q.enqueue(NULL);
			
			while (!(q.isEmpty()))
			{
				Node* temp = q.get_front();
				q.dequeue();

				if (temp == NULL)
				{
					cout << endl;
					if (!(q.isEmpty()))
					{
						q.enqueue(NULL);
					}
				}
				else
				{
					if (temp->name == name)
					{
						cout << "Found and path is: " << temp->path<<endl;
						return;
					}
					if (temp->left)
					{
						q.enqueue(temp->left);
					}
					if (temp->right)
					{
						q.enqueue(temp->right);
					}
				}
			}
			
				cout << "The file or folder by name does not exist! ";
			
			return;
		}
	};

	