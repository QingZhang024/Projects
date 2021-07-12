/* Index.cpp
 *
 * Qing Zhang
 * Comp 15
 * Proj 2: Gerp
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include "Index.h"
#include "stringProcessing.h"

using namespace std;


/* Default Constructor
 * Parameter: None
 * Returns: None
 * Description: Creates empty FSTree.
 */
Index::Index()
{
    theTree = FSTree();
}

/* Parameterized Constructor
 * Parameter: None
 * Returns: None
 * Description: Creates FSTree based on given filepath. Index the words in all
 *              subdirectory and files. .
 */
Index::Index(string root)
{
    theTree = FSTree(root);
    indexLines(theTree.getRoot());
    Words temp;
    temp.word = "EMPTY";
    wordIndexSize = 52027;
    currentWordNum = 0;
    vector<Words> vect(wordIndexSize, temp); 
    wordIndex = vect;
    lineToWords();
}

/* Function: indexLines
 * Parameters: DirNode *root
 * Returns: None
 * Description: Puts all files on the files stack, and parse everyline in every
 *              file into a vector of lines. 
 */
void Index::indexLines(DirNode *root)
{
    stack<Files> allFiles;
    fileStack(root, allFiles, "");
    while (!allFiles.empty()){
        Files temp = allFiles.top();
        if (temp.file -> hasFiles()){
            int Fnum = temp.file -> numFiles();
            for (int i = 0; i < Fnum; i++){
                string path = temp.path; 
                path += temp.file -> getFile(i);
                readFiles(path);
            }
        }
        allFiles.pop();
    }
}

/* Function: fileStack
 * Parameters: DirNode *root, stack<Files> &allFiles, string path
 * Returns: None
 * Description: Recursively store all files in a file stack. 
 */
void Index::fileStack(DirNode *root, stack<Files> &allFiles, string path)
{
    if (! root -> isEmpty()){
        Files temp;
        temp.file = root;
        temp.path = path + root -> getName() + "/";
        allFiles.push(temp); 
    }      
    if (root -> hasSubDir()){
        int sd = root -> numSubDirs();
        for (int i = 0; i < sd; i++){
            string Path = path + root -> getName() + "/";
            fileStack(root -> getSubDir(i), allFiles, Path);
        }
    }  
}

/* Function: readFiles
 * Parameters: string path
 * Returns: None
 * Description: Takes a filepath, open the file, and store everyline in
 *              lineIndex vector. 
 */
void Index::readFiles(string path)
{
    ifstream infile;
    infile.open(path);
    if (!infile){
        cerr << "Error: could not open file " << path << "\n";
        return;
    }
    string line;
    int num = 0;
    getline(infile, line);
    while(!infile.eof()){
        num++;
        Lines temp;
        temp.line = line;
        temp.filePath = path;
        temp.lineNum = num;
        lineIndex.push_back(temp);
        getline(infile, line);
    }
}

/* Function: lineToWords
 * Parameters: None
 * Returns: None
 * Description: Go through the whole lineIndex and for each line, index words. 
 */
void Index::lineToWords()
{
    int size = lineIndex.size();
    for (int i = 0; i < size; i++){
        indexWords(lineIndex[i].line, i);
    }
}

/* Function: indexWords
 * Parameters: string line, int lIndex
 * Returns: None
 * Description: Gets a line, and index every words in the line. Check if the 
 *              word has appeared in the same line before by storing all 
 *              indexed words in a vector. 
 */
void Index::indexWords(string line, int lIndex)
{
    vector<string> repeats;
    stringstream ss;
    ss.str(line);
    string word;
    while (ss >> word){
        word = stripNonAlphaNum(word);
        if (! is_repeated(repeats, word)){
            repeats.push_back(word);
            string root = convertLower(word);
            int slot = hashingWords(wordIndex, root);
            int subsize = wordIndex[slot].subwords.size();
            bool found = false;
            for (int i = 0; i < subsize; i++){
                if (wordIndex[slot].subwords[i].word == word){
                    wordIndex[slot].subwords[i].lineIndexNums.push_back(lIndex);
                found = true;
                break;
                }
            }
            if (found == false){
                subWords temp;
                temp.word = word;
                temp.lineIndexNums.push_back(lIndex);
                wordIndex[slot].subwords.push_back(temp);
            }
            checkExpand();
        }
    }
}

/* Function: is_repeated
 * Parameters: vector<string> &repeats, string word
 * Returns: bool
 * Description: Checks whether the word has appeared in the vector before. 
 */
bool Index::is_repeated(vector<string> &repeats, string word)
{
    int size = repeats.size();
    for (int i = 0; i < size; i++){
        if (word == repeats[i])
            return true;
    }
    return false;

}

/* Function: hashingWords
 * Parameters: vector<Words>&Index, string word
 * Returns: size_t
 * Description: Hash function that hash each word in its all lower-case form. 
 *              Calculates its location using linear probing.
 */
size_t Index::hashingWords(vector<Words>&Index, string word)
{
    hash<string> hash_function;
    size_t temp = hash_function(word);
    temp = temp % wordIndexSize;
    Words tempWord;
    tempWord.word = word;
    if (Index[temp].word == "EMPTY"){
        Index[temp] = tempWord;
        currentWordNum++;
        return temp;
    } else if (Index[temp].word == word){
        return temp;
    } else {
        for (size_t i = temp; i < size_t(wordIndexSize); i++){
            if (Index[i].word == word){
                return i;
            } else if (Index[i].word == "EMPTY"){
                Index[i] = tempWord;
                currentWordNum++;
                return i;
            }
        }
        for (size_t j = 0; j < temp; j++){
            if (Index[j].word == word){
                return j;
            } else if (Index[j].word == "EMPTY"){
                Index[j] = tempWord;
                currentWordNum++;
                return j;
            }
        }
    }
    return 0;  
}

/* Function: convertLower
 * Parameters: string word
 * Returns: string
 * Description: Takes a string and convert all uppercase letters in the word
 *              into lowercase letters. 
 */
string Index::convertLower(string word)
{
    int size = word.size();
    string temp = "";
    for (int i = 0; i < size; i++){
        if ((word[i] >= 65) and (word[i] <= 90))
            temp += word[i] + 32;
        else 
            temp += word[i];
    }
    return temp;
}
 
/* Function: checkExpand
 * Parameters: None
 * Returns: None
 * Description: Checks if the wordIndex needs to be expanded. If so, go through
 *              the whole index and rehash all the root word, and puts all the
 *              info into the new vector. 
 */  
void Index::checkExpand()
{
    if (double(currentWordNum) / double(wordIndexSize) >= 0.7){
        Words temp;
        temp.word = "EMPTY";
        vector<Words> vect(wordIndexSize * 2 + 113, temp); 
        int WIS = wordIndexSize;
        wordIndexSize = wordIndexSize * 2 + 113;
        currentWordNum = 0;
        for (int i = 0; i < WIS; i++){
            if (wordIndex[i].word != "EMPTY"){
                size_t hashI = hashingWords(vect, wordIndex[i].word);
                int subS = wordIndex[i].subwords.size();
                for (int j = 0; j < subS; j++){
                    subWords nsw;
                    nsw.word = wordIndex[i].subwords[j].word;
                    
                    int lineN = wordIndex[i].subwords[j].lineIndexNums.size();
                    for (int k = 0; k < lineN; k++){
                        nsw.lineIndexNums.push_back(
                                wordIndex[i].subwords[j].lineIndexNums[k]);
                    }                    
                    vect[hashI].subwords.push_back(nsw); 
                }
            }
        }
        wordIndex = vect;
    }
}

/* Function: Gerp
 * Parameters: string word, ostream &output
 * Returns: None
 * Description: Searches the word given sensitively, and outputs all info. 
 */
void Index::Gerp(string word, ostream &output)
{
    string temp = stripNonAlphaNum(word); 
    string root = convertLower(temp);
    size_t index = hashingWords(wordIndex, root);
    bool not_found = true;

    int subsize = wordIndex[index].subwords.size();
    for (int i = 0; i < subsize; i++){
        if (wordIndex[index].subwords[i].word == temp){
            not_found = false;
            int lsize = wordIndex[index].subwords[i].lineIndexNums.size();
            for (int j = 0; j < lsize; j++){
                int Lindex = wordIndex[index].subwords[i].lineIndexNums[j];
                output << lineIndex[Lindex].filePath << ":";
                output << lineIndex[Lindex].lineNum << ": ";
                output << lineIndex[Lindex].line << "\n";
            }
        }
    }
    if (not_found == true){
        output << word << " Not Found. Try with @insensitive or @i.\n";
    }   
}

/* Function: GerpInsensitive
 * Parameters: string Word, ostream &output
 * Returns: None
 * Description: Searches the word insensitively, outputs all info. 
 */
void Index::GerpInsensitive(string word, ostream &output)
{
    string temp = stripNonAlphaNum(word); 
    string root = convertLower(temp);
 
    size_t index = hashingWords(wordIndex, root);

    if (wordIndex[index].word == "EMPTY"){
        output << word << " Not Found.\n";
    } else {
        int subsize = wordIndex[index].subwords.size();
        for (int i = 0; i < subsize; i++){
            int lsize = wordIndex[index].subwords[i].lineIndexNums.size();
            for (int j = 0; j < lsize; j++){
                int Lindex = wordIndex[index].subwords[i].lineIndexNums[j];
                output << lineIndex[Lindex].filePath << ":";
                output << lineIndex[Lindex].lineNum << ": ";
                output << lineIndex[Lindex].line << "\n";
            }
        }

    }
}







