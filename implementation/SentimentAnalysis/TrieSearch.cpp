#include "TrieSearch.h"
#include "Helper.h"

using namespace std;

void TrieSearch::buildTrie(vector<string>& patterns)
{
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

void TrieSearch::preProcessing(vector<string>& wordBag)
{
    this->buildTrie(wordBag);
}

unordered_map<string, int> TrieSearch::searchIn(string& sentence)
{
    unordered_map<string, int> result;

    for (int i = 0; i < sentence.length(); i++) {
        Node* current = this->root;

        for (int j = i; j < sentence.length(); j++) {
            char c = sentence[j];
            
            if (current->child.find(c) == current->child.end())
                break;

            current = current->child[c];

            if (current->currentWord != "" && Helper::punctuation.find(sentence[j + 1]) != Helper::punctuation.end()) {
                string wordFound = current->currentWord;

                if (result.find(wordFound) == result.end())
                    result[wordFound] = 0;

                result[wordFound] = result[wordFound] + 1;
                i = j + 1;
                break;
            }
        }
    }

    return result;

}
