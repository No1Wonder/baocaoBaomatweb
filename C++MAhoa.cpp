#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;

/* ================== CAESAR ================== */
char caesarShift(char c, int k, bool encrypt) {
    if (!isalpha(c)) return c;
    char base = isupper(c) ? 'A' : 'a';
    if (encrypt)
        return ( (c - base + k) % 26 ) + base;
    else
        return ( (c - base - k + 26) % 26 ) + base;
}
string caesarEncrypt(const string &text, int k) {
    string res = "";
    for (char c : text) res += caesarShift(c, k, true);
    return res;
}
string caesarDecrypt(const string &text, int k) {
    string res = "";
    for (char c : text) res += caesarShift(c, k, false);
    return res;
}

/* ================== AFFINE ================== */
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int modInverse(int a, int m) {
    a %= m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}
char affineShift(char c, int a, int b, bool encrypt) {
    if (!isalpha(c)) return c;
    char base = isupper(c) ? 'A' : 'a';
    if (encrypt) {
        return ( (a * (c - base) + b) % 26 ) + base;
    } else {
        int inv = modInverse(a, 26);
        return ( (inv * ((c - base - b + 26)) ) % 26 ) + base;
    }
}
string affineEncrypt(const string &text, int a, int b) {
    string res = "";
    for (char c : text) res += affineShift(c, a, b, true);
    return res;
}
string affineDecrypt(const string &text, int a, int b) {
    string res = "";
    for (char c : text) res += affineShift(c, a, b, false);
    return res;
}

/* ================== TRANSPOSITION (HOÁN V?) ================== */
string transpositionEncrypt(const string &text, int key) {
    vector<string> rows(key, "");
    for (int i = 0; i < text.size(); i++) {
        rows[i % key] += text[i];
    }
    string res = "";
    for (int i = 0; i < key; i++) res += rows[i];
    return res;
}
string transpositionDecrypt(const string &cipher, int key) {
    int n = cipher.size();
    int col = (n + key - 1) / key;
    int shortCols = (key * col) - n;
    vector<int> lens(key, col);
    for (int i = key - shortCols; i < key; i++) lens[i]--;

    vector<string> rows(key);
    int pos = 0;
    for (int i = 0; i < key; i++) {
        rows[i] = cipher.substr(pos, lens[i]);
        pos += lens[i];
    }

    string res = "";
    for (int j = 0; j < col; j++) {
        for (int i = 0; i < key; i++) {
            if (j < rows[i].size()) res += rows[i][j];
        }
    }
    return res;
}

/* ================== VIGENERE ================== */
string vigenereEncrypt(const string &text, const string &key) {
    string res = "";
    for (int i = 0, j = 0; i < text.size(); i++) {
        char c = text[i];
        if (!isalpha(c)) { res += c; continue; }
        char base = isupper(c) ? 'A' : 'a';
        int k = tolower(key[j % key.size()]) - 'a';
        res += ( (c - base + k) % 26 ) + base;
        j++;
    }
    return res;
}
string vigenereDecrypt(const string &text, const string &key) {
    string res = "";
    for (int i = 0, j = 0; i < text.size(); i++) {
        char c = text[i];
        if (!isalpha(c)) { res += c; continue; }
        char base = isupper(c) ? 'A' : 'a';
        int k = tolower(key[j % key.size()]) - 'a';
        res += ( (c - base - k + 26) % 26 ) + base;
        j++;
    }
    return res;
}

/* ================== PLAYFAIR ================== */
vector<vector<char>> generatePlayfairMatrix(const string &key) {
    string filtered = "";
    vector<bool> used(26, false);

    for (char c : key) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I';
            if (!used[c - 'A']) {
                filtered += c;
                used[c - 'A'] = true;
            }
        }
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;
        if (!used[c - 'A']) {
            filtered += c;
            used[c - 'A'] = true;
        }
    }
    vector<vector<char>> matrix(5, vector<char>(5));
    for (int i = 0; i < 25; i++) {
        matrix[i / 5][i % 5] = filtered[i];
    }
    return matrix;
}

pair<int,int> findPos(const vector<vector<char>> &matrix, char c) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (matrix[i][j] == c) return {i, j};
    return {-1, -1};
}

string playfairProcess(const string &text, const vector<vector<char>> &matrix, bool encrypt) {
    string filtered = "";
    for (char c : text) if (isalpha(c)) filtered += toupper(c);
    for (int i = 0; i < filtered.size(); i += 2) {
        if (i + 1 == filtered.size() || filtered[i] == filtered[i+1]) {
            filtered.insert(i + 1, "X");
        }
    }

    string res = "";
    for (int i = 0; i < filtered.size(); i += 2) {
        auto [r1, c1] = findPos(matrix, filtered[i]);
        auto [r2, c2] = findPos(matrix, filtered[i+1]);
        if (r1 == r2) {
            res += matrix[r1][ (c1 + (encrypt ? 1 : 4)) % 5 ];
            res += matrix[r2][ (c2 + (encrypt ? 1 : 4)) % 5 ];
        } else if (c1 == c2) {
            res += matrix[ (r1 + (encrypt ? 1 : 4)) % 5 ][c1];
            res += matrix[ (r2 + (encrypt ? 1 : 4)) % 5 ][c2];
        } else {
            res += matrix[r1][c2];
            res += matrix[r2][c1];
        }
    }
    return res;
}
string playfairEncrypt(const string &text, const string &key) {
    auto matrix = generatePlayfairMatrix(key);
    return playfairProcess(text, matrix, true);
}
string playfairDecrypt(const string &text, const string &key) {
    auto matrix = generatePlayfairMatrix(key);
    return playfairProcess(text, matrix, false);
}

/* ================== MAIN TEST ================== */
int main() {
    string text = "HELLO WORLD";
    cout << "Plaintext: " << text << "\n\n";

    // Caesar
    cout << "=== Caesar ===\n";
    string caesE = caesarEncrypt(text, 3);
    cout << "Encrypt: " << caesE << "\n";
    cout << "Decrypt: " << caesarDecrypt(caesE, 3) << "\n\n";

    // Affine
    cout << "=== Affine ===\n";
    string affE = affineEncrypt(text, 5, 8); // a=5, b=8 (gcd(5,26)=1)
    cout << "Encrypt: " << affE << "\n";
    cout << "Decrypt: " << affineDecrypt(affE, 5, 8) << "\n\n";

    // Transposition
    cout << "=== Transposition ===\n";
    string transE = transpositionEncrypt(text, 3);
    cout << "Encrypt: " << transE << "\n";
    cout << "Decrypt: " << transpositionDecrypt(transE, 3) << "\n\n";

    // Vigenere
    cout << "=== Vigenere ===\n";
    string vigE = vigenereEncrypt(text, "KEY");
    cout << "Encrypt: " << vigE << "\n";
    cout << "Decrypt: " << vigenereDecrypt(vigE, "KEY") << "\n\n";

    // Playfair
    cout << "=== Playfair ===\n";
    string playE = playfairEncrypt(text, "KEYWORD");
    cout << "Encrypt: " << playE << "\n";
    cout << "Decrypt: " << playfairDecrypt(playE, "KEYWORD") << "\n";

    return 0;
}
```
