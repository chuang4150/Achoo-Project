#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include "Disease.h"

using namespace std;

bool SearchTree::symptomPresent(vector<string> sympList, string symptom) //modified from http://codereview.stackexchange.com/questions/59997/contains-algorithm-for-stdvector
{
	if (sympList.empty())
	{
		return false; //return false immediately if there are no symptoms to compare to
	}
	if (find(sympList.begin(), sympList.end(), symptom) != sympList.end()) //search through non-empty vector for symptom
	{
		return true; //if there is a matching symptom, return true
	}
	else
	{
		return false; //no matches? return false
	}
}

void SearchTree::insertNode(Disease illness) //insert nodes into SearchTree objects
{
	Node *newNode;
	newNode = new Node;
	newNode->disease = illness; //object of disease class is data of node
	newNode->Lchild = newNode->Rchild = NULL; //set children to null

	if (root == NULL)
	{
		root = newNode; //if the tree doesn't yet have a root, give it one
	}
	else
	{
		Node *temp = root;
		while (temp != NULL)
		{
			if (illness.symptoms.size() <= temp->disease.symptoms.size()) //compare vector sizes 
			{
				if (temp->Rchild != NULL) //go to the right
				{
					temp = temp->Rchild;
				}
				else
				{
					temp->Rchild = newNode;
					break;
				}
			}
			else if (illness.symptoms.size() > temp->disease.symptoms.size()) //if the object has more symptoms
			{
				if (temp->Lchild != NULL) //go to the left
				{
					temp = temp->Lchild;
				}
				else
				{
					temp->Lchild = newNode;
					break;
				}
			}

		}
	}
}


int SearchTree::CountNodes(Node*node)  
{
	Node * Tmp = root;
	int count = 0;
	stack<Node*> S;
	while (1)
	{
		//traverse left until its NULL & push
		while (Tmp != NULL)
		{
			S.push(Tmp);
			Tmp = Tmp->Lchild;
		}
		//if stack is empty stop the process
		if (S.empty()) return count;

		//if not empty, pop 1 and go right
		Tmp = S.top();
		S.pop();
		count++;
		Tmp = Tmp->Rchild;
	}
}

SearchTree SearchTree::TraverseTree(string symptom, SearchTree newTree) //given a symptom, create new node in newTree
{ //modifed from w8.2, slide 33
	Node *temp = root;
	stack<Node*> nodeStack;

	while (1)
	{
		while (temp != NULL)
		{
			nodeStack.push(temp);
			temp = temp->Lchild;
		}
		if (nodeStack.empty()) return newTree;

		temp = nodeStack.top();
		nodeStack.pop();
		if (symptomPresent(temp->disease.symptoms, symptom))
		{
			newTree.insertNode(temp->disease); //put the disease in the new tree
		//	cout << "Inserting node: " << temp->disease.name << endl;
		}
		temp = temp->Rchild;
	}
}

Disease::Disease()
{
	name = "No name";
	sex = NULL;
	symptoms = vector<string>{}; 
}
Disease::Disease(char* illnessName, char* diseaseSex, vector<string> symptomVector) 
{
	name = illnessName;
	sex = diseaseSex;
	symptoms = symptomVector;
}
Disease::~Disease()
{
	if (!name.empty()) //string
	{
		name.clear();
	}

	if (sex != NULL) //*char
	{
		sex = NULL;
	}
	if (!symptoms.empty()) //vector<string>
	{
		symptoms.clear();
	} 

}

void SearchTree::deleteTree(Node* node) //modified from http://cboard.cprogramming.com/cplusplus-programming/57293-deleting-all-nodes-binary-search-tree.html
{
	if (node == NULL)
	{
		return;
	}
	if (node->Lchild != NULL)
	{
		node->Lchild = NULL;
	}
	if (node->Rchild != NULL)
	{
		node->Rchild = NULL;
	}
	delete node;
	root = NULL; //otherwise the root wants to hang around and will throw off your results
}


void SearchTree::readTree() //just print everything out
{ //modifed from book, pg 333
	Node *temp = root;
	Node *parent = root;
	Node *child = root;
	stack<Node*> nodeStack;

	while (1)
	{
		while (temp != NULL)
		{
			nodeStack.push(temp);
			temp = temp->Lchild;
		}
		if (nodeStack.empty()) return;

		temp = nodeStack.top();
		nodeStack.pop();
		string strName = temp->disease.name;
		cout << strName << endl;
		temp = temp->Rchild;
	}

}

SearchTree SearchTree::sortBySex(string sex, SearchTree newTree) //clear out sex-based diseases (ex: prostate cancer, menopause)
{ //modified from book, pg 333
	Node *temp = root;
	Node *parent = root;
	Node *child = root;
	stack<Node*> nodeStack;

	while (1)
	{
		while (temp != NULL)
		{
			nodeStack.push(temp);
			temp = temp->Lchild;
		}
		if (nodeStack.empty()) return newTree;

		temp = nodeStack.top();
		nodeStack.pop();
		string tempSex = temp->disease.sex;
		if (tempSex.compare(sex) == 0 || tempSex.compare("m/f") == 0) //if the sex matches, put disease in the tree; .compare() returns 0 if true
		{
			//	cout << symptom << " is present in " << temp->disease.name << endl;
			newTree.insertNode(temp->disease); //put the disease in the new tree
		}
		temp = temp->Rchild;
	}
}