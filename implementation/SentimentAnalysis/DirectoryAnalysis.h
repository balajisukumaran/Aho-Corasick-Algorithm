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
    int positiveCount;

    /// <summary>
    /// number of negative words
    /// </summary>
    int negativeCount;

    /// <summary>
    /// number of stop words
    /// </summary>
    int stopCount;

    /// <summary>
    /// polarity of the file
    /// </summary>
    int polarity;

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
    DirectoryAnalysis(const string& fileName, int positiveCount, int negativeCount, int stopCount, int polarity, const string& timeTaken)
        : fileName(fileName), positiveCount(positiveCount), negativeCount(negativeCount), stopCount(stopCount), polarity(polarity), timeTaken(timeTaken)
    {
    }
};