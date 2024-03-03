#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "DirectoryAnalysis.h"
#include "FileAnalysis.h"

using namespace std;

class FileService
{

public:
    static void generateDirectoryLevelAnalysis(vector<DirectoryAnalysis*> analysis);
    static void generateFileLevelAnalysis(vector<FileAnalysis*> analysis);
};

