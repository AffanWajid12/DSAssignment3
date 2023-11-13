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
	Node(string name,bool type,Node* root)
	{
		this->name = name;
		path = set_path(name,root);
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
	string set_path(string name,Node* root)
	{
		string left = "";
		string right = "";
		if (root == NULL)
		{
			return name;
		}
		if (name == root->name)
		{
			return name;

		}
		else if(name != root->name)
		{
			
			if (root->left && !(root->left->type) )//Check if it is not NULL and is also a directory
			{
				 left = set_path(name, root->left);
			}

			if (root->right && !(root->right->type))//Check if it is not NULL and is also a directory
			{
				right = set_path(name, root->right);
			}

			if (!(root->left || root->right))//If both of them non existent
			{
				return "|";
			}


		}

		if (!(contains_sym(left)))
		{
			return root->name+left;
			
		}
		else if(!(contains_sym(left)))
		{
			return root->name+right ;
		}
		
		return "No Path";
		
	}
	void set_path_auto(Node* root)
	{
		this->path = set_path(name, root);
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
		if(!(isEmpty()) && front !=NULL)
			return front->data;

		return NULL;
	}
	void dequeue()
	{
		if (isEmpty() )
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
		root = new Node("\\",false,root);
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
	}
	void add_file()
	{

	}
	void add_dir()
	{

	}
};