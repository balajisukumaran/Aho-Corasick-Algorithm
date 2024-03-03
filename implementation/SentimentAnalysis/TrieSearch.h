#pragma once
#include "Node.h"
#include "IPatternMatching.h"

using namespace std;

class TrieSearch : public IPatternMatching {

private:
    Node* root;
    void buildTrie(vector<string>& patterns);

public:
    void preProcessing(vector<string>& wordBag) override;
    unordered_map<string, int> searchIn(string& sentence) override;
};