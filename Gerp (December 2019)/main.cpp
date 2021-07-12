/* main.cpp
 *
 * Qing Zhang
 * Comp 15
 * Proj2: Gerp
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "Index.h"

using namespace std;

void Run(Index &myIndex, ofstream &outfile);

/* main of Gerp
 * 
 * Runs the Gerp by creating an Index, and run commands with it. 
 */
int main(int argc, char *argv[])
{
    if (argc != 3){
        cerr << "Usage: gerp directory output_file";
        return EXIT_FAILURE;
    }
    Index myIndex(argv[1]);

    string outputfile = argv[2];
    ofstream outfile;
    outfile.open(outputfile);

    Run(myIndex, outfile);
    return 0;
}

/* Function: Run
 * Paramenters: Index &myIndex, ofstream &outfile
 * Returns: None
 * Description: Ask the user for what to Query and query according to given
 *              commands. 
 */
void Run(Index &myIndex, ofstream &outfile)
{
    string command;
    cout << "Query? ";
    while(getline(cin, command)){
        stringstream ss;
        ss.str(command);
        string word;
        while (ss >> word){
            cout << "\n";
            if ((word == "@q") or (word == "@quit")){
                cout << "\nGoodbye! Thank you and have a nice day.\n";
                return;
            }
            if ((word == "@i") or (word == "@insentitive")){
                ss >> word;
                myIndex.GerpInsensitive(word, outfile);
                cout << "Query? ";
            }else if (word == "@f"){
                ss >> word;
                outfile.close();
                outfile.open(word);
            }else{
                myIndex.Gerp(word, outfile);
                cout << "Query? ";
            }
        } 
    }
}
