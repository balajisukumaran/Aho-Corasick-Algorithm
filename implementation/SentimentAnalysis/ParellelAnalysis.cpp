#include "ParellelAnalysis.h"
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
#include <future>
#include "Analysis.cpp"

using namespace boost::property_tree;

/// <summary>
/// Search result
/// </summary>
struct SearchResult {
    map<std::string, int> results;
    double executionTime;
};

/// <summary>
/// File details
/// </summary>
struct FileDetails {
    size_t index;
    std::string fileName;
    long long wordCount;
};

/// <summary>
/// Log the execution time when running parelly
/// </summary>
/// <param name="matcher">algorithm</param>
/// <param name="content">content</param>
/// <returns>search result</returns>
SearchResult performSearchAndMeasureTime(IPatternMatching* matcher, const std::string& content) {
    auto start = std::chrono::high_resolution_clock::now();
    auto results = matcher->searchIn(content);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    return SearchResult{ results, elapsed.count() };
}

/// <summary>
/// assign patterns and approiate classes based on the config file
/// </summary>
void ParellelAnalysis::assignPatterns() {
    size_t memBeforePreprocessing = 0, memAfterPreprocessing = 0;

    updateMemoryUsage(memBeforePreprocessing);
    auto start = std::chrono::high_resolution_clock::now();

    this->positiveMatch->preProcessing(positiveWords);
    this->stopMatch->preProcessing(stopWords);
    this->negativeMatch->preProcessing(negativeWords);

    updateMemoryUsage(memAfterPreprocessing);
    auto finish = std::chrono::high_resolution_clock::now();
    this->elapsedPreprocess = (finish - start).count();
    this->memoryUsagePreprocessing = memAfterPreprocessing - memBeforePreprocessing;
}

/// <summary>
/// Generate the report and output file
/// </summary>
void ParellelAnalysis::generateReport() {
    std::vector<filesystem::path> files = Helper::getListofFiles(this->path);

    std::vector<DirectoryAnalysis*> directoryAnalysisList;
    std::vector<FileAnalysis*> fileAnalysisList;
    std::vector<TextAnalysis*> textAnalysisList;

    // We will store futures for asynchronous execution
    std::vector<future<SearchResult>> futuresPositive;
    std::vector<future<SearchResult>> futuresNegative;
    std::vector<future<SearchResult>> futuresStop;
    std::vector<FileDetails> fileDetails;

    size_t memBeforePreprocessing = 0, memAfterPreprocessing = 0;

    auto totalTimeStart = std::chrono::high_resolution_clock::now();
    updateMemoryUsage(memBeforePreprocessing);
    // Launch asynchronous tasks
    size_t index = 0;
    for (auto& file : files) {
        try {
            std::string content = Helper::readFile(file);

            fileDetails.push_back(FileDetails{ index, file.filename().generic_string(), std::count(content.begin(), content.end(), ' ') + 1 });

            futuresPositive.push_back(async(launch::async, [this, content] {
                return performSearchAndMeasureTime(this->positiveMatch, std::ref(content));
                }));

            futuresNegative.push_back(async(launch::async, [this, content] {
                return performSearchAndMeasureTime(this->negativeMatch, std::ref(content));
                }));

            futuresStop.push_back(async(launch::async, [this, content] {
                return performSearchAndMeasureTime(this->stopMatch, std::ref(content));
                }));
        }
        catch (const std::exception& e) {
            std::cerr << "An exception occurred: " << e.what() << std::endl;
            fileDetails.push_back(FileDetails{ index, file.filename().generic_string(), 0 });
        }
        index++;
    }

    for (size_t i = 0; i < files.size(); ++i) {
        auto positiveRes = futuresPositive[i].get();
        auto negativeRes = futuresNegative[i].get();
        auto stopRes = futuresStop[i].get();

        cout << "File: " << files[i] << endl;
        cout << "Execution Time: " << positiveRes.executionTime + negativeRes.executionTime + stopRes.executionTime << endl;
        cout << "Positive matches: " << positiveRes.results.size() << endl;
        cout << "Negative matches: " << negativeRes.results.size() << endl;
        cout << "Stop word matches: " << stopRes.results.size() << endl;
        cout << "============================================" << endl;

        ostringstream stream;
        stream << fixed << setprecision(7) << (positiveRes.executionTime + negativeRes.executionTime + stopRes.executionTime) << "s";

        if (files.size() > 1) {
            DirectoryAnalysis* directoryAnalysis = new DirectoryAnalysis(fileDetails[i].fileName
                , positiveRes.results.size()
                , negativeRes.results.size()
                , stopRes.results.size()
                , positiveRes.results.size() - negativeRes.results.size()
                , stream.str());
            directoryAnalysisList.push_back(directoryAnalysis);
        }
        else
        {
            for (auto& it : positiveRes.results) {
                FileAnalysis* fileAnalysis = new FileAnalysis(it.first, it.second, "Positive");
                fileAnalysisList.push_back(fileAnalysis);
            }
            for (auto& it : negativeRes.results) {
                FileAnalysis* fileAnalysis = new FileAnalysis(it.first, it.second, "Negative");
                fileAnalysisList.push_back(fileAnalysis);
            }
            for (auto& it : stopRes.results) {
                FileAnalysis* fileAnalysis = new FileAnalysis(it.first, it.second, "Stop");
                fileAnalysisList.push_back(fileAnalysis);
            }
        }

        TextAnalysis* textAnalysis = new TextAnalysis(fileDetails[i].fileName,
            fileDetails[i].wordCount,
            positiveRes.results.size(),
            negativeRes.results.size(),
            stopRes.results.size(),
            positiveRes.results.size() - negativeRes.results.size(),
            (positiveRes.executionTime + negativeRes.executionTime + stopRes.executionTime));

        textAnalysisList.push_back(textAnalysis);

    }

    auto totalTimeEnd = std::chrono::high_resolution_clock::now();
    updateMemoryUsage(memAfterPreprocessing);
    chrono::duration<double> totalTimeElapsed = totalTimeEnd - totalTimeStart;

    size_t memoryUsage = memAfterPreprocessing - memBeforePreprocessing;

    Result* result = new Result(files.size(), algorithmType, totalTimeElapsed.count(), this->elapsedPreprocess, memoryUsage, this->memoryUsagePreprocessing, textAnalysisList);

    if (directoryAnalysisList.size() > 0)
        FileService::generateDirectoryLevelAnalysis(directoryAnalysisList);
    else if (fileAnalysisList.size() > 0)
        FileService::generateFileLevelAnalysis(fileAnalysisList);

    FileService::generateResultFile(result);
}