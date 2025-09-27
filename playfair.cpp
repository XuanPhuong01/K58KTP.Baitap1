#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

char table5[5][5];

// Tao bang Playfair 5x5 tu khóa (ghép J->I)
void buildTable(const string &key) {
    vector<bool> used(26, false);
    string letters = "";

    for (size_t i = 0; i < key.size(); ++i) {
        char c = key[i];
        if (!isalpha((unsigned char)c)) continue;
        c = toupper((unsigned char)c);
        if (c == 'J') c = 'I';
        if (!used[c - 'A']) {
            used[c - 'A'] = true;
            letters.push_back(c);
        }
    }
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (c == 'J') continue; // b? J
        if (!used[c - 'A']) {
            letters.push_back(c);
            used[c - 'A'] = true;
        }
    }
    int p = 0;
    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            table5[r][c] = letters[p++];
        }
    }
}

// Tim vi tri ki tu trong bang (tra ve pair)
pair<int,int> getPos(char ch) {
    if (ch == 'J') ch = 'I';
    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            if (table5[r][c] == ch) return make_pair(r, c);
        }
    }
    return make_pair(-1, -1); // không tim thay(khong nen xay ra)
}

// Chuan hoa van ban:giu chu, chuyen hoa,J->I,chuyen hoa,chen X khi can de tao digraph
string prepareText(const string &input) {
   
    string tmp;
    for (size_t i = 0; i < input.size(); ++i) {
        char ch = input[i];
        if (!isalpha((unsigned char)ch)) continue;
        ch = toupper((unsigned char)ch);
        if (ch == 'J') ch = 'I';
        tmp.push_back(ch);
    }
    
    string out;
    size_t i = 0;
    while (i < tmp.size()) {
        char a = tmp[i];
        char b = (i + 1 < tmp.size()) ? tmp[i+1] : '\0';
        out.push_back(a);
        if (b == '\0') {
          
            out.push_back('X');
            break;
        }
        if (a == b) {
            
            out.push_back('X');
            i += 1;
        } else {
            
            out.push_back(b);
            i += 2;
        }
    }
    if (out.size() % 2 != 0) out.push_back('X'); 
    return out;
}
//xu li mot cap khi ma hoa hoa giai ma
string processPair(char a, char b, bool encrypt) {
    pair<int,int> pa = getPos(a);
    pair<int,int> pb = getPos(b);
    int r1 = pa.first, c1 = pa.second;
    int r2 = pb.first, c2 = pb.second;
    string res;
    if (r1 == r2) {
        
        if (encrypt) {
            res.push_back(table5[r1][(c1 + 1) % 5]);
            res.push_back(table5[r2][(c2 + 1) % 5]);
        } else {
            res.push_back(table5[r1][(c1 + 4) % 5]); // -1 mod5 = +4
            res.push_back(table5[r2][(c2 + 4) % 5]);
        }
    } else if (c1 == c2) {
       
        if (encrypt) {
            res.push_back(table5[(r1 + 1) % 5][c1]);
            res.push_back(table5[(r2 + 1) % 5][c2]);
        } else {
            res.push_back(table5[(r1 + 4) % 5][c1]);
            res.push_back(table5[(r2 + 4) % 5][c2]);
        }
    } else {
        
        res.push_back(table5[r1][c2]);
        res.push_back(table5[r2][c1]);
    }
    return res;
}

// Ma hóa Playfair
string playfairEncrypt(const string &plain) {
    string prepared = prepareText(plain);
    string out;
    for (size_t i = 0; i + 1 < prepared.size(); i += 2) {
        out += processPair(prepared[i], prepared[i+1], true);
    }
    return out;
}

// Giai ma Playfair
string playfairDecrypt(const string &cipher) {
    
    string out;
    for (size_t i = 0; i + 1 < cipher.size(); i += 2) {
        out += processPair(cipher[i], cipher[i+1], false);
    }
    return out;
}


void printTable() {
    cout << "Playfair table:\n";
    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) cout << table5[r][c] << ' ';
        cout << '\n';
    }
}

int main() {
    string key, text;
    cout << "Nhap khoa: ";
    getline(cin, key);
    buildTable(key);
    //printTable(); 

    cout << "Nhap van ban: ";
    getline(cin, text);

    string enc = playfairEncrypt(text);
    cout << "Ma hoa: " << enc << '\n';

    string dec = playfairDecrypt(enc);
    cout << "Giai ma: " << dec << '\n';

    return 0;
}

