#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Disease
{
public: 
	string name;
	vector<string> symptoms;
	char* sex;
public:
	Disease();
	Disease(char* illnessName, char* diseaseSex, vector<string> symptomVector);
	~Disease(); 
};

class Node //modified off HW6
{
public:
	Disease disease;
	Node *Lchild;
	Node *Rchild;
};

class SearchTree //modified off HW6
{
public:
	Node *root;
	Node *nodePtr;
	int numNodes = 0;
public:
	SearchTree() {
		root = NULL;
	}
	void insertNode(Disease illness);
	int CountNodes(Node*node); 
	SearchTree TraverseTree(string symptom, SearchTree newTree);
	bool symptomPresent(vector<string>, string symptom);
	void deleteTree(Node* node);
	void readTree();
	SearchTree sortBySex(string sex, SearchTree newTree);
};

