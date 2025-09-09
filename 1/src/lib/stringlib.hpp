#ifndef STRINGLIB_HPP
#define STRINGLIB_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <memory>

// Для C-строк
char* read_string_console(const char* prompt);
std::vector<const char*> search_in_file(const char* filename, const char* search_term);

// Для std::string
std::string read_string_console(const std::string& prompt);
std::vector<std::string> search_in_file(const std::string& filename, const std::string& search_term);

void free_search_results(std::vector<const char*>& results);

#endif