#include <iostream>
#include <chrono>
#include <vector>
#include "memo.h"


using namespace std;


string to_string(const vector<int> &v);
void benchmark_rob();
void benchmark_SBS();



int main(void) {
    string separator(80, '-');
    srand(time(NULL));
    cout << separator << endl;
    benchmark_rob();
    cout << separator << endl;
    benchmark_SBS();
    cout << separator << endl;
    return 0;
}


string to_string(const vector<int> &v) {
    string s = "[";
    for (unsigned i = 0; i < v.size() - 1; ++i) s += to_string(v[i]) + ", ";
    s += to_string(v[v.size() - 1]) + "]";
    return s;
}


void benchmark_rob() {
    string separator(80, '#');

    // sizes of tests
    vector<int> house_sizes{30, 40, 45};

    for (int& house_size : house_sizes) {

        // generate test case
        vector<int> houses;
        for (int i = 0; i < house_size; ++i) {
            houses.push_back(rand() % 100);
        }

        // benchmarking recursive solution
        auto t1 = chrono::high_resolution_clock::now();
        int max_val = rob(houses, (int)houses.size() - 1);
        auto t2 = chrono::high_resolution_clock::now();
        float d = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
        float t = d / 1000000;

        cout << separator << endl;
        cout << "Recursive rob(" << to_string(houses) << ", "
             << (int)houses.size() - 1 << "): " << max_val 
             << "; took " << t << " seconds\n";

        // benchmarking memo solution
        t1 = chrono::high_resolution_clock::now();
        max_val = memo_rob(houses, (int)houses.size() - 1);
        t2 = chrono::high_resolution_clock::now();
        d = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
        t = d / 1000000;

        cout << "Memoized  rob(" << to_string(houses) << ", "
             << (int)houses.size() - 1 << "): " << max_val 
             << "; took " << t << " seconds\n";
    }
}


void benchmark_SBS() {
    string separator(80, '#');

    // sizes of tests
    vector<int> list_sizes{20, 30, 33};

    for (int& list_size : list_sizes) {

        // generate test case
        vector<int> A;
        for (int i = 0; i < list_size; ++i) {
            A.push_back(rand() % 50);
        }

        int target = rand() % 1000;

        // benchmarking recursive solution
        auto t1 = chrono::high_resolution_clock::now();
        bool subset_exist = SBS(A, target, (int)A.size() - 1);
        auto t2 = chrono::high_resolution_clock::now();
        float d = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
        float t = d / 1000000;

        cout << separator << endl;
        cout << "Recursive SBS(" << to_string(A) << ", " << target << ", "
             << (int)A.size() - 1 << "): " << (subset_exist ? "true" : "false")
             << "; took " << t << " seconds\n";

        // benchmarking memo solution
        t1 = chrono::high_resolution_clock::now();
        subset_exist = memo_SBS(A, target, (int)A.size() - 1);
        t2 = chrono::high_resolution_clock::now();
        d = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
        t = d / 1000000;

        cout << "Memoized  SBS(" << to_string(A) << ", " << target << ", "
             << (int)A.size() - 1 << "): " << (subset_exist ? "true" : "false")
             << "; took " << t << " seconds\n";
    }
}
