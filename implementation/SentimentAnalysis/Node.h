#pragma once
#include<unordered_map>
#include<string>

using namespace std;

class Node {

public:
	string currentWord;
	unordered_map<char, Node*> child;
	Node* suffixLink;
	Node* outputLink;

	Node() {
		suffixLink = nullptr;
		outputLink = nullptr;
	}
};