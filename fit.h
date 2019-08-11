//
// Created by spknnk on 09.05.19.
//

#ifndef NBC_FIT_H
#define NBC_FIT_H

#include "base.h"

std::tuple<size_t , size_t>  ProcessDocs(std::ifstream &fin, std::unordered_map<std::string, TClass>& globalMap);

void Serialize(std::ofstream &fout, const std::unordered_map<std::string, TClass>& globalMap, size_t docsNum, size_t wordsNum);

std::vector<std::string> ClassesToVec(std::string& line);

#endif //NBC_FIT_H