#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Hàm tính nghich dao modulo
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1) return x;
    return 1;
}

// Ma hoa Affine
string affineEncrypt(string text, int a, int b) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char((a * (c - base) + b) % 26 + base);
        } else result += c;
    }
    return result;
}

// Giai ma Affine
string affineDecrypt(string text, int a, int b) {
    string result = "";
    int a_inv = modInverse(a, 26);
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char((a_inv * ((c - base) - b + 26)) % 26 + base);
        } else result += c;
    }
    return result;
}

int main() {
    int choice, a, b;
    string text;

    cout << "=============================\n";
    cout << "   MA HOA AFFINE - PHUONG\n";
    cout << "=============================\n";
    cout << "1. Ma hoa\n";
    cout << "2. Giai ma\n";
    cout << "0. Thoat\n";
    cout << "=============================\n";
    cout << "Nhap lua chon: ";
    cin >> choice;
    cin.ignore(); 

    if (choice == 0) {
        cout << "Tam biet Phuong!\n";
        return 0;
    }

    cout << "Nhap van ban: ";
    getline(cin, text);

    cout << "Nhap khoa a (nguyen to cung 26) va b: ";
    cin >> a >> b;

    if (choice == 1) {
        string encrypted = affineEncrypt(text, a, b);
        cout << "Van ban da ma hoa: " << encrypted << endl;
    } else if (choice == 2) {
        string decrypted = affineDecrypt(text, a, b);
        cout << "Van ban da giai ma: " << decrypted << endl;
    } else {
        cout << "Lua chon khong hop le!\n";
    }

    return 0;
}

