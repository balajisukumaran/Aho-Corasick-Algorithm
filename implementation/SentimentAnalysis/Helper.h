#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm> 
#include <filesystem>
#include <fstream>
#include <unordered_set>

using namespace std;

class Helper {
public:
	static vector<string> split(const string& str, char delimiter);
	static void removeSpecialCharacters(string& str);
	static vector<filesystem::path> getListofFiles(string& path);
	static string readFile(const filesystem::path& path);
    static vector<string> readWordsFromFile(const string& file_path);
	static unordered_set<char> punctuation;
};