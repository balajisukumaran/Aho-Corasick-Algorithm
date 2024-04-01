#pragma once
#include "Node.h"
#include "IPatternMatching.h"
#include <queue>
#include <unordered_set>
#include <map>

using namespace std;

/// <summary>
/// AhoCorasick Search
/// </summary>
class AhoCorasickAutomaton : public IPatternMatching {

private:

    /// <summary>
    /// Trie root
    /// </summary>
    Node* root;

    /// <summary>
    /// build the suffix and output links for the trie
    /// </summary>
    void buildSuffixAndOutputLinks();

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