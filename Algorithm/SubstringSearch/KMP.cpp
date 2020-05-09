#include <string>
#include <vector>
#include <array>
using namespace std;

// Knuth-Morris-Pratt substring search
// key idea: increment or back up in pattern string determining on match or mismatch
// faster than brute-force method when both pattern and text are self-repetitive
// worst cast time complexity: O(M + N)
int search(const string& pattern, const string& text) {
    size_t M = pattern.size(), N = text.size();
    size_t i = 0, j = 0;
    
    // dfa: deterministic finite-state automaton
    // dfa[pos][ch]
    //   pos: next character in pattern to match is pattern[pos] / current state
    //   ch: the charater to match / jump path / input character from text
    //   when pattern[pos] == ch, match transition, dfa[pos][ch] = pos + 1 
    vector<array<size_t, 128>> dfa(M, array<size_t, 128>{});

    // O(M), construct the DFA
    // i: state to backup when mismatch
    // j: next state to increment
    dfa[0][pattern[0]] = 1;
    for (i = 0, j = 1; j < M; ++j) {
        // if ch != pattern[j], state j should be treated as state i
        // so i and j has the same jump table except for dfa[j][pattern[j]
        dfa[j] = dfa[i];            // mismatch case
        dfa[j][pattern[j]] = j + 1; // match case
        i = dfa[i][pattern[j]];
    }

    // O(N), search pattern in text using DFA
    // i: index in text, input of dfa
    // j: index in pattern, state of dfa
    for (i = 0, j = 0; i < N && j < M; ++i) {
        j = dfa[j][text[i]];
    }
    return j == M ? i - M : N;
}

#include <iostream>
int main() {
    string text = "AABRAACADABRAACAADABRA";
    string pattern = "AACAA";
    int pos = search(pattern, text);
    cout << text << endl;
    for (int idx = 0; idx < pos; ++idx) cout << " ";
    cout << pattern << endl;
    return 0;
}