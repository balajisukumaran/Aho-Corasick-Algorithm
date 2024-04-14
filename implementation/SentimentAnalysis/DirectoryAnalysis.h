#pragma once
#include <string>

using namespace std;

/// <summary>
/// Model class for Directory Analysis data
/// </summary>
class DirectoryAnalysis {
public:

    /// <summary>
    /// File name
    /// </summary>
    string fileName;

    /// <summary>
    /// number of positive words
    /// </summary>
    size_t positiveCount;

    /// <summary>
    /// number of negative words
    /// </summary>
    size_t negativeCount;

    /// <summary>
    /// number of stop words
    /// </summary>
    size_t stopCount;

    /// <summary>
    /// polarity of the file
    /// </summary>
    size_t polarity;

    /// <summary>
    /// time taken in seconds
    /// </summary>
    string timeTaken;

    /// <summary>
    /// Constructor for Directory Analysis
    /// </summary>
    /// <param name="fileName">file name</param>
    /// <param name="positiveCount">positive count</param>
    /// <param name="negativeCount">negative count</param>
    /// <param name="stopCount">stop count</param>
    /// <param name="polarity">polarity of a file</param>
    /// <param name="timeTaken">time taken to calculate</param>
    DirectoryAnalysis(const string& fileName, size_t positiveCount, size_t negativeCount, size_t stopCount, size_t polarity, const string& timeTaken)
        : fileName(fileName), positiveCount(positiveCount), negativeCount(negativeCount), stopCount(stopCount), polarity(polarity), timeTaken(timeTaken)
    {
    }
};