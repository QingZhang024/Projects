/* FSTreeTraversal.cpp
 * 
 * Qing Zhang
 * Comp 15
 * Proj 2
 */

#include <iostream>
#include "DirNode.h"
#include "FSTree.h"

using namespace std;

void Print_all_Path(DirNode *root, string path);

int main(int argc, char* argv[])
{
    if (argc == 2){    
        FSTree myTree(argv[1]);
        Print_all_Path(myTree.getRoot(), "");
    }
    return 0;
}

void Print_all_Path(DirNode *root, string path)
{
    if (root -> isEmpty())
        return;
    else {
        path += root -> getName() + "/";
        int numFile = root -> numFiles();
        int numSubDir = root -> numSubDirs();
        for (int i = 0; i < numFile; i++)
            cout << path << root -> getFile(i) << "\n";
        for (int n = 0; n < numSubDir; n++){
            Print_all_Path(root -> getSubDir(n), path);
        }       
    }
}
