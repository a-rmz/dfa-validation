
#include "str_utils.h"
#include <regex>

/**
  * The code for this utility function was taken from here http://stackoverflow.com/a/236803,
  * with some modifications to avoid having empty tokens and trimming the extra spaces
  */

template<typename Out>

/**
  * Split a string given a delimiter and add it to a container
  */
void split(const std::string &s, char delim, Out result) {
    // Trim extra spaces
    std::string trimmed = std::regex_replace(s, std::regex(" +"), "$1");
    // Transform the string to a stream
    std::stringstream ss;
    ss.str(trimmed);
    // Temporary string
    std::string item;
    // Iterate as long as there are tokens
    while (std::getline(ss, item, delim)) {
      // Check that the token is not empty
      if (!item.empty()) {
        // Add the item to the collection
        *(result++) = item;
      }
    }
}

/**
  * Split a word with a delimiter and return the vector containing the tokens
  */
std::vector<std::string> split(const std::string &s, char delim) {
    // Temporary container
    std::vector<std::string> elems;
    // Split the string and save the tokens to elems
    split(s, delim, std::back_inserter(elems));
    // Return the resulting vector
    return elems;
}