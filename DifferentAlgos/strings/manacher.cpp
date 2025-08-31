#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void printSubstring(const string& s, int left, int right) {
    for (int i = left; i <= right; ++i)
        cout << s[i];
}

void longestPalSub(const string& s) {
    string t = "@";
    for (char c : s) {
        t += '#';
        t += c;
    }

    t += '#';
    t += '$';

    vector<int> p(t.length(), 0);

    int maxLen = 0;
    int start = 0;
    int maxRight = 0;
    int center = 0;

    for (int i = 1; i < t.length() - 1; ++i) {
        if (i < maxRight)
            p[i] = min(maxRight - i, p[2 * center - i]);
        
        while (t[i + p[i] + 1] == t[i - p[i] - 1])
            p[i]++;

        if (i + p[i] > maxRight) {
            center = i;
            maxRight = i + p[i];
        }

        if (p[i] > maxLen) {
            start = (i - p[i] - 1) / 2;
            maxLen = p[i];
        }
    }

    cout << "Longest palindromic substring is: ";
    printSubstring(s, start, start + maxLen - 1);
}

int main() {
    string str = "daabddfddbegtd";
    longestPalSub(str);
    cout << endl;

    return 0;
}
