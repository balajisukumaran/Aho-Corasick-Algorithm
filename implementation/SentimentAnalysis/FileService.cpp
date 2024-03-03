#include "FileService.h"

using namespace std;

void FileService::generateDirectoryLevelAnalysis(vector<DirectoryAnalysis*> analysis)
{

    // Create an ofstream object for file writing
    ofstream outFile("C:\\Users\\balaj\\source\\repos\\Dataset\\Books\\Analysis\\table.txt");

    // Check if the file was opened successfully
    if (!outFile.is_open()) {
        cerr << "Could not open the file for writing." << endl;
    }

    // Set the width for each column
    const int fileNameWidth = 40;
    const int positiveCountWidth = 20;
    const int negativeCountWidth = 20;
    const int stopCountWidth = 20;
    const int polarityCountWidth = 20;
    const int timeTakenWidth = 10;

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

void FileService::generateFileLevelAnalysis(vector<FileAnalysis*> analysis)
{

    // Create an ofstream object for file writing
    ofstream outFile("C:\\Users\\balaj\\source\\repos\\Dataset\\Books\\Analysis\\file.txt");

    // Check if the file was opened successfully
    if (!outFile.is_open()) {
        cerr << "Could not open the file for writing." << endl;
    }
    string word;
    int occurency;
    string wordType;
    // Set the width for each column
    const int wordWidth = 35;
    const int occurencyWidth = 12;
    const int wordTypeWidth = 12;;

    // Print the header to the file
    outFile << left << setw(wordWidth) << "WORD"
        << setw(occurencyWidth) << "OCCURRENCES"
        << setw(wordTypeWidth) << "WORD TYPE" << endl;

    // Print the separator to the file
    outFile << setfill('-') << setw(wordWidth+occurencyWidth+wordTypeWidth) << "-" << endl;

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