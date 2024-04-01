#pragma once
#include "Node.h"
#include "IPatternMatching.h"
#include "map"

using namespace std;

/// <summary>
/// Trie Search implementation
/// </summary>
class TrieSearch : public IPatternMatching {

private:

    /// <summary>
    /// Trie Root
    /// </summary>
    Node* root;

    /// <summary>
    /// build the trie
    /// </summary>
    /// <param name="patterns"></param>
    void buildTrie(vector<string>& patterns);

public:

    /// <summary>
    /// PreProcesses patterns to search 
    /// </summary>
    /// <param name="wordBag"></param>
    void preProcessing(vector<string>& wordBag) override;

    /// <summary>
    /// Search for the patterns
    /// </summary>
    /// <param name="sentence"></param>
    /// <returns></returns>
    map<string, int> searchIn(const string& sentence) override;
};