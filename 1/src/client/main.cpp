#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <iterator>

#include "../lib/stringlib.hpp"

#define PROMPT_FILE "Enter filename: "
#define PROMPT_TERM "Enter search term: "
#define NO_MATCHES "No matches found"

int main() {
    try {
        for (auto i : std::views::iota(0)) {
            std::string filename = read_string_console(static_cast<std::string>(PROMPT_FILE));
            if (filename.empty()) {
                break;
            }

            std::string search_term = read_string_console(static_cast<std::string>(PROMPT_TERM));
            if (filename.empty()) {
                break;
            }

            auto results = search_in_file(static_cast<std::string>(filename), static_cast<std::string>(search_term));

            if (results.empty()) {
                std::cout << NO_MATCHES << std::endl;
            } else {
                std::cout << "Found " << results.size() << " matches:" << std::endl;
                std::ranges::for_each(results, [](const auto& result) {
                    std::cout << result << std::endl;
                });
            }

            std::vector<const char*> c_results = search_in_file(filename.c_str(), search_term.c_str());
            if (!c_results.empty()) {   
                std::cout << "C-style results (" << c_results.size() << "matches):" << std::endl;
                
                std::ranges::for_each(c_results.begin(), c_results.end(), [](const char* result) {
                    std::cout << result << std::endl;
                });
                
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