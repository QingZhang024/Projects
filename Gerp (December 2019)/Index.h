/* Index.h
 *
 * Qing Zhang
 * Comp 15
 * Proj2: Gerp
 */

#ifndef INDEX_H
#define INDEX_H

#include <stack>
#include <vector>
#include <fstream>
#include "FSTree.h"
#include "DirNode.h"

class Index {

public:
    Index();
    Index(std::string root);

    void Gerp(std::string word, std::ostream &output);
    void GerpInsensitive(std::string word, std::ostream &output);
    
private:
    FSTree theTree;

    struct Lines{
        std::string line;
        std::string filePath;
        int lineNum;
    };
   
    struct subWords{
        std::string word;
        std::vector<int> lineIndexNums;
    };

    struct Words{
        std::string word;
        std::vector<subWords> subwords;
    };

    struct Files{
        DirNode *file;
        std::string path;
    };

    std::vector<Lines> lineIndex;
     
    std::vector<Words> wordIndex;

    int wordIndexSize;
    int currentWordNum;

    std::string getPath();

    void indexLines(DirNode *root);
    void fileStack(DirNode *root, std::stack<Files> &allFiles, std::string path);
    void readFiles(std::string path);
    
    void lineToWords();
    bool is_repeated(std::vector<std::string> &repeats, std::string word);

    void indexWords(std::string line, int lIndex);
    size_t hashingWords(std::vector<Words>&Index, std::string word);
    std::string convertLower(std::string word);
    void checkExpand();


};

#endif
