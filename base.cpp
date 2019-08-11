#include "base.h"

void ProcessString(std::string &line, std::unordered_map<std::string, size_t> &sampleFreq, size_t &wordCount, std::unordered_set<std::string> &totalUniqueWords, bool toGlobal) {
    std::string processedWord;
    //std::set<std::string> stopWords = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until", "while", "of", "at", "by", "for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above", "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here", "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more", "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s", "t", "can", "will", "just", "don", "should", "now"};
    std::set<std::string> stopWords = {};
    for(char& ch: line) {
        if (isalpha(ch) && (ch != ' ')) {
            processedWord += static_cast<char>(tolower(ch));
        } else {
            if (!processedWord.empty() && !Contains(processedWord, stopWords)) {
                sampleFreq[processedWord] += 1;
                wordCount += 1;
                if(toGlobal){
                    if(!Contains(processedWord, totalUniqueWords)){
                        totalUniqueWords.insert(processedWord);
                    }
                }
            }
            processedWord.clear();
        }
    }
}
