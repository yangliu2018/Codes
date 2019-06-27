#include "Permutation.h"
#include <iostream>
using namespace std;

int main() {
    vector<int> vec = { 5, 4, 3, 2, 1};
    NextPermutation(vec);
    for (auto& item : vec) cout << item << " ";
}