# Multi-Pattern Search Algorithm for Sentiment Analysis

## Overview

This project is designed to search for patterns of positive, negative, and stop words within a large dataset utilizing a multi-pattern search algorithm. Users have the option to utilize the Aho-Corasick, Trie Search, or KMP Algorithm for pattern searching. Configuration of the algorithm and execution settings can be done via the `config.ini` file.

## Configuration and Execution

### Step 1: Navigate to the Release Directory

Begin by navigating to the executable's directory: implementation/SentimentAnalysis/x64/Release

### Step 2: Configure the Application

Modify the `config.ini` file with the desired settings. Sample input and word lists are provided in the `run/books` and `run/words` directories, respectively. Update the configuration as shown below:

```ini
[algorithm]
type = 2 // 1: Aho-Corasick, 2: Trie Search, 3: KMP Algorithm
parellel = 1 // 1: Parallel, 2: Sequential

[file]
input_path = C:\Users\balaj\source\repos\Dataset\Books\20000  // Dataset path
output_path = C:\Users\balaj\source\repos\Dataset\Books\Analysis\20000\ // Results path
positive_words_file = C:\Users\balaj\source\repos\Aho-Corasick-Algorithm\implementation\SentimentAnalysis\words\positive-words.txt // Positive words list
negative_words_file = C:\Users\balaj\source\repos\Aho-Corasick-Algorithm\implementation\SentimentAnalysis\words\negative-words.txt // Negative words list
stop_words_file = C:\Users\balaj\source\repos\Aho-Corasick-Algorithm\implementation\SentimentAnalysis\words\stop-words.txt  // Stop words list
```

Ensure that the paths and files specified in the config.ini file exist before proceeding.

### Step 3: Run the Analysis

Execute SentimentAnalysis.exe to start the analysis. The program will generate table*\*.txt files containing the sentiment analysis results and result*\*.txt files showing the performance metrics of the selected algorithm.
