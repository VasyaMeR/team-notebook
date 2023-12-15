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
	for(int i = 1; i < n; i++) {
		if(i < r) {
			z[i] = min(r - i, z[i - l]);
		}
		while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
			z[i]++;
		}
		if(i + z[i] > r) {
			l = i;
			r = i + z[i];
		}
	}
	return z;
}
