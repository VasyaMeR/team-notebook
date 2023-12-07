/**
 * Author: Vasyl Merenych
 * Date: 2022-09-28
 * License: CC0
 * Source: folklore
 * Description: Z-functions, z[i] equal to the length of largest common prefix of string s and suffix of s starting at i.
 * Time: O(N), N - size of string s
 * Status: -
 */

vector<int> z_function(const string& s) {
	int n = s.size();
	vector<int> z(n);
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i <= r)
			z[i] = max(r - i + 1, z[i - l]);
		while (z[i] + i < n && s[z[i] + i] == s[z[i]])
			z[i]++;
		if (z[i] + i - 1 > r) {
			r = z[i] + i - 1;
			l = i;
		}
	}
	return z;
}
