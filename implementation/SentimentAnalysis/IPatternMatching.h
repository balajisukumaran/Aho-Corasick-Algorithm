#pragma once
#include <iostream>
#include <vector>
#include <map>

using namespace std;

/// <summary>
/// Interface for pattern matching
/// </summary>
class IPatternMatching {

public:

	/// <summary>
	/// preprocessing the patterns
	/// </summary>
	/// <param name="wordBag"></param>
	virtual	void preProcessing(vector<string>& wordBag) = 0 ;

	/// <summary>
	/// search for the patterns
	/// </summary>
	/// <param name="sentence">sentence to search on</param>
	/// <returns>patterns matched count</returns>
	virtual	map<string, int> searchIn(const string& sentence) = 0;
};