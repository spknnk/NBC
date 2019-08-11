#include "fit.h"
// ./NBC learn --input sample.txt --output stats.logs

std::tuple<size_t , size_t>  ProcessDocs(std::ifstream &fin, std::unordered_map<std::string, TClass>& globalMap){

    std::string line;
    size_t totalUniqueDocs = 0;

    std::unordered_set<std::string> totalUniqueWords;

    size_t ALLNUMBEROFLINES = 0; // DEL
    size_t  IT = 1;

    while(fin.peek() != EOF) {
        totalUniqueDocs += 1;
        size_t numberOfLines = 0;
        std::unordered_map<std::string, size_t> sampleFreq;
        size_t wordsInDocument = 0;

        fin >> numberOfLines;
        fin.get();

        ALLNUMBEROFLINES += numberOfLines;
        if(ALLNUMBEROFLINES >= 1000000){
            std::cout << IT << "M" << std::endl;
            IT++;
            ALLNUMBEROFLINES = ALLNUMBEROFLINES % 1000000;
        }

        for(; numberOfLines > 0; --numberOfLines) {
            getline(fin, line);
            ProcessString(line, sampleFreq, wordsInDocument, totalUniqueWords, true);
        }

        getline(fin, line);
        std::vector<std::string> classesVec = ClassesToVec(line);
        for(auto& theme: classesVec){
            globalMap[theme].wordsCount += wordsInDocument;
            globalMap[theme].docsCount += 1;
            for(auto& iter : sampleFreq){
                globalMap[theme].wordsFreq[iter.first] += iter.second;
            }
        }
    }
    std::cout << "Docs: " << totalUniqueDocs << " Themes: " << globalMap.size() << " Total words: " << totalUniqueWords.size() << std::endl;
    return std::make_tuple(totalUniqueDocs, totalUniqueWords.size());
}

std::vector<std::string> ClassesToVec(std::string& line) {
    std::string tmp;
    std::vector<std::string> vec;
    for(char& ch: line){
        if(ch != ',')
            tmp += ch;
        else {
            vec.push_back(tmp);
            tmp.clear();
        }
    }
    if(!tmp.empty()) vec.push_back(tmp);
    return vec;
}

void Serialize(std::ofstream &fout, const std::unordered_map<std::string, TClass>& globalMap, size_t docsNum, size_t wordsNum){
    fout << docsNum << " " << wordsNum << std::endl;
    for(auto const& theme: globalMap){
        fout << theme.first << std::endl;
        fout << theme.second.docsCount << " " << theme.second.wordsCount << std::endl;
        fout << theme.second.wordsFreq.size() << std::endl;
        for(auto& word: theme.second.wordsFreq){
            fout << word.first << " " << word.second << std::endl;
        }
    }
}
