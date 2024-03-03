#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "IPatternMatching.h"

using namespace std;

class KnuthMorrisPratt : public IPatternMatching {

private:
	unordered_map<string, vector<int>> prefixTable;
	
public:
	void preProcessing(vector<string>& wordBag) override;
	unordered_map<string, int> searchIn(string& sentence) override;
};