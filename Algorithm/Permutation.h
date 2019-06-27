#pragma once

#include <vector>

template <class T>
void NextPermutation(std::vector<T>& perm) {
    int i = (int)perm.size() - 2;
    int j = (int)perm.size() - 1;
    while (i >= 0 && perm[i] > perm[i + 1]) --i;
    if (i >= 0) {
        while (perm[j] < perm[i]) --j;
        std::swap(perm[i], perm[j]);
    }
    ++i;
    j = (int)perm.size() - 1;
    while (i < j) std::swap(perm[i++], perm[j--]);
}