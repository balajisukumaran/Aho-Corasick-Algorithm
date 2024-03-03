#pragma once
#include "Node.h"
#include "IPatternMatching.h"
#include <queue>
#include <unordered_set>

using namespace std; 

class AhoCorasickAutomaton : public IPatternMatching {

private:
    Node* root;
    void buildSuffixAndOutputLinks();
    void buildTrie(vector<string>& patterns);

public:
    void preProcessing(vector<string>& wordBag) override;
    unordered_map<string, int> searchIn(string& sentence) override;
};