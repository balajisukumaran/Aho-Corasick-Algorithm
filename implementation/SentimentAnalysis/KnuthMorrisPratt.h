#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include "IPatternMatching.h"

using namespace std;

/// <summary>
/// KMP algorithm implementation
/// </summary>
class KnuthMorrisPratt : public IPatternMatching {

private:

    /// <summary>
    /// prefix tables for each word
    /// </summary>
    unordered_map<string, vector<int>> prefixTable;

public:
    /// <summary>
    /// Preprocessing the patterns
    /// </summary>
    /// <param name="wordBag"></param>
    void preProcessing(vector<string>& wordBag) override;

    /// <summary>
    /// Use KMP algorithm to search for patterns
    /// </summary>
    /// <param name="sentence">input sentence</param>
    /// <returns>words and counts</returns>
    map<string, int> searchIn(const string& sentence) override;
};