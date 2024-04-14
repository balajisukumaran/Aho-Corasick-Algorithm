#include "FileService.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include "Analysis.cpp"
#include <chrono>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ini_parser.hpp"

using namespace boost::property_tree;
using namespace std;
using json = nlohmann::json;

/// <summary>
/// get the current time
/// </summary>
/// <returns></returns>
string getCurrentTime() {
    // Get current time as time_point
    auto now = chrono::system_clock::now();

    // Convert to time_t for conversion to tm (time structure)
    auto now_c = chrono::system_clock::to_time_t(now);

    // Convert to tm structure for local timezone
    tm now_tm;
    localtime_s(&now_tm, &now_c); // Use localtime_s instead of localtime

    // Output as string stream
    stringstream ss;
    ss << put_time(&now_tm, "%Y-%m-%d_%H%M");

    return ss.str();
}

/// <summary>
/// Used when there are more than 1 files in the directory
/// </summary>
/// <param name="analysis"></param>
void FileService::generateDirectoryLevelAnalysis(vector<DirectoryAnalysis*> analysis)
{
    ptree pt;
    string outputPath;

    ini_parser::read_ini("config.ini", pt);
    outputPath = pt.get<string>("file.output_path");

    // Create an ofstream object for file writing
    ofstream outFile(outputPath + "table_" + getCurrentTime() + ".txt");

    // Check if the file was opened successfully
    if (!outFile.is_open()) {
        cerr << "Could not open the file for writing." << endl;
    }

    // Set the width for each column
    const size_t fileNameWidth = 40;
    const size_t positiveCountWidth = 20;
    const size_t negativeCountWidth = 20;
    const size_t stopCountWidth = 20;
    const size_t polarityCountWidth = 20;
    const size_t timeTakenWidth = 10;

    // Print the header to the file
    outFile << left << setw(fileNameWidth) << "FILE NAME"
        << setw(positiveCountWidth) << "POSITIVE WORDS"
        << setw(negativeCountWidth) << "NEGATIVE WORDS"
        << setw(stopCountWidth) << "STOP WORDS"
        << setw(polarityCountWidth) << "POLARITY"
        << setw(timeTakenWidth) << "TIME TAKEN" << endl;

    // Print the separator to the file
    outFile << setfill('-') << setw(fileNameWidth + positiveCountWidth + negativeCountWidth + stopCountWidth + polarityCountWidth + timeTakenWidth) << "-" << endl;

    // Reset fill character for the data
    outFile << setfill(' ');

    // Print the data to the file
    for (const auto& obj : analysis) {
        outFile << left << setw(fileNameWidth) << obj->fileName
            << setw(positiveCountWidth) << obj->positiveCount
            << setw(negativeCountWidth) << obj->negativeCount
            << setw(stopCountWidth) << obj->stopCount
            << setw(polarityCountWidth) << obj->polarity
            << setw(timeTakenWidth) << obj->timeTaken << endl;
    }

    // Close the file
    outFile.close();
}

/// <summary>
/// used when there is only 1 file in the directory
/// </summary>
/// <param name="analysis"></param>
void FileService::generateFileLevelAnalysis(vector<FileAnalysis*> analysis)
{
    ptree pt;
    string outputPath;

    ini_parser::read_ini("config.ini", pt);
    outputPath = pt.get<string>("file.output_path");

    // Create an ofstream object for file writing
    ofstream outFile(outputPath + "file_" + getCurrentTime() + ".txt");

    // Check if the file was opened successfully
    if (!outFile.is_open()) {
        cerr << "Could not open the file for writing." << endl;
    }
    string word;
    size_t occurency;
    string wordType;
    // Set the width for each column
    const size_t wordWidth = 35;
    const size_t occurencyWidth = 12;
    const size_t wordTypeWidth = 12;;

    // Print the header to the file
    outFile << left << setw(wordWidth) << "WORD"
        << setw(occurencyWidth) << "OCCURRENCES"
        << setw(wordTypeWidth) << "WORD TYPE" << endl;

    // Print the separator to the file
    outFile << setfill('-') << setw(wordWidth + occurencyWidth + wordTypeWidth) << "-" << endl;

    // Reset fill character for the data
    outFile << setfill(' ');

    // Print the data to the file
    for (const auto& obj : analysis) {
        outFile << left << setw(wordWidth) << obj->word
            << setw(occurencyWidth) << obj->occurency
            << setw(wordTypeWidth) << obj->wordType << endl;
    }

    // Close the file
    outFile.close();
}

/// <summary>
/// Generate the input files for the notebook
/// </summary>
/// <param name="result"></param>
void FileService::generateResultFile(Result* result)
{
    ptree pt;
    string outputPath;

    ini_parser::read_ini("config.ini", pt);
    outputPath = pt.get<string>("file.output_path");
    writeModelToJsonFile(result, outputPath + "result_" + getCurrentTime() + ".json");
}