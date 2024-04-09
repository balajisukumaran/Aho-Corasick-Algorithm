#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
    
    std::string file_path = "stopwords.txt";
    std::unordered_set<std::string> unique_words;
    std::ifstream input_file(file_path);
    std::string word;

    if (!input_file.is_open()) {
        std::cerr << "Failed to open the file for reading." << std::endl;
        return 1;
    }

    while (input_file >> word) {
        unique_words.insert(word);
    }
    input_file.close();

    std::ofstream output_file(file_path, std::ios::trunc); 
    
    if (!output_file.is_open()) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return 1;
    }

    for (const auto& unique_word : unique_words) {
        output_file << unique_word << std::endl;
    }
    output_file.close();

    std::cout << "Duplicates removed and unique words stored back to the file." << std::endl;

    return 0;
}
