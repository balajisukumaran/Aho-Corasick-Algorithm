#include "AhoCorasickAutomaton.h"
#include "Helper.h"

using namespace std;

void AhoCorasickAutomaton::preProcessing(vector<string>& wordBag) {
	this->buildTrie(wordBag);
	this->buildSuffixAndOutputLinks();
}

unordered_map<string, int> AhoCorasickAutomaton::searchIn(string& sentence) {

	Node* parent = this->root;
	unordered_map<string, int> result;

	for (size_t i = 0; i < sentence.length(); i++) {
		char c = sentence[i];

		if (parent->child.find(c) != parent->child.end()) {
			parent = parent->child[c];

			if (parent->currentWord != "") {
				
				if (i < sentence.length() && Helper::punctuation.find(sentence[i + 1]) != Helper::punctuation.end()) {
					string wordFound = parent->currentWord;

					if (result.find(wordFound) == result.end())
						result[wordFound] = 0;

					result[wordFound] = result[wordFound] + 1;
				}
			}

			Node* mol = parent->outputLink;

			while (mol != nullptr) {

				if (i < sentence.length() && Helper::punctuation.find(sentence[i + 1]) != Helper::punctuation.end()) {
					string wordFound = mol->currentWord; 

					if (result.find(wordFound) == result.end())
						result[wordFound] = 0; 
					
					result[wordFound] = result[wordFound] + 1; 
				}
				mol = mol->outputLink; 
			}
		}
		else {

			while (parent != this->root && parent->child.find(c) == parent->child.end()) { 
				parent = parent->suffixLink; 
			}
			
			if (parent->child.find(c) != parent->child.end()) i--;
		}
	}

	return result;
}

void AhoCorasickAutomaton::buildTrie(vector<string>& patterns) {

	this->root = new Node(); // Ensure root is initialized
	for (size_t i = 0; i < patterns.size(); i++) {
		Node* curr = root;
		for (char c : patterns[i]) {
			if (curr->child.find(c) != curr->child.end()) {
				curr = curr->child[c];
			}
			else {
				Node* newNode = new Node();
				curr->child[c] = newNode;
				curr = newNode;
			}
		}
		curr->currentWord = patterns[i];
	}
}

void AhoCorasickAutomaton::buildSuffixAndOutputLinks() {
	this->root->suffixLink = this->root;

	queue<Node*> queue;

	for (auto& rc : root->child) {
		queue.push(rc.second);
		rc.second->suffixLink = root;
	}

	while (!queue.empty()) {
		Node* curState = queue.front();
		queue.pop();

		for (auto& cc : curState->child) {
			Node* childNode = cc.second;
			Node* temp = curState->suffixLink;
			while (temp != root && temp->child.find(cc.first) == temp->child.end()) {
				temp = temp->suffixLink;
			}

			if (temp->child.find(cc.first) != temp->child.end()) {
				childNode->suffixLink = temp->child[cc.first];
			}
			else {
				childNode->suffixLink = root;
			}
			queue.push(childNode);
		}

		if (curState->suffixLink->currentWord != "") {
			curState->outputLink = curState->suffixLink;
		}
		else {
			curState->outputLink = curState->suffixLink->outputLink;
		}
	}
}
