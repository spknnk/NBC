#ifndef NBC_PREDICT_H
#define NBC_PREDICT_H

#include "base.h"

std::tuple<size_t , size_t>  LoadData(std::ifstream &fin, std::unordered_map<std::string, TClass>& globalMap);

void Classify(std::ifstream &fin, std::ofstream &fout, const std::unordered_map<std::string, TClass>& globalMap, size_t docsNum , size_t wordsNum);
#endif //NBC_PREDICT_H
