// ciphers_simple.cpp
// Simple console tool: Caesar + Columnar Transposition
// Compatible with older compilers (Dev-C++ / MinGW)
// Author: Phuong (template s?a l?i)

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <limits>   // numeric_limits
using namespace std;

// ---------------- Caesar ----------------
int normalizeKey(int k) {
    k %= 26;
    if (k < 0) k += 26;
    return k;
}

string caesarEncrypt(const string &text, int key) {
    int k = normalizeKey(key);
    string out;
    out.reserve(text.size());
    for (size_t i = 0; i < text.size(); ++i) {
        unsigned char ch = static_cast<unsigned char>(text[i]);
        if (isupper(ch)) {
            char base = 'A';
            out.push_back(static_cast<char>(base + (ch - base + k) % 26));
        } else if (islower(ch)) {
            char base = 'a';
            out.push_back(static_cast<char>(base + (ch - base + k) % 26));
        } else {
            out.push_back(text[i]);
        }
    }
    return out;
}

string caesarDecrypt(const string &text, int key) {
    return caesarEncrypt(text, -normalizeKey(key));
}

// ---------------- Columnar transposition (permutation) ----------------
// We accept a key entered as space separated integers (1..n or 0..n-1).
// During encrypt: for each block of size n, we append characters in the order given by key.
// Example: key = [3 1 2] and block "ABC" -> output "CAB"

// Parse a line of integers into vector<int>
vector<int> parseKeyLine(const string &line) {
    vector<int> v;
    stringstream ss(line);
    int x;
    while (ss >> x) v.push_back(x);
    return v;
}

// Normalize key to 0-based indexes (0..n-1), accept either 1-based or 0-based input
// Returns true if valid permutation
bool normalizeKeyPermutation(const vector<int> &input, vector<int> &out) {
    int n = (int)input.size();
    if (n == 0) return false;
    out.assign(n, -1);

    bool looksOneBased = true;
    for (int i = 0; i < n; ++i) {
        if (input[i] < 1 || input[i] > n) { looksOneBased = false; break; }
    }
    if (looksOneBased) {
        for (int i = 0; i < n; ++i) out[i] = input[i] - 1; // convert to 0-based
    } else {
        // assume 0-based, validate
        for (int i = 0; i < n; ++i) {
            if (input[i] < 0 || input[i] >= n) return false;
            out[i] = input[i];
        }
    }
    // check permutation

