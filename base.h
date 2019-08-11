#ifndef NBC_BASE_H
#define NBC_BASE_H

#include <unordered_map>
#include <map>
#include "math.h"
#include <unordered_set>
#include <string>
#include "string.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <set>

struct TClass{
    size_t docsCount;
    size_t wordsCount; // total words in class
    std::unordered_map <std::string, size_t> wordsFreq;
};

template<class T, class C> bool Contains(const T& elem, const C& container){
    return container.find(elem) != container.end();
}

void ProcessString(std::string &line, std::unordered_map<std::string, size_t> &sampleFreq, size_t &wordCount, std::unordered_set<std::string> &totalUniqueWords, bool toGlobal);

#endif //NBC_BASE_H


