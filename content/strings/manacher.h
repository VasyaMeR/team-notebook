/**
 * Author: Vasyl Merenych
 * Date: 2024-09-12
 * License: CC0
 * Source: adamant cf-blog
 * Description: For each position in a string, computes p[0][i] = half length of
 *  longest even palindrome around pos i, p[1][i] = longest odd (half rounded down).
 * Time: O(N), N - size of string s
 * Status: -
 */


vector<vector<int>> manacher(string s) {
	int n = s.size();
	vector<vector<int>> p(2, vector<int>(n,0));

    for (int z = 0, l = 0, r = 0; z < 2; z++, l = 0, r = 0) {
        for (int i = 0; i < n; i++) {
            if (i < r) 
				p[z][i] = min(r - i + !z, p[z][l + r - i + !z]);
			
            int L= i - p[z][i], R = i + p[z][i] - !z;
            while (L - 1 >= 0 && R + 1 < n && s[L - 1] == s[R + 1]) {
				p[z][i]++; L--; R++;
			}
            if (R > r) {
				l = L;
				r = R;
			}
		}
	}
	return p;
}