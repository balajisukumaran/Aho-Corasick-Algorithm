#include "KnuthMorrisPratt.h"
#include "Helper.h"

/// <summary>
/// Preprocessing the patterns
/// </summary>
/// <param name="wordBag"></param>
void KnuthMorrisPratt::preProcessing(vector<string>& wordBag) {

    for (string& word : wordBag) {
        size_t wordLength = word.length();
        vector<int> lps(wordLength, 0);

        size_t len = 0;
        size_t i = 1;

        while (i < wordLength) {
            if (word[i] == word[len]) {
                len++;
                lps[i] = len;
                i++;
            }
            else {
                if (len != 0) {
                    len = lps[len - 1];
                }
                else {
                    lps[i] = len;
                    i++;
                }
            }
        }

        this->prefixTable[word] = lps;
    }
}

/// <summary>
/// Use KMP algorithm to search for patterns
/// </summary>
/// <param name="sentence">input sentence</param>
/// <returns>words and counts</returns>
map<string, int> KnuthMorrisPratt::searchIn(const string& sentence) {
    map<string, int> result;
    string paddedSentence = " " + sentence + " "; // Padding to handle word boundaries

    // Iterate over each pattern and search for it in the sentence
    for (auto& it : this->prefixTable) {
        const string& pattern = it.first;
        vector<int> prefixTable = it.second;

        size_t m = pattern.length();
        size_t n = paddedSentence.length();
        size_t i = 0; // index for paddedSentence[]
        size_t j = 0; // index for pattern[]

        // Start searching for the pattern in the sentence
        while (i < n) {
            // Match found, move to the next character in both pattern and text
            if (pattern[j] == paddedSentence[i]) {
                j++;
                i++;
            }

            // If whole pattern is found, reset j and increment count
            if (j == m) {
                // Check for word boundaries
                if (Helper::isWordBoundary(paddedSentence[i - j - 1]) && Helper::isWordBoundary(paddedSentence[i])) {
                    result[pattern]++;
                }
                j = prefixTable[j - 1]; // Get the length of the next prefix which is also suffix
            }
            else if (i < n && pattern[j] != paddedSentence[i]) {
                // Mismatch after j matches
                if (j != 0) {
                    j = prefixTable[j - 1];
                }
                else {
                    i = i + 1;
                }
            }
        }
    }

    return result;
}