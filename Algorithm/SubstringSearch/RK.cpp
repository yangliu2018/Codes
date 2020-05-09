#include <string>
#include <vector>
#include <array>
#include <iostream>
using namespace std;

// M: pattern length, R: base, Q: divisor
long long Hash(const string& key, int pos, int M, int R, int Q) {
    long long h = 0;
    for (int i = 0; i < M; ++i) {
        h = (h * R + key[pos + i]) % Q;
    }
    return h;
}

/// TODO: generate bit random prime number
long long LongRandomPrime() {
    return (long long)(1e9 + 7);
}

// Robin-Karp fingerprint search
// Monte Carlo algorithm: guarantee completion time but fail to output a correct answer with a small probability
// very large value of Q makes it extremely unlikely that a collision will occur (collision probability 1/Q for a random string)
// prime number makes the frequency distribution of the hash values more uniform, even though the hash function is relatively weak
int Search(const string& pattern, const string& text) {
    int M = pattern.size(), N = text.size(), R = 256;
    long long Q = LongRandomPrime();
    long long RM = 1;    // RM = R^(M-1) % Q
    for (int i = 1; i < M; ++i) RM = (RM * R) % Q;
    long long pattern_hash = Hash(pattern, 0, M, R, Q);
    cout << pattern_hash << "\n\n";

    int i = M;
    long long hash = Hash(text, 0, M, R, Q); // hash value for substring in text
    // Monte Carlo: only check the hash value but not check substring characters again
    // rolling hash: reuse the hash value of last hash to calculate next hash value
    while (i < N && hash != pattern_hash) {
        hash = ((hash + Q - text[i - M] * RM % Q) * R + text[i]) % Q;
        ++i;
        cout << hash << endl;
    }
    return hash == pattern_hash ? i - M : N;
}



int main() {
    string text = "AABRAACADABRAACAADABRA";
    string pattern = "AACAA";
    //string pattern = "AADABRA";
    int pos = Search(pattern, text);
    cout << text << endl;
    for (int idx = 0; idx < pos; ++idx) cout << " ";
    cout << pattern << endl;
    return 0;
}