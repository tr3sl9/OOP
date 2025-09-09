#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "../lib/stringlib.hpp"

int main() {
    try {
        while (true) {
            std::string filename = read_string_console((std::string)"Enter filename: ");
            if (filename.empty()) break;

            std::string search_term = read_string_console((std::string)"Enter search term: ");
            if (search_term.empty()) break;
            
            auto results = search_in_file(filename, search_term);
            
            if (results.empty()) {
                std::cout << "No matches found." << std::endl;
            } else {
                std::cout << "Found " << results.size() << " matches:" << std::endl;
                for (const auto& result : results) {
                    std::cout << result << std::endl;
                }
            }
            
            std::vector<const char*> c_results = search_in_file(filename.c_str(), search_term.c_str());
            if (!c_results.empty()) {
                std::cout << "C-style results (" << c_results.size() << " matches):" << std::endl;
                for (const char* result : c_results) {
                    std::cout << result << std::endl;
                }
                free_search_results(c_results);
            }
            
            std::cout << "Continue? (y/n): ";
            std::string response;
            if (!std::getline(std::cin, response) || response != "y") {
                break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}