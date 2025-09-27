#include <iostream>
#include <string>
using namespace std;

// Ham tra ve ki tu da ma hoa voi 1 ky tu key
char encryptChar(char c, char k) {
    if (!isalpha(c)) return c;
    char base = isupper(c) ? 'A' : 'a';
    int shift = tolower(k) - 'a';
    return (c - base + shift) % 26 + base;
}

//Ham  tra ve ky tu da giai ma voi 1 ky ry key
char decryptChar(char c, char k) {
    if (!isalpha(c)) return c;
    char base = isupper(c) ? 'A' : 'a';
    int shift = tolower(k) - 'a';
    return (c - base - shift + 26) % 26 + base;
}

// Ma hoa toan bo van ban
string vigenereEncrypt(string text, string key) {
    string res = "";
    int j = 0, n = key.size();
    for (char c : text) {
        res += encryptChar(c, key[j % n]);
        if (isalpha(c)) j++;
    }
    return res;
}

// Giai ma toan bo van ban
string vigenereDecrypt(string text, string key) {
    string res = "";
    int j = 0, n = key.size();
    for (char c : text) {
        res += decryptChar(c, key[j % n]);
        if (isalpha(c)) j++;
    }
    return res;
}

int main() {
    string text, key;
    cout << "Nhap van ban: ";
    getline(cin, text);
    cout << "Nhap khoa: ";
    cin >> key;

    string mahoa = vigenereEncrypt(text, key);
    cout << "Ma hoa: " << mahoa << endl;

    string giaima = vigenereDecrypt(mahoa, key);
    cout << "Giai ma: " << giaima << endl;

    return 0;
}

