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
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ini_parser.hpp"
#include "SequentialAnalysis.h"
#include "Analysis.cpp"

using namespace std;
using namespace boost::property_tree;

/// <summary>
/// assign patterns and approiate classes based on the config file
/// </summary>
void SequentialAnalysis::assignPatterns() {
    this->positiveMatch->preProcessing(positiveWords);
    this->stopMatch->preProcessing(stopWords);
    this->negativeMatch->preProcessing(negativeWords);
}

/// <summary>
/// Generate the report and output file
/// </summary>
void SequentialAnalysis::generateReport() {

    vector<filesystem::path> files = Helper::getListofFiles(this->path);
    vector<DirectoryAnalysis*> directoryAnalysisList;
    vector<FileAnalysis*> fileAnalysisList;
    vector<TextAnalysis*> textAnalysisList;

    auto totalTimeStart = std::chrono::high_resolution_clock::now();
    for (auto& file : files) {
        try {
            string content = Helper::readFile(file);
            ostringstream stream;

            auto start = std::chrono::high_resolution_clock::now();
            map<string, int> positiveRes = this->positiveMatch->searchIn(content);
            map<string, int> negativeRes = this->negativeMatch->searchIn(content);
            map<string, int> stopRes = this->stopMatch->searchIn(content);
            auto finish = std::chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = finish - start;

            cout << "File: " << file << endl;
            cout << "Execution Time: " << elapsed.count() << endl;
            cout << "Positive matches: " << positiveRes.size() << endl;
            cout << "Negative matches: " << negativeRes.size() << endl;
            cout << "Stop word matches: " << stopRes.size() << endl;
            cout << "============================================" << endl;

            stream << fixed << setprecision(7) << elapsed.count() << "s";

            if (files.size() > 1) {
                DirectoryAnalysis* directoryAnalysis = new DirectoryAnalysis(file.filename().string()
                    , positiveRes.size()
                    , negativeRes.size()
                    , stopRes.size()
                    , positiveRes.size() - negativeRes.size()
                    , stream.str());
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

            TextAnalysis* textAnalysis = new TextAnalysis(file.filename().generic_string(),
                std::count(content.begin(), content.end(), ' ') + 1,
                positiveRes.size(),
                negativeRes.size(),
                stopRes.size(),
                positiveRes.size() - negativeRes.size(),
                elapsed.count());

            textAnalysisList.push_back(textAnalysis);
        }
        catch (const std::exception& e) {
            std::cerr << "An exception occurred: " << e.what() << std::endl;
        }
    }
    auto totalTimeEnd = std::chrono::high_resolution_clock::now();
    chrono::duration<double> totalTimeElapsed = totalTimeEnd - totalTimeStart;


    Result* result = new Result(files.size(), algorithmType, totalTimeElapsed.count(), textAnalysisList);

    if (directoryAnalysisList.size() > 0)
        FileService::generateDirectoryLevelAnalysis(directoryAnalysisList);
    else if (fileAnalysisList.size() > 0)
        FileService::generateFileLevelAnalysis(fileAnalysisList);

    FileService::generateResultFile(result);
}