#include <iostream>
#include "fit.h"
#include "predict.h"
#include <time.h>

void GetFileNames(int argc, const char **argv, std::string &inputFile,
                  std::string &statsFile,
                  std::string &outputFile){

    for(int i = 2; i < argc-1; ++i){
        if(!strcmp(argv[i], "--input"))
            inputFile = argv[i+1];
        if(!strcmp(argv[i], "--stats"))
            statsFile = argv[i+1];
        if(!strcmp(argv[i], "--output"))
            outputFile = argv[i+1];
    }

}



int main(int argc, char const *argv[]) {
    std::string inputFile;
    std::string statsFile;
    std::string outputFile;

    GetFileNames(argc, argv, inputFile, statsFile, outputFile);

//    for(int i = 0; i < argc; i++){
//        std::cout << i << " " << argv[i] << std::endl;
//    }

    std::unordered_map<std::string, TClass> globalMap;
    size_t docsNum, wordsNum;

    clock_t tStart = clock();

    if(!strcmp(argv[1], "learn")) {
        std::ifstream fin(inputFile);
        std::tie(docsNum, wordsNum) = ProcessDocs(fin, globalMap);
        std::ofstream fout(outputFile);
        Serialize(fout, globalMap, docsNum, wordsNum);
    }

    if(!strcmp(argv[1], "classify")) {
        std::ifstream stats(statsFile);
        std::tie(docsNum, wordsNum) = LoadData(stats, globalMap);
        std::ifstream fin(inputFile);
        std::ofstream fout(outputFile);
        Classify(fin, fout, globalMap, docsNum, wordsNum);
    }

    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    return 0;
}