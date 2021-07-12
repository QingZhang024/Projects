/* stringProcessing.cpp
 * 
 * Qing Zhang
 * Comp 15
 * Proj 2
 */

#include <iostream>
#include <string>
#include "stringProcessing.h"

using namespace std;

/* Function: stripNonAlphaNum
 * Parameters: string string
 * Returns: string
 * Description: Stripps the beginning and ending non-alphanumaric digits. 
 */
string stripNonAlphaNum(string string)
{
    int start = -1;
    int end = -1;
    int size = string.size();
    for (int i = size - 1; i >= 0; i--){
        if (string[i] < 48){
        }else if ((string[i] > 57) and (string[i] < 65)){
        }else if ((string[i] > 90) and (string[i] < 97)){
        }else if (string[i] > 122){
        }else {
            end = i;
            break;
        }
    }
    for (int n = 0; n <= end; n++){
        if (string[n] < 48){
        }else if ((string[n] > 57) and (string[n] < 65)){
        }else if ((string[n] > 90) and (string[n] < 97)){
        }else if (string[n] > 122){
        }else {
            start = n;
            break;
        }      
    }
    std::string stripped = "";
    for (int t = start; t <= end; t++){
        stripped += string[t];
    }
    return stripped;
}
