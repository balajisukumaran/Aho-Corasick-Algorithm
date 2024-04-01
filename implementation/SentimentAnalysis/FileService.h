#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "DirectoryAnalysis.h"
#include "FileAnalysis.h"
#include "Analysis.cpp"
#include <nlohmann/json.hpp>
#include <algorithm>
#include <cctype>

using namespace std;
using json = nlohmann::json;

/// <summary>
/// Contains methods to create the analysis result files
/// </summary>
class FileService
{

public:

    /// <summary>
    /// Used when there are more than 1 files in the directory
    /// </summary>
    /// <param name="analysis"></param>
    static void generateDirectoryLevelAnalysis(vector<DirectoryAnalysis*> analysis);

    /// <summary>
    /// used when there is only 1 file in the directory
    /// </summary>
    /// <param name="analysis"></param>
    static void generateFileLevelAnalysis(vector<FileAnalysis*> analysis);

    /// <summary>
    /// Generate the input files for the notebook
    /// </summary>
    /// <param name="result"></param>
    static void generateResultFile(Result* result);

    // Function to convert an Analysis object to a JSON object
    static json analysisToJson(TextAnalysis* textAnalysis) {
        return json{
            {"name", removeSpecialCharacters(textAnalysis->name)},
            {"totalWords", textAnalysis->totalWords},
            {"positiveWords", textAnalysis->positiveWords},
            {"negativeWords", textAnalysis->negativeWords},
            {"stopWords", textAnalysis->stopWords},
            {"polarity", textAnalysis->polarity},
            {"TimeTaken", textAnalysis->timeTaken}
        };
    }

    /// <summary>
    /// Function to convert a Model object to a JSON object
    /// </summary>
    /// <param name="model">result data</param>
    /// <returns>json</returns>
    static json modelToJson(const Result& model) {
        json jAnalysisArray = json::array();
        for (auto analysis : model.analysis) {
            jAnalysisArray.push_back(analysisToJson(analysis));
        }

        return json{
            {"totalFiles", model.totalFiles},
            {"Algorithm", removeSpecialCharacters(model.algorithm)},
            {"Total Time Taken", model.totalTimeTaken},
            {"analysis", jAnalysisArray}
        };
    }

    static string removeSpecialCharacters(const std::string& input) {
        std::string result = input;
        result.erase(
            std::remove_if(
                result.begin(),
                result.end(),
                [](unsigned char c) { return !std::isalnum(c); }
            ),
            result.end()
        );
        return result;
    }


    /// <summary>
    /// Function to write a list of Model objects to a JSON file
    /// </summary>
    /// <param name="model">result</param>
    /// <param name="filename">file to create</param>
    static void writeModelToJsonFile(const Result* model, const string& filename) {
        json jModel = modelToJson(*model);

        // Write the JSON array to a file
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << jModel.dump(4); // The '4' argument pretty-prints the JSON
            outFile.close();
        }
    }

    /// <summary>
    /// Function to write a list of Model objects to a JSON file
    /// </summary>
    /// <param name="models"></param>
    /// <param name="filename"></param>
    static void writeModelsToJsonFile(const vector<Result>& models, const string& filename) {
        json jModelsArray = json::array();

        // Convert each Model object to JSON and add it to the array
        for (const auto& model : models) {
            jModelsArray.push_back(modelToJson(model));
        }

        // Write the JSON array to a file
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << jModelsArray.dump(4); // The '4' argument pretty-prints the JSON
            outFile.close();
        }
    }
};

