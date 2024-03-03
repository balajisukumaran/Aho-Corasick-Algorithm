#pragma once
#include <string>

using namespace std;

class DirectoryAnalysis {
public:
    string fileName;
    int positiveCount;
    int negativeCount;
    int stopCount;
    int polarity;
    string timeTaken;

    DirectoryAnalysis(const string& fileName, int positiveCount, int negativeCount, int stopCount, int polarity, const string& timeTaken)
        : fileName(fileName), positiveCount(positiveCount), negativeCount(negativeCount), stopCount(stopCount), polarity(polarity), timeTaken(timeTaken)
    {
    }
};