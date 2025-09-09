#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <cstring>
#include <ranges>
#include <iterator>

#include "stringlib.hpp"

char* read_string_console(const char* prompt) {
    std::cout << prompt;
    std::cout.flush();

    std::string input;
    if (!std::getline(std::cin, input)) {
        throw std::runtime_error("Failed to read input");
    }

    char* result = new char[input.size() + 1];
    std::strcpy(result, input.c_str());

    return result;
}

std::string read_string_console(const std::string& prompt) {
    std::cout << prompt;
    std::cout.flush();

    std::string input;
    if (!std::getline(std::cin, input)) {
        throw std::runtime_error("Failed to read input");
    }

    return input;
}

namespace {
    std::string to_lower(const std::string& s) {
        std::string result;
        std::ranges::transform(s, std::back_inserter(result), [](unsigned char c) { 
            return std::tolower(c); 
        });

        return result;
    }
}

std::vector<std::string> search_in_file(const std::string& filename, const std::string& search_term) {
    if (!std::filesystem::exists(filename)) {
        throw std::runtime_error("File does not exist: " + filename);
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::vector<std::string> results;
    std::string line;
    auto line_number = 0;
    std::string lower_search_term = to_lower(search_term);

    while (std::getline(file, line)) {
        line_number++;
        std::string lower_line = to_lower(line);
        
        if (lower_line.find(lower_search_term) != std::string::npos) {
            results.push_back(std::to_string(line_number) + ": " + line);
        }
    }

    return results;
}

std::vector<const char*> search_in_file(const char* filename, const char* search_term) {
    if (filename == nullptr) {
        throw std::logic_error("File is nullptr");
    }

    std::vector<std::string> string_results = search_in_file(std::string(filename), std::string(search_term));
    std::vector<const char*> results;
    
    std::transform(string_results.begin(), string_results.end(), std::back_inserter(results),
                  [](const std::string& str) {
                      char* c_str = new char[str.size() + 1];
                      std::strcpy(c_str, str.c_str());
                      return c_str;
                  });
    
    return results;
}

void free_search_results(std::vector<const char*>& results) {
    std::for_each(results.begin(), results.end(), [](const char* str) { delete[] str; });
    results.clear();
}