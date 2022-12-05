/**
 * Author: Vasyl Merenych
 * Date: 2022-12-05
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed sum-tree with update on segment. Bounds are inclusive to the left and to the right.
 * Time: update - O(\log N), get - O(\log N)
 * Status: -
 */

#include <vector>
#include <iostream>
#include <array>

struct segment_tree {
	static const int N = 1e5 + 100;
	static const int NONE = -1;

	struct node{
		int mn = INT_MAX;
		int mx = INT_MIN;
		int promise = NONE;
	};
	array<node, 4 * N> tree; 

	void update(int l, int r, int val) {
		update(1, 0, N - 1, l, r, val);
	}

	node get(int l, int r) {
		return get(1, 0, N - 1, l, r);
	}

	void push(int v, int l, int r) {
		if (tree[v].promise == NONE)
			return;
		tree[v].mn = tree[v].mx = tree[v].promise;
		if (l != r) {
			tree[2 * v].promise = tree[v].promise;
			tree[2 * v + 1].promise = tree[v].promise;	
		}
		tree[v].promise = NONE;
	}

	void update(int v, int tl, int tr, int l, int r, int value) {
		push(v, tl, tr);
		if (l > tr || tl > r)
			return;
		if (l <= tl && tr <= r) {
			tree[v].promise = value;
			push(v, tl, tr);
			return;
		}
		int mid = (tl + tr) / 2;
		update(2 * v, tl, mid, l, r, value);
		update(2 * v + 1, mid + 1, tr, l, r, value);

		tree[v].mx = max(tree[2 * v].mx, tree[2 * v + 1].mx);
		tree[v].mn = min(tree[2 * v].mn, tree[2 * v + 1].mn);
	}

	node get(int v, int tl, int tr, int l, int r) {
		push(v, tl, tr);
		if (l > tr || tl > r)
			return node();
		if (l <= tl && tr <= r) {
			return tree[v];
		}
		int mid = (tl + tr) / 2;
		auto left = get(2 * v, tl, mid, l, r);
		auto right = get(2 * v + 1, mid + 1, tr, l, r);

		return node {
			.mn = min(left.mn, right.mn),
			.mx = max(left.mx, right.mx),
			.promise = NONE
		};
	}
};
