#pragma once

#include <cstddef>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// get_page_size returns the size of a page in bytes.
size_t get_page_size();

// get_memory_usage returns the amount of memory used by the process in bytes.
size_t get_memory_usage();

template <typename T>
std::vector<T> read_tsv_column(const std::string &filename, size_t column_number) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file: " + filename);
  }

  std::vector<T> result;
  std::string line;
  while (std::getline(file, line)) {
    std::stringstream stream(line);
    std::string cell;

    // todo: now taking only the first column as a value and T is
    // determined by the author itself by carefully looking at the file
    // content.
    (void)column_number;

    if (std::getline(stream, cell, '\t')) {
      std::istringstream value_stream(cell);
      T value;
      value_stream >> value;

      if (value_stream.fail()) {
        throw std::invalid_argument("Failed to convert value to type T.");
      }

      result.push_back(value);
    }
  }

  return result;
}
