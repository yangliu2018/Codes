#include "Permutation.h"
#include <iostream>
using namespace std;

int main() {
    vector<int> ini = { 0, 0, 1, 1 };
    //vector<int> ini = { 1, 2, 3, 4 };
    auto vec = ini;
    do {
        for (auto& item : vec) cout << item << " ";
        cout << endl;
        NextPermutation(vec);
    } while (vec != ini);
    return 0;
}