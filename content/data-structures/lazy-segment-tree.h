/**
 * Author: Vasyl Merenych
 * Date: 2022-12-05
 * License: CC0
 * Source: folklore
 * Description: Segment tree, update(+=) at segment, sum at segment. R is excluded.
 * Time: update - O(\log N), get - O(\log N)
 * Status: -
 */

#include <array>
#include <vector>
template<typename T> struct lazy_segment_tree {
	struct node{
		T sum = 0;
		T promise = 0;
	};

	int n;
	std::vector<node> tree; 

	lazy_segment_tree(int n_, const vector<T>& init): n(n_) {
		tree.assign(4 * n, node{});
		build(1, 0, n, init);
	}

	void build(int v, int l, int r, const vector<T>& init) {
		if (l + 1 == r) {
			tree[v].sum = init[l];
			return;
		}
		if (l >= r)
			return;
		int mid = (l + r) / 2;
		build(2 * v, l, mid, init);
		build(2 * v + 1, mid, r, init);

		tree[v].sum = (tree[2 * v].sum + tree[2 * v + 1].sum);
	}

	void update(int l, int r, T value) {
		update(1, 0, n, l, r, value);
	}

	T get(int l, int r) {
		return get(1, 0, n, l, r);
	}

	T get(int pos) {
		return get(1, 0, n, pos, pos + 1);
	}

	void push(int v, int l, int r) {
		if (tree[v].promise == 0)
			return;
		
		tree[v].sum += tree[v].promise * (r - l);
		if (l + 1 < r) {
			tree[2 * v].promise += tree[v].promise;
			tree[2 * v + 1].promise += tree[v].promise;
		}
		tree[v].promise = 0;
	}

	void update(int v, int tl, int tr, int l, int r, T value) {
		push(v, tl, tr);
		if (l >= tr || tl >= r)
			return;
		if (l <= tl && tr <= r) {
			tree[v].promise += value;
			push(v, tl, tr);
			return;
		}
		int mid = (tl + tr) / 2;
		update(2 * v, tl, mid, l, r, value);
		update(2 * v + 1, mid, tr, l, r, value);

		tree[v].sum = tree[2 * v].sum + tree[2 * v + 1].sum;
	}

	T get(int v, int tl, int tr, int l, int r) {
		push(v, tl, tr);
		if (l >= tr || tl >= r)
			return 0;
		if (l <= tl && tr <= r) {
			return tree[v].sum;
		}
		int mid = (tl + tr) / 2;
		auto left = get(2 * v, tl, mid, l, r);
		auto right = get(2 * v + 1, mid, tr, l, r);

		return left + right;
	}
};