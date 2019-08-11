#include "predict.h"
#include <cmath>
// ./NBC classify --stats stats.logs --input validation.file --output output.file

std::tuple<size_t , size_t>  LoadData(std::ifstream &fin, std::unordered_map<std::string, TClass>& globalMap){
    size_t wordsNum, docsNum;
    fin >> docsNum >> wordsNum;

    std::string theme, tmp_line;
    size_t tmp_num;
    size_t lines;
    while(fin.peek() != EOF){
        fin >> theme;
        fin >> globalMap[theme].docsCount >> globalMap[theme].wordsCount;
        fin >> lines;
        for(size_t i = 0; i < lines; ++i){
            fin >> tmp_line >> tmp_num;
            globalMap[theme].wordsFreq[tmp_line] = tmp_num;
        }
    }
    std::cout << "Data is loaded!" << std::endl;
    return std::make_tuple(docsNum, wordsNum);
}

void Classify(std::ifstream &fin, std::ofstream &fout, const std::unordered_map<std::string, TClass>& globalMap, size_t docsNum , size_t wordsNum){

    std::string line;
    std::unordered_set<std::string> totalUniqueWords; // placeholder

    while(fin.peek() != EOF) {
        size_t numberOfLines = 0;
        std::unordered_map<std::string, size_t> documentMap;
        size_t wordsInDocument = 0;

        fin >> numberOfLines;
        fin.get();
        for(; numberOfLines > 0; --numberOfLines) {
            getline(fin, line);
            ProcessString(line, documentMap, wordsInDocument, totalUniqueWords, false);
        }

        std::map<double, std::string> logPreds; // mb vec of strings.
        double prediction = 0;
        double wic = 0;
        std::string wordName;
        for(auto& theme: globalMap){
            prediction = std::log(double(theme.second.docsCount) / docsNum);
            for(auto& word: documentMap){
                wordName = word.first;
                auto pos = theme.second.wordsFreq.find(wordName);
                pos == theme.second.wordsFreq.end() ? wic = 0 : wic = pos->second;
                prediction += word.second * std::log(double(wic + 1)/(wordsNum + theme.second.wordsCount));
            }
            logPreds[prediction] = theme.first;
        }

        // .975 CONFIDENCE OR FIVE MOST PROBABLE
        int i = 0;
        int maxTags = 5;
        double maxProb = 0;
        for(auto it = logPreds.rbegin(); i < maxTags; ++it, ++i){
            if(i == 0) maxProb = it->first;
            if(1.025*maxProb > it->first) break;
            else if(i != 0) fout << ", ";
            fout << it->second;
        }
        fout << std::endl;

    }

}