#pragma once
#include <string>

using namespace std;

class FileAnalysis {
public:
    string word;
    int occurency;
    string wordType;


    FileAnalysis(const string& word, int occurency, const string& wordType)
        : word(word), occurency(occurency), wordType(wordType)
    {
    }
};