#include <bits/stdc++.h>
using namespace std;

vector<int> buildlps(string pat) {
    int n = pat.size();
    vector<int> lps(n, 0);
    int len = 0;
    for (int i = 1; i < n;) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0)
                len = lps[len - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

vector<int> kmpsearch(string text, string pat) {
    vector<int> lps = buildlps(pat);
    vector<int> res;
    int i = 0, j = 0;
    int n = text.size(), m = pat.size();
    while (i < n) {
        if (text[i] == pat[j]) {
            i++;
            j++;
        }
        if (j == m) {
            res.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && text[i] != pat[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return res;
}

int main() {
    string text, pat;
    cin >> text >> pat;
    vector<int> pos = kmpsearch(text, pat);
    if (pos.empty())
        cout << "Pattern not found";
    else {
        for (int x : pos)
            cout << "Pattern found at index " << x << "\n";
    }
}


/*
ababcabcabababd ababd
Pattern found at index 10


*/