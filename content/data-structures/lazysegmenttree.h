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

template<typename T> struct lazy_segment_tree {
	static const int N = 1e5 + 100;
	static const T NONE = 0;

	struct node{
		T sum = 0;
		T promise = NONE;
	};
	std::array<node, 4 * N> tree; 

	void update(int l, int r, T val) {
		update(1, 0, N, l, r, val);
	}

	node get(int l, int r) {
		return get(1, 0, N, l, r);
	}

	node get(int pos) {
		return get(1, 0, N, pos, pos + 1);
	}

	void push(int v, int l, int r) {
		if (tree[v].promise == NONE)
			return;
		tree[v].sum += tree[v].promise * (r - l);
		if (l != r) {
			tree[2 * v].promise += tree[v].promise;
			tree[2 * v + 1].promise += tree[v].promise;	
		}
		tree[v].promise = NONE;
	}

	void update(int v, int tl, int tr, int l, int r, T value) {
		push(v, tl, tr);
		if (l >= tr || tl >= r)
			return;
		if (l <= tl && tr <= r) {
			tree[v].promise = value;
			push(v, tl, tr);
			return;
		}
		int mid = (tl + tr) / 2;
		update(2 * v, tl, mid, l, r, value);
		update(2 * v + 1, mid + 1, tr, l, r, value);

		tree[v].sum = (tree[2 * v].sum + tree[2 * v + 1].sum);
	}

	node get(int v, int tl, int tr, int l, int r) {
		push(v, tl, tr);
		if (l >= tr || tl >= r)
			return node();
		if (l <= tl && tr <= r) {
			return tree[v];
		}
		int mid = (tl + tr) / 2;
		auto left = get(2 * v, tl, mid, l, r);
		auto right = get(2 * v + 1, mid + 1, tr, l, r);

		return node {
			.sum = (left.sum + right.sum),
			.promise = NONE
		};
	}
};
