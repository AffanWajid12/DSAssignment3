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
		if (root == NULL)
		{
			return "";
		}
		if (name == root->name)
		{
			return name;

		}

		left = set_path(name, root->left,"");
		right = set_path(name, root->right,"");

		if (left != "")
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
		else if(right!="")
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
		return left + right;
	}

	/*
	string set_path(string name, Node* root)
	{

		string left = "";
		string right = "";
		if (root == NULL)
		{
			return "|";
		}
		if (name == root->name)
		{
			return name;

		}
		
		if (name != root->name)
		{
			if (root->left || root->right)
			{
				if (root->left)//Check if it is not NULL and is also a directory
				{
					left = set_path(name, root->left);
				}

				if (root->right)//Check if it is not NULL and is also a directory
				{
					right = set_path(name, root->right);
				}

				if (!(contains_sym(left)))
				{
				//
					if (root->name != "\\" && type == false)
					{

						return root->name + "\\" + left;
					}
					else if (root->name != "\\" && type == true)
					{
						return root->name + "\\" + left + name;
					}
					else
					{
						return root->name + left;
					}//
					if (root->name != "\\")
					{

						return root->name + "\\" + left;
					}
					return "\\" + left;
				}
				else if (!(contains_sym(right)))
				{//
					if (root->name != "\\")
					{

						return root->name + "\\" + right;
					}
					else if (root->name != "\\" && type == true)
					{
						return root->name + "\\" + left + name;
					}
					else
					{
						return root->name + right;
					}//
					if (root->name != "\\")
					{

						return root->name + "\\" + right;
					}
					return "\\" + right;
				}
			}
			else if(root->left == NULL && root->right == NULL)
			{
				return "|";
			}


		}


		

		return "No Path";

	}*/
	void set_path_auto(Node* root)
	{
		/*
		string path = "";
		bool check = set_path(name, root, path);
		if (check)
		{
			this->path = path;
		}
		else
		{
			this->path = "Path does not exist";
		}*/
		this->path = set_path(name, root,"");
	}

};

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

class FileTree
{
private:
	Node* root;

public:
	FileTree()
	{
		root = new Node("\\", false, root);

		root->left = new Node("Patients");
		root->left->set_path_auto(root);

		root->right = new Node("Logs");
		root->right->set_path_auto(root);
	}

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
						cout << "This dir has space for new file! Do you want to add the new directory here? " << endl;
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
						cout << "This dir has space for new file! Do you want to add the new directory here? " << endl;
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

	}
	void search(string name)
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
					cout << "Found and path is: " << temp->path;
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