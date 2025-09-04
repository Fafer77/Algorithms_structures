#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

vector<int> z_function(string const& s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;

    for (int i = 1; i < n; ++i) {
        if (i < r)
            z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[z[i] + i])
            z[i]++;
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int get_z(vector<int> const& z, int i) {
    if (0 <= i && i < (int)z.size())
        return z[i];
    else
        return 0;
}

vector<pair<int, int>> repetitions;

void convert_to_repetitions(int shift, bool left, int cntr, 
                            int l, int left_extend, int right_extend) {
    for (int l1 = max(1, l - right_extend); l1 <= min(l, left_extend); ++l1) {
        if (left && l1 == l)
            break;
        int pos = shift + (left ? cntr - l1 : cntr - l - l1 + 1);
        repetitions.emplace_back(pos, pos + 2 * l - 1);
    }
}

void find_repetitions(string s, int shift = 0) {
    int n = s.size();
    if (n == 1)
        return;
    
    int nu = n / 2;
    int nv = n - nu;
    string u = s.substr(0, nu);
    string v = s.substr(nu);
    string ru(u.rbegin(), u.rend());
    string rv(v.rbegin(), v.rend());

    find_repetitions(u, shift);
    find_repetitions(v, shift + nu);

    vector<int> z1 = z_function(ru);
    vector<int> z2 = z_function(v + '#' + u);
    vector<int> z3 = z_function(ru + '#' + rv);
    vector<int> z4 = z_function(v);

    for (int cntr = 0; cntr < n; ++cntr) {
        int l, left_extend, right_extend;
        if (cntr < nu) {
            l = nu - cntr;
            left_extend = get_z(z1, nu - cntr);
            right_extend = get_z(z2, nv + 1 + cntr);
        } else {
            l = cntr - nu + 1;
            left_extend = get_z(z3, nu + 1 + nv - 1 - (cntr - nu));
            right_extend = get_z(z4, cntr - nu + 1);
        }
        if (left_extend + right_extend >= l)
            convert_to_repetitions(shift, cntr < nu, cntr, l, left_extend, right_extend);
    }
}

int main() {
    string test_string = "abracadabracadabra";

    cout << "Testowany string: " << test_string << endl;

    repetitions.clear();

    find_repetitions(test_string);

    cout << "Znalezione powtórzenia (start, koniec):" << endl;
    if (repetitions.empty()) {
        cout << "Brak powtórzeń." << endl;
    } else {
        sort(repetitions.begin(), repetitions.end());
        for (const auto& p : repetitions) {
            cout << "  - (" << p.first << ", " << p.second << ") -> " 
                 << test_string.substr(p.first, p.second - p.first + 1) << endl;
        }
    }

    return 0;
}
