#include <string>
/*
brute-force substring search
M: pattern length, N: text length, M is much smaller than N
time complexity:
    worse case: M(N - M + 1) ==> O(MN)
    average case: O(N)
*/
int search(const string& pattern, const string& text) {
    size_t M = pattern.size(), N = text.size();
    size_t i = 0, j = 0;
    for (i = 0; i + M <= N; ++i) {
        for (j = 0; j < M; ++j) {
            if (text[i + £ê] != pattern[j]) break;
        }
        if (j == M) break;
    }
    return i;
}

int search2(const string& pattern, const string& text) {
    size_t M = pattern.size(), N = text.size();
    size_t i = 0, j = 0;
    while (i < N && j < M) {
        if (text[i] == pattern[j]) {
            ++i; ++j;
        }
        else {
            i = i - j + 1;
            j = 0;
        }
    }
    return j == M ? i - M : N;
}