#include <vector>
#include <string>
#include <unordered_map>
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
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ini_parser.hpp"

using namespace std;
using namespace boost::property_tree;

class Analysis {

private:
    string path;
    string stopWordsPath;
    string positiveWordsPath;
    string negativeWordsPath;
    vector<string> positiveWords;
    vector<string> negativeWords;
    vector<string> stopWords;
    IPatternMatching* positiveMatch;
    IPatternMatching* negativeMatch;
    IPatternMatching* stopMatch;

public:
    Analysis(string& path, int algorithm)
    {
        ptree pt;
        ini_parser::read_ini("config.ini", pt);

        this->path = path;
        this->stopWordsPath = pt.get<string>("file.stop_words_file");
        this->positiveWordsPath = pt.get<string>("file.positive_words_file");
        this->negativeWordsPath = pt.get<string>("file.negative_words_file");

        positiveWords = Helper::readWordsFromFile(positiveWordsPath);
        negativeWords = Helper::readWordsFromFile(negativeWordsPath);
        stopWords = Helper::readWordsFromFile(stopWordsPath);

        if (algorithm == 1) {
            this->positiveMatch = new AhoCorasickAutomaton();
            this->negativeMatch = new AhoCorasickAutomaton();
            this->stopMatch = new AhoCorasickAutomaton();
        }
        else if (algorithm == 2) {
            this->positiveMatch = new TrieSearch();
            this->negativeMatch = new TrieSearch();
            this->stopMatch = new TrieSearch();
        }
        else if (algorithm == 3) {
            this->positiveMatch = new KnuthMorrisPratt();
            this->negativeMatch = new KnuthMorrisPratt();
            this->stopMatch = new KnuthMorrisPratt();
        }
        assignPatterns();
    }

    void assignPatterns() {
        this->positiveMatch->preProcessing(positiveWords);
        this->stopMatch->preProcessing(stopWords);
        this->negativeMatch->preProcessing(negativeWords);
    }

    void generateReport() {

        vector<filesystem::path> files = Helper::getListofFiles(this->path);
        vector<DirectoryAnalysis*> directoryAnalysisList;
        vector<FileAnalysis*> fileAnalysisList;

        int i = 0;

        for (auto& file : files) {
            string content = Helper::readFile(file);
            ostringstream stream;

            auto start = std::chrono::high_resolution_clock::now();
            unordered_map<string, int> positiveRes = this->positiveMatch->searchIn(content);
            unordered_map<string, int> negativeRes = this->negativeMatch->searchIn(content);
            unordered_map<string, int> stopRes = this->stopMatch->searchIn(content);
            auto finish = std::chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = finish - start;
            stream << fixed << setprecision(7) << elapsed.count() << "s";

            if (files.size() > 1) {
                DirectoryAnalysis* directoryAnalysis = new DirectoryAnalysis(file.filename().string(), positiveRes.size(), negativeRes.size(), stopRes.size(), positiveRes.size() - negativeRes.size(), stream.str());
                directoryAnalysisList.push_back(directoryAnalysis);
            }
            else
            {
                for (auto& it : positiveRes) {
                    FileAnalysis* fileAnalysis = new FileAnalysis(it.first, it.second, "Positive");
                    fileAnalysisList.push_back(fileAnalysis);
                }
                for (auto& it : negativeRes) {
                    FileAnalysis* fileAnalysis = new FileAnalysis(it.first, it.second, "Negative");
                    fileAnalysisList.push_back(fileAnalysis);
                }
                for (auto& it : stopRes) {
                    FileAnalysis* fileAnalysis = new FileAnalysis(it.first, it.second, "Stop");
                    fileAnalysisList.push_back(fileAnalysis);
                }
            }
            i++;
            if (i == 5) break;
        }

        if(directoryAnalysisList.size()>0)
            FileService::generateDirectoryLevelAnalysis(directoryAnalysisList);
        else if (fileAnalysisList.size() > 0)
            FileService::generateFileLevelAnalysis(fileAnalysisList);
    }
};