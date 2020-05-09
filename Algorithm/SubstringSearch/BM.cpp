#include <string>
#include <vector>
#include <array>
#include <iostream>
using namespace std;

void log(const string& pattern, const string& text, int pos, int skip) {
    cout << text << endl;
    for (int idx = 0; idx < pos; ++idx) cout << " ";
    cout << pattern << endl;
    cout << skip << endl;
}

// Boyer-Moore substring search
// slide pattern left to right, match character right to left
// when mismatch, slide pattern to the right to match current character in text
// time complexity:
//   typical inputs: O(N / M), skip M characters every time
//   worst case: O(MN)
// futher optimization: record the rightmost possible character for each position in pattern (2-D, similar to KMP)
// futher optimization: reuse the information of the matched portion at the right of current position
// full BM algorithm provides O(N) worst-case guarantee
int search(const string& pattern, const string& text) {
    size_t M = pattern.size(), N = text.size();
    // the table giving the rightmost occurence in the pattern of each possible character
    array<int, 128> right = {};
    fill(right.begin(), right.end(), -1);
    for (size_t j = 0; j < M; ++j) right[pattern[j]] = j;
    
    // i: the current position to check pattern in text
    // j: the current position to check character in pattern
    int i = 0, j = 0, skip = 0;
    while (i + M <= N) {
        j = M - 1;
        // scan from right to left in the pattern
        while (j >= 0 && pattern[j] == text[i + j]) --j;
        if (j == -1) return i;
        // when mismatch, skip to the rightmost occurence in pattern to match current character in text
        skip = j - right[text[i + j]];
        // the jump destination should be at the left of j in pattern, 
        // so slide pattern to the right by j - right[text[i+j]], 
        // otherwise slide pattern to the right by one.
        // not consider multiple jump targets existing
        if (skip <= 0) skip = 1;
        log(pattern, text, i, skip);
        i += skip;
    }
    return N;
}



int main() {
    //string text = "AABRAACADABRAACAADABRA";
    //string pattern = "AACAA";
    string text = "AAAAAAAAAAAAAAABAAAAAAA";
    string pattern = "BAAAAA";
    int pos = search(pattern, text);
    cout << text << endl;
    for (int idx = 0; idx < pos; ++idx) cout << " ";
    cout << pattern << endl;
    return 0;
}