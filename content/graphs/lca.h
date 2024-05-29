/**
 * Author: Vasyl Merenych
 * Date: 2024-03-13
 * License: CC0
 * Source: folklore
 * Description: Finds lowest common ancestor of two vertices using sparce table
 * Time: O(n * log(n)) - build, O(1) - get
 * Status: -
 */

struct LCA {
	vector<pair<int, int>> traversal;
	vector<int> pos;
	graph<int> g;
	int n;
	sparse_table<pair<int, int>> st;
	
	LCA(int n_, graph<int> g_, int root = 0): n(n_), g(g_) {
		pos.resize(n);
		dfs(root, -1, 0);
		st = sparse_table<pair<int, int>>(traversal.size(), traversal);
	}

	void dfs(int v, int pred, int depth) {
		pos[v] = traversal.size();
		traversal.push_back({depth, v});
		for (auto to : g[v]) {
			if (to != pred) {
				dfs(to, v, depth + 1);
				traversal.push_back({depth, v});
			}
		}
	}

	int get(int a, int b) {
		if (a == b)
			return a;
		return st.get(min(pos[a], pos[b]), max(pos[a], pos[b]) + 1).second;
	}
};