/**
 * Author: Vasyl Merenych
 * Date: 2023-11-30
 * License: CC0
 * Source: folklore
 * Description: Persistent segment tree, update(+=) at segment, sum at segment. R is excluded.
 * Time: update - O(\log N), get - O(\log N)
 * Status: -
 */

#include <array>

template<typename T> struct persistent_segment_tree {
	static const int N = 1e5 + 100;
	static const int M = 1e6 + 100;

	struct node {
		T sum;
		int left, right;

		node(T val = T()): sum(val), left(-1), right(-1) {}
		node(int left_, int right_): sum(T()), left(left_), right(right_) {}
	};
	std::array<node, M> tree;

	node create_node(T val = 0) {
		return node(val);
	}
	node create_node(int left, int right) {
		auto v = node(left, right);
		v.sum = tree[left].sum + tree[right].sum;
		
		return v;
	}
	int LAST = 0;
	template<typename... params>
	int new_node(params... args) {
		tree[++LAST] = create_node(args...);
		return LAST;
	}

	void update(int pos, T val) {
		update(1, 0, N, pos, val);
	}

	node get(int l, int r) {
		return get(1, 0, N, l, r);
	}

	node get(int pos) {
		return get(1, 0, N, pos, pos + 1);
	}

	int update(int v, int l, int r, int pos, T val) {
		if (l + 1 == r) {
			return new_node(val + tree[v].sum);
		}

		int mid = (l + r) / 2;
		if (pos < mid) {
			return new_node(
				update(tree[v].left, l, mid, pos, val),
				tree[v].right
			);
		} else {
			return new_node(
				tree[v].left,
				update(tree[v].right, mid, r, pos, val)
			);
		}
	}

	node get(int v, int tl, int tr, int l, int r) {
		if (l <= tl && tr <= r) {
			return tree[v];
		}
		if (tr <= l || r <= tl)
			return 0;

		int mid = (tl + tr) / 2;
		return node {
			.sum = get(tree[v].left, tl, mid, l, r).sum + 
				get(tree[v].right, mid, tr, l, r).sum
		};
	}
};