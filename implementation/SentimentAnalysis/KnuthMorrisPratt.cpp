#include "KnuthMorrisPratt.h"
#include "Helper.h"

void KnuthMorrisPratt::preProcessing(vector<string>& wordBag) {
	
	for (string& word : wordBag) {
		int wordLength = word.length();
		vector<int> lps(wordLength, 0);

		int len = 0;
		int i = 1;

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

unordered_map<string, int> KnuthMorrisPratt::searchIn(string& sentence) {
	//int result = 0;
	unordered_map<string, int> result;

	for (auto& it : this->prefixTable) {
		const string& pattern = it.first;
		vector<int> prefixTable = it.second;

			Helper::removeSpecialCharacters(sentence);
			
			int i = 0;
			int n = sentence.length();
			int m = pattern.length();
			int j = 0;

			while ((n - i) >= (m - j)) {

				if (pattern[j] == sentence[i]) {
					j++;
					i++;
				}

				if (j == m) {
					//result++; //word found move to next word in the patterns
					break;
				}

				else if (i < n && pattern[j] != sentence[i]) {
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