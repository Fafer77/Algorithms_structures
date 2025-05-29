#include <iostream>
#include <vector>
using namespace std;

vector<int> PrefixSufixFunction(const string &P)
{
    int m = P.size();
    vector<int> pi(m);
    pi[0] = 0;
    int k = 0;
    for (int q = 1; q < m; ++q)
    {
        while (k > 0 && P[k] != P[q])
            k = pi[k - 1];
        if (P[k] == P[q])
            ++k;
        pi[q] = k;
    }
    return pi;
}

vector<int> KMP(const string &text, const string &P)
{
    int n = text.size();
    int m = P.size();
    vector<int> pi = PrefixSufixFunction(P);
    vector<int> indices;
    int j = 0;
    for (int i = 0; i < n; ++i)
    {
        while (j > 0 && text[i] != P[j])
            j = pi[j - 1];
        if (text[i] == P[j])
            ++j;
        if (j == m)
        {
            indices.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }

    return indices;
}

int main()
{
    string text, pattern;
    cout << "Enter text: ";
    cin >> text;
    cout << "Enter pattern:";
    cin >> pattern;

    vector<int> indices = KMP(text, pattern);

    for (auto i : indices)
    {
        cout << i << endl;
    }

    return 0;
}
