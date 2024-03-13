/**
 * Author: Vasya Merenych
 * Date: 2024-03-13
 * License: CC0
 * Source: 
 * Description: Disjoint Set Union with roolbacks
 * Time: O(q * log(q) * log(n)), q - number of queries, n - number of vertices
 * Status: -
 */

#include <array>
#include <vector>

struct Query {
    int v, u;
    bool united;
    Query(int _v, int _u) : v(_v), u(_u) {}
};

struct DSU
{
	struct DSU_save
	{
		int v, rang_v;
		int u, rang_u;
	};
	int n;
	std::vector<int> pred, rang;
	std::vector<DSU_save> saves;


	DSU(int n_): n(n_) {
		pred.resize(n);
		rang.resize(n);
		for (int i = 0; i < n; i++) {
			pred[i] = i;
			rang[i] = 0;
		}
	}
	int get(int v) {
		if (pred[v] == v) {
			return v;
		}
		return get(pred[v]);
	}

	bool merge(int u, int v) {
		u = get(u);
		v = get(v);
		if (u == v)
			return false;
		if (rang[u] < rang[v]) 
			std::swap(u, v);
		saves.push_back({v, rang[v], u, rang[u]});
		pred[v] = u;

		if (rang[u] == rang[v]) {
			rang[u]++;
		}
		return true;
	}

	void rollback() {
		if (saves.empty())
			return;
		auto [v, rang_v, u, rang_u] = saves.back();
		rang[v] = rang_v;
		rang[u] = rang_u;

		pred[v] = v;
		pred[u] = u;

		saves.pop_back();
	}
};

struct dynamic_connectivity_problem {
	std::vector<std::vector<Query>> tree;
	int q, n;
	DSU dsu;
	dynamic_connectivity_problem(int q_, int n_): q(q_), n(n_), dsu(DSU(n_)) {
		tree.resize(4 * q);
	}

	void add(Query a, int l, int r) {
		add(1, 0, q, l, r, a);
	}

	void add(int v, int tl, int tr, int l, int r, const Query& a) {
		if (l <= tl && tr <= r) {
			tree[v].push_back(a);
			return;
		}
		if (l >= tr || tl >= r)
			return;
		int mid = (tr + tl) / 2;
		add(2 * v, tl, mid, l, r, a);
		add(2 * v + 1, mid, tr, l, r, a);
	}

	void dfs(int v, int l, int r) {
		if (l >= r)
			return;
		
		for (auto& q: tree[v]) {
			q.united = dsu.merge(q.u, q.v);
		}
		if (l + 1 == r) {
			int x = dsu.get(0);
			// do something
		} else {
			int mid = (r + l) / 2;
			dfs(2 * v, l, mid);
			dfs(2 * v + 1, mid, r);
		}

		for (auto& q: tree[v]) {
			if (q.united)
				dsu.rollback();
			q.united = false;
		}
	}
};
