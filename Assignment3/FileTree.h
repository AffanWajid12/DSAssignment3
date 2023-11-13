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
	string set_path(string name,Node* root)
	{
		string left = "";
		string right = "";
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

			if (!(root->left && root->right))
			{
				return "|";
			}


		}

		if (!(left.find('|')))
		{
			return left;
			
		}
		else if(!(right.find('|')))
		{
			return right;
		}
		
		return "No Path";
		
	}
};


class Queue
{

};

class FileTree
{
private:
	Node* root;

public:
	FileTree()
	{
		root = new Node("\\",false,root);
		root->left = new Node("Patients", false,root);
		root->right = new Node("Logs", false,root);
	}
	
	void 
};