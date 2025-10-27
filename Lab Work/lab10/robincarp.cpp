#include <bits/stdc++.h>
using namespace std;

void rabinKarp(string txt, string pat, int q) {
    int d = 256;  
    int m = pat.length();
    int n = txt.length();

    int p = 0; // hash  for pattern
    int t = 0; // hash for text window
    int h = 1; // d^(m-1)

    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for (int i = 0; i < m; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // slide the pattern in text
    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (txt[i + j] != pat[j]) {
                    match = false;
                    break;
                }
            }
            if (match)
                cout << "Pattern found at index " << i << endl;
        }

        // hash for the  next window
        if (i < n - m) {
            t = (d * (t - txt[i] * h) + txt[i + m]) % q;

            if (t < 0)
                t = (t + q);
        }
    }
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        string txt;
        string pat;
        // cout << "Enter text: "  << endl;
        cin >> txt;
        // cout  << "Enter pattern: " ;
    cin >> pat;
    int q = 37; 
    rabinKarp(txt, pat, q);
    
   }
   return 0;
}

/*
aabbabab
abab

bacababab
abab

ababcababcabcabc
abc     

ababcababcabcabc
abcab


output 
3
aabbabab
abab
Pattern found at index 4

bacababab
abab
Pattern found at index 3
Pattern found at index 5

ababcababcabcabc
abc
Pattern found at index 2
Pattern found at index 7
Pattern found at index 10
Pattern found at index 13

*/
