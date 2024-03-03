#include "Helper.h"

using namespace std;
namespace fs = filesystem;

unordered_set<char> Helper::punctuation = { ' ', '.','?', '!',  ',', ';', ':', '-', ')', ']', '}', '\'','"' }; 

vector<string> Helper::split(const string& str, char delimiter) {

	vector<string> tokens;
	string token;
	istringstream tokenStream(str);

	while (getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}

void Helper::removeSpecialCharacters(string& str) {
	str.erase(remove_if(str.begin(), str.end(), [](unsigned char c) {
		return !isalnum(c);
		}), str.end());
}

vector<filesystem::path> Helper::getListofFiles(string& path) {
	vector<filesystem::path> result;

	try {
		if (fs::exists(path) && fs::is_directory(path)) {
			for (const auto& entry : fs::directory_iterator(path)) {
				if (!entry.is_directory()) {
					result.push_back(entry.path());
				}
			}
		}
        if (fs::exists(path) && fs::is_regular_file(path)) {
            result.push_back(path);
        }
	}
	catch (const fs::filesystem_error& e) {
		cerr << "Error: " << e.what() << endl;
	}
	return result;
}

string Helper::readFile(const filesystem::path& path)
{
	ifstream file_stream(path);
	if (!file_stream.is_open()) {
		throw runtime_error("Could not open file at " + path.string());
	}
	stringstream buffer;
	buffer << file_stream.rdbuf();
	return buffer.str();
}

vector<string> Helper::readWordsFromFile(const string& file_path) {
	vector<string> words;
	ifstream file(file_path);
	string word;

	if (!file.is_open()) {
		cerr << "Error opening file: " << file_path << endl;
		return words;
	}

	while (getline(file, word)) {
		if (!word.empty()) {
			words.push_back(word);
		}
	}

	file.close();
	return words;
}
