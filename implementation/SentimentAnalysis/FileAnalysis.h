#pragma once
#include <string>

using namespace std;

/// <summary>
/// Model class for File Analysis data
/// </summary>
class FileAnalysis {
public:

    /// <summary>
    /// word found
    /// </summary>
    string word;

    /// <summary>
    /// count 
    /// </summary>
    size_t occurency;

    /// <summary>
    /// word type
    /// </summary>
    string wordType;

    /// <summary>
    /// contructor for File Analysis
    /// </summary>
    /// <param name="word"></param>
    /// <param name="occurency"></param>
    /// <param name="wordType"></param>
    FileAnalysis(const string& word, size_t occurency, const string& wordType)
        : word(word), occurency(occurency), wordType(wordType)
    {
    }
};