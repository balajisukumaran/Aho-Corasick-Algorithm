#ifndef TEXT_ANALYSIS_H
#define TEXT_ANALYSIS_H

#include <string>
#include <vector>
#include <intsafe.h>

/// <summary>
/// Model class for text analysis
/// </summary>
class TextAnalysis {
public:
    std::string name;
    size_t totalWords;
    size_t positiveWords;
    size_t negativeWords;
    size_t stopWords;
    size_t polarity;
    double timeTaken;

    TextAnalysis(std::string name, size_t totalWords, size_t positiveWords, size_t negativeWords, size_t stopWords, size_t polarity, double timeTaken) {
        this->name = name;
        this->totalWords = totalWords;
        this->positiveWords = positiveWords;
        this->negativeWords = negativeWords;
        this->stopWords = stopWords;
        this->polarity = polarity;
        this->timeTaken = timeTaken;
    }
};
#endif 


#ifndef RESULT_H
#define RESULT_H

/// <summary>
/// Model class for complete analysis result
/// </summary>
class Result {
public:
    size_t totalFiles;
    std::string algorithm;
    double totalTimeTaken;
    double preProcessTimeTaken;
    std::vector<TextAnalysis*> analysis;
    size_t memoryUsagePreprocess;
    size_t memoryUsage;

    Result(size_t totalFiles, std::string algorithm, double totalTimeTaken, double preProcessTimeTaken, size_t memoryUsage, size_t memoryUsagePreprocess, std::vector<TextAnalysis*> analysis) {
        this->totalFiles = totalFiles;
        this->algorithm = algorithm;
        this->totalTimeTaken = totalTimeTaken;
        this->preProcessTimeTaken = preProcessTimeTaken;
        this->memoryUsage = memoryUsage;
        this->memoryUsagePreprocess = memoryUsagePreprocess;
        this->analysis = analysis;
    }
};
#endif