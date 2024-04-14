#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include "IPatternMatching.h"
#include "KnuthMorrisPratt.h"
#include "AhoCorasickAutomaton.h"
#include "TrieSearch.h"
#include "Helper.h"
#include "DirectoryAnalysis.h"
#include "FileAnalysis.h"
#include "FileService.h"
#include "IAnalysis.h"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ini_parser.hpp"

using namespace boost::property_tree;

/// <summary>
/// Contains methods which parellely searches for bag of words
/// </summary>
class ParellelAnalysis : public IAnalysis {

private:

    std::string path;
    std::string stopWordsPath;
    std::string positiveWordsPath;
    std::string negativeWordsPath;
    std::vector<std::string> positiveWords;
    std::vector<std::string> negativeWords;
    std::vector<std::string> stopWords;
    IPatternMatching* positiveMatch;
    IPatternMatching* negativeMatch;
    IPatternMatching* stopMatch;
    std::string algorithmType;
    size_t memoryUsagePreprocessing;
    double elapsedPreprocess;

public:

    /// <summary>
    /// Contructor for Parellel analysis class
    /// </summary>
    /// <param name="path"></param>
    /// <param name="algorithm"></param>
    ParellelAnalysis(std::string& path, size_t algorithm)
    {
        ptree pt;
        ini_parser::read_ini("config.ini", pt);

        this->path = path;
        this->stopWordsPath = pt.get<std::string>("file.stop_words_file");
        this->positiveWordsPath = pt.get<std::string>("file.positive_words_file");
        this->negativeWordsPath = pt.get<std::string>("file.negative_words_file");

        positiveWords = Helper::readWordsFromFile(positiveWordsPath);
        negativeWords = Helper::readWordsFromFile(negativeWordsPath);
        stopWords = Helper::readWordsFromFile(stopWordsPath);

        if (algorithm == 1) {
            this->positiveMatch = new AhoCorasickAutomaton();
            this->negativeMatch = new AhoCorasickAutomaton();
            this->stopMatch = new AhoCorasickAutomaton();
            this->algorithmType = "AhoCorasickParellel";
        }
        else if (algorithm == 2) {
            this->positiveMatch = new TrieSearch();
            this->negativeMatch = new TrieSearch();
            this->stopMatch = new TrieSearch();
            this->algorithmType = "TrieSearchParellel";
        }
        else if (algorithm == 3) {
            this->positiveMatch = new KnuthMorrisPratt();
            this->negativeMatch = new KnuthMorrisPratt();
            this->stopMatch = new KnuthMorrisPratt();
            this->algorithmType = "KMPParellel";
        }

        assignPatterns();
    }

    /// <summary>
    /// assign patterns and approiate classes based on the config file
    /// </summary>
    void assignPatterns();

    /// <summary>
    /// Generate the report and output file
    /// </summary>
    void generateReport();
};