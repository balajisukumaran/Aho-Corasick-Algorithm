#ifndef TEXT_ANALYSIS_H
#define TEXT_ANALYSIS_H

#include <string>
#include <vector>

using namespace std;

/// <summary>
/// Model class for text analysis
/// </summary>
class TextAnalysis {
public:
    string name;
    int totalWords;
    int positiveWords;
    int negativeWords;
    int stopWords;
    int polarity;
    double timeTaken;

    TextAnalysis(string name, int totalWords, int positiveWords, int negativeWords, int stopWords, int polarity, double timeTaken) {
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
    int totalFiles;
    string algorithm;
    double totalTimeTaken;
    vector<TextAnalysis*> analysis;

    Result(int totalFiles, string algorithm, double totalTimeTaken, vector<TextAnalysis*> analysis) {
        this->totalFiles = totalFiles;
        this->algorithm = algorithm;
        this->totalTimeTaken = totalTimeTaken;
        this->analysis = analysis;
    }
};
#endif