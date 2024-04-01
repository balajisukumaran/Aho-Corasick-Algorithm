#include "TrieSearch.h"
#include "Helper.h"

using namespace std;

/// <summary>
/// build the trie
/// </summary>
/// <param name="patterns"></param>
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

/// <summary>
/// PreProcesses patterns to search 
/// </summary>
/// <param name="wordBag"></param>
void TrieSearch::preProcessing(vector<string>& wordBag)
{
    this->buildTrie(wordBag);
}

/// <summary>
/// Search for the patterns
/// </summary>
/// <param name="sentence"></param>
/// <returns></returns>
map<string, int> TrieSearch::searchIn(const string& storyContent) {
    map<string, int> result;
    string sentence = " " + storyContent + " ";  // Add padding to handle beginning and end of string.

    for (int i = 1; i < sentence.length() - 1; ) {
        Node* current = this->root;
        string wordFound;

        for (int j = i; j < sentence.length() - 1; j++) {
            char c = sentence[j];

            if (current->child.find(c) == current->child.end()) {
                break;
            }

            current = current->child[c];  // Move to the next node in the trie.

            if (current != nullptr && current->currentWord != "") {
                if (Helper::isWordBoundary(sentence[j + 1]) && Helper::isWordBoundary(sentence[i - 1])) {
                    wordFound = current->currentWord;  // Store the most recent word found.
                    if (result.find(wordFound) == result.end()) {
                        result[wordFound] = 1;
                    }
                    else {
                        result[wordFound]++;
                    }
                }
            }
        }

        if (!wordFound.empty()) {
            i += wordFound.length();  // Move past the end of the found word.
        }
        else {
            i++;  // Move to the next character
        }
    }

    return result;
}