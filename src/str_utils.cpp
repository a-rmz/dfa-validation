
#include <regex>
#include "str_utils.h"

template<typename Out>

void split(const std::string &s, char delim, Out result) {
    std::string trimmed = std::regex_replace(s, std::regex(" +"), "$1");
    std::stringstream ss;
    ss.str(trimmed);
    std::string item;
    while (std::getline(ss, item, delim)) {
      if (!item.empty()) {
        *(result++) = item;
      }
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}