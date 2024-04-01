#include "AhoCorasickAutomaton.h"
#include "Helper.h"

using namespace std;

/// <summary>
/// PreProcesses patterns to search 
/// </summary>
/// <param name="wordBag">bag of words</param>
void AhoCorasickAutomaton::preProcessing(vector<string>& wordBag) {
    this->buildTrie(wordBag);
    this->buildSuffixAndOutputLinks();
}


/// <summary>
/// Search for the patterns
/// </summary>
/// <param name="sentence">sentence to search</param>
/// <returns></returns>
map<string, int> AhoCorasickAutomaton::searchIn(const string& storyContent) {
    Node* parent = this->root;
    map<string, int> result;
    string sentence = " " + storyContent + " ";  // Add padding to handle beginning and end of string.

    for (size_t i = 1; i < sentence.length() - 1; i++) {
        char c = sentence[i];

        // Proceed with the next node in the trie or follow the suffix links back
        while (parent != this->root && parent->child.find(c) == parent->child.end()) {
            parent = parent->suffixLink;
        }

        if (parent->child.find(c) != parent->child.end()) {
            parent = parent->child[c];
        }

        // Now parent is either root or a node with the current character c as a valid child
        if (parent != nullptr) {
            Node* temp = parent;

            // Check for matches and follow output links
            while (temp != nullptr && temp != this->root) {
                if (!temp->currentWord.empty() && Helper::isWordBoundary(sentence[i - temp->currentWord.length()]) && Helper::isWordBoundary(sentence[i + 1])) {
                    string wordFound = temp->currentWord;

                    if (result.find(wordFound) == result.end()) {
                        result[wordFound] = 1;
                    }
                    else {
                        result[wordFound]++;
                    }
                }
                temp = temp->outputLink;
            }
        }
    }

    return result;
}


/// <summary>
/// build the trie
/// </summary>
/// <param name="patterns">patterns</param>
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

/// <summary>
/// build the suffix and output links for the trie
/// </summary>
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
