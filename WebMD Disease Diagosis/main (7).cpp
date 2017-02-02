#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Disease.h"

using namespace std;

string lower(string input);

int main() {

	SearchTree tree; //tree for diseases
	vector<string> tempVect; //put symtoms in and clear out with each use
	char illnessName[200];
	char diseaseSex[4];
	char symptArray[500];

	stringstream ss;

	ifstream in;
	in.open("full_disease_list.txt");
	if (!in.is_open())
	{
		cout << "Incorrect file for diseases.\n";
		return false;
	}
	//Shingles, B, Skin blisters, Headache, Pain or discomfort, Fever, Skin rash, Skin bumps
	while (in.peek() != EOF)
	{
		in.getline(illnessName, 200, ',');
		if ((unsigned)strlen(illnessName) < 3) //after the last disease it will attempt to grab another line
		{
			break; //stop it
		}
		//cout << illnessName << endl; //first word is name of illness
		in.getline(diseaseSex, 4, ',');
		//cout << diseaseSex << endl; //second is sex
	
		in.getline(symptArray, 500, '\n'); //get the rest of the line
		char* tokens;
		tokens = strtok(symptArray, ",\n"); //http://www.cplusplus.com/reference/cstring/strtok/ break into symptoms
		while (tokens != NULL)
		{
			tempVect.push_back(tokens);
			tokens = strtok(NULL, ",\n");
		}

		Disease illness = Disease(illnessName, diseaseSex, tempVect); //throw it all into the disease
		tree.insertNode(illness); 
		tempVect.clear();
	}

	string hasDiseases;
	cout << "Are you diseased?\n";
	cin >> hasDiseases;
	hasDiseases = lower(hasDiseases);


	if (hasDiseases.compare("n") == 0 || hasDiseases.compare("no") == 0)
	{
		cout << "Glad to hear it. Have a good day\n";
	}
	while (hasDiseases.compare("y") == 0 || hasDiseases.compare("yes") == 0) //0 means valid comparison
	{
		string userSex;
		cout << "Are you male or female?\n";
		cin >> userSex;
		userSex = lower(userSex);


		if (userSex.compare("male") == 0 || userSex.compare("m") == 0) //returns 0 if true
		{
			userSex = "m";
		}
		else if (userSex.compare("female") == 0 || userSex.compare("f") == 0)
		{
			userSex = "f";
		}
		else
		{
			cout << "Unfortunately we do not have any diseases listed for that sex so we will search without that filter.\n";
			userSex = "m/f";
		}

		SearchTree matchingTree;
		matchingTree = tree.sortBySex(userSex, matchingTree); //make matching tree first match the user's sex

		string symptom;
		cout << "Please enter a symptom: "; //then prompt for symptoms

		cin.ignore(500, '\n'); //need this for multi-word symptoms, ex: "chest pain"
		getline(cin, symptom);
		symptom = lower(symptom); 

		SearchTree secondaryTree; //make a secondary tree because you will need to swap between this and matchingtree
		
		secondaryTree = matchingTree.TraverseTree(symptom, secondaryTree); //get new tree filled out

		matchingTree.deleteTree(matchingTree.root); //clear out matching tree now that secondaryTree has been created
		//matchingTree.readTree(); this was to make sure the deleteTree() function was working properly

		if (secondaryTree.CountNodes(secondaryTree.root) == 0)
		{
			cout << "No known diseases match your symptoms. See a real doctor.\n";
		//	system("pause");
			return 0;
		}


		string answer;
		cout << "Do you have another symptom?\n";
		cin >> answer;
		answer = lower(answer);
		
		int numAnswers = 1;
		while (answer.compare("y") == 0 || answer.compare("yes") == 0) //if yes
		{
			cout << "Please enter a symptom: ";
			cin.ignore(500, '\n'); //need this for multi-word symptoms, ex: "chest pain"
			getline(cin, symptom);
			symptom = lower(symptom);
			if (numAnswers % 2 != 0) //if an even number
			{
				matchingTree = secondaryTree.TraverseTree(symptom, matchingTree); //reassign with new tree
				secondaryTree.deleteTree(secondaryTree.root); //delete the first tree
				if (matchingTree.CountNodes(matchingTree.root) == 0)
				{
					cout << "No known diseases match your symptoms. See a real doctor.\n";
				//	system("pause");
					return 0;
				}
			}
			else
			{
				secondaryTree = matchingTree.TraverseTree(symptom, secondaryTree); //reassign with the new tree
				matchingTree.deleteTree(matchingTree.root); //delete the first tree
				if (secondaryTree.CountNodes(secondaryTree.root) == 0)
				{
					cout << "No known diseases match your symptoms. See a real doctor.\n";
				//	system("pause");
					return 0;
				}
			}
			cout << "Do you have another symptom?\n";
			cin >> answer;
			answer = lower(answer);
			numAnswers++;
		}
		if (numAnswers % 2 == 0)
		{
			cout << "You may have the following diseases:\n";
			matchingTree.readTree();
		}

		else
		{
			cout << "You may have the following diseases:\n";
			secondaryTree.readTree();
		}

		cout << "Are there any other diseases you're curious to know if you have?\n";
		cin >> hasDiseases;
		hasDiseases = lower(hasDiseases);
	}
	
//	system("pause");
	return 0;
}

string lower(string input)
{
	for (unsigned int i = 0; i < input.length(); i++)
	{
		input[i] = tolower(input[i]); //http://www.cplusplus.com/reference/cctype/tolower/
	}
	return input;
}
