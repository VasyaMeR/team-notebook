/**
 * Author: Vasyl Merenych
 * Date: 2022-09-28
 * License: CC0
 * Source: folklore
 * Description: Suffix array will contain integers that represent the starting indexes of the all the suffixes of a given string, after the aforementioned suffixes are sorted.
 * Time: O(N * log2(N)), N - size of string s
 * Status: -
 */

vector<int> suffix_arrays(string s) {
	s = s + "$";
	int n = s.size();
	
	vector<int> p(n);
	vector<vector<int>> c(20, vector<int>(n));
	int alphabet = 256;

	auto set_classes = [&](int k) {
		int classes = 0;
		c[k][p[0]] = classes++;
		for (int i = 1; i < n; i++) {
			auto cur = pair{c[k - 1][p[i]], c[k - 1][(p[i] + (1<<(k-1))) % n]};
			auto prev = pair{c[k - 1][p[i - 1]], c[k - 1][(p[i - 1] + (1<<(k-1))) % n]};
			if (cur == prev) {
				c[k][p[i]] = c[k][p[i - 1]];
			} else {
				c[k][p[i]] = classes++;
			}
		}
	};

	auto init_base = [&]() {
		vector<int> cnt(alphabet);
		for (int i = 0; i < n; i++) {
			cnt[s[i]]++;
		}
		for (int i = 1; i < alphabet; i++) {
			cnt[i] += cnt[i - 1];
		}
		for (int i = n - 1; i >= 0; i--) {
			p[cnt[s[i]] - 1] = i;
			cnt[s[i]]--;

		}
		int classes = 0;
		c[0][p[0]] = classes++;
		for (int i = 1; i < n; i++) {
			if (s[p[i]] == s[p[i - 1]]) {
				c[0][p[i]] = c[0][p[i - 1]];
			} else {
				c[0][p[i]] = classes++;
			}
		}
	};

	init_base();

	for (int k = 0; (1<<k) < n; k++) {
		vector<int> pn(n), cnt(n);
		for (int i = 0; i < n; i++) {
			pn[i] = (p[i] - (1<<k) + n) % n;
			cnt[c[k][pn[i]]]++;
		}

		for (int i = 1; i < n; i++)
			cnt[i] += cnt[i - 1];

		for (int i = n - 1; i >= 0; i--) {
			p[cnt[c[k][pn[i]]] - 1] = pn[i];
			cnt[c[k][pn[i]]]--;
		}
		
		set_classes(k + 1);
	}

	p.erase(p.begin());
	return p;
}
