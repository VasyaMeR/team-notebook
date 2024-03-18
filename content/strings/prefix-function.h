/**
 * Author: Vasyl Merenych
 * Date: 2024-03-16
 * License: CC0
 * Source: folklore
 * Description: The prefix function for this string is defined as an array p of length n, where p[i] is the length of the longest valid prefix of the substring s[0...i], which is also a suffix of this substring.
 * Time: O(N), N - size of string s
 * Status: -
 */


vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
