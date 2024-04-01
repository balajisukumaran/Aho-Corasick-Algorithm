#pragma once
#include<unordered_map>
#include<string>

using namespace std;

/// <summary>
/// Trie Node
/// </summary>
class Node {

public:
    /// <summary>
    /// Current word  - If present leaf node
    /// </summary>
    string currentWord;

    /// <summary>
    /// Node childrens
    /// </summary>
    unordered_map<char, Node*> child;

    /// <summary>
    /// Suffix link
    /// </summary>
    Node* suffixLink;

    /// <summary>
    /// Output Link
    /// </summary>
    Node* outputLink;

    /// <summary>
    /// contructor for TrieNode
    /// </summary>
    Node() {
        suffixLink = nullptr;
        outputLink = nullptr;
    }
};