#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class IPatternMatching {

public:
	virtual	void preProcessing(vector<string>& wordBag) = 0 ;
	virtual	unordered_map<string, int> searchIn(string& sentence) = 0;
};