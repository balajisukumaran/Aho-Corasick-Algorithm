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

/// <summary>
/// contaisn helper methods for the application
/// </summary>
class Helper {
public:

    /// <summary>
    /// splits the sentence based on character
    /// </summary>
    /// <param name="str">str to split</param>
    /// <param name="delimiter">character to split</param>
    /// <returns></returns>
    static vector<string> split(const string& str, char delimiter);

    /// <summary>
    /// remove special character
    /// </summary>
    /// <param name="str">string</param>
    static void removeSpecialCharacters(string& str);

    /// <summary>
    /// get the list of files in a directory
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    static vector<filesystem::path> getListofFiles(string& path);

    /// <summary>
    /// read file
    /// </summary>
    /// <param name="path">path of the file</param>
    /// <returns>file content</returns>
    static string readFile(const filesystem::path& path);

    /// <summary>
    /// read words from a file
    /// </summary>
    /// <param name="file_path">file to read</param>
    /// <returns>words</returns>
    static vector<string> readWordsFromFile(const string& file_path);

    /// <summary>
    /// puntuation in scope
    /// </summary>
    static unordered_set<char> punctuation;

    /// <summary>
    /// puntuation boundary
    /// </summary>
    /// <param name="c">charac</param>
    /// <returns>is the character surrounded by puntuation</returns>
    static bool isWordBoundary(char c);
};