/**
 * Author: Merenych Vasyl
 * Date: 2023-12-05
 * License: CC0
 * Source: folklore
 * Description: Trie implementation
 * Time: O(n) 
 * Status: -
 */

template<int N = (int)1e6 + 1>
struct trie {
	struct node {
		int cnt = 0;
		array<int, 27> links;
	
		node() {
			links.fill(-1);
			cnt = 0;
		}
	};

	array<node, N> tree;  
	int sz = 0;
	int root = 0;

	bor() {
		root = sz++;
	}

	void add(string s) {
		int cur = root;
		tree[cur].cnt++;
		for (int i = 0; i < s.size(); i++) {
			int nxt = tree[cur].links[s[i] - 'a'];
			if (nxt == -1) {
				nxt = sz++;
				tree[cur].links[s[i] - 'a'] = nxt;
			}
			tree[nxt].cnt++;
			cur = nxt;
		}
	}

	void remove(string s) {
		int cur = root;
		tree[cur].cnt--;
		for (int i = 0; i < s.size(); i++) {
			int nxt = tree[cur].links[s[i] - 'a'];
			assert(nxt != -1);
			tree[nxt].cnt--;
			cur = nxt;
		}
	}

	int get_cnt_of_str(const string& s) {
		int cur = root;
		for (int i = 0; i < s.size(); i++) {
			int nxt = tree[cur].links[s[i] - 'a'];
			if (nxt == -1) {
				return 0;
			}
			cur = nxt;
		}
		return tree[cur].cnt;
	}


	void clear() {
		for (int i = 0; i < sz; i++)
			tree[i] = node();
	}
};
