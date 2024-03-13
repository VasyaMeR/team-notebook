
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
	struct node {
		T sum;
		int left, right;

		node(T val = T()): sum(val), left(-1), right(-1) {}
		node(int left_, int right_): sum(T()), left(left_), right(right_) {}
	};
	std::vector<node> tree;

	node create_node(T val = 0) {
		return node(val);
	}
	node create_node(int left, int right) {
		auto v = node(left, right);
		v.sum = (left != -1 ? tree[left].sum : 0) + (right != -1 ? tree[right].sum : 0);
		
		return v;
	}
	int LAST = 0;
	template<typename... params>
	int new_node(params... args) {
		tree[++LAST] = create_node(args...);
		return LAST;
	}
	int n;
	persistent_segment_tree(int n_, int sz_, const vector<T>& a, int& first_root): n(n_) {
		tree.resize(sz_);
		first_root = build(0, n, a);
	}

	int build(int l, int r, const vector<T>& a) {
		if (l + 1 == r) {
			return new_node(a[l]);
		}
		int mid = (r + l) / 2;
		int left = build(l, mid, a);
		int right = build(mid, r, a);
		return new_node(left, right);
	}

	int update(int root, int pos, T val) {
		return update(root, 0, n, pos, val);
	}

	T get(int root, int l, int r) {
		return get(root, 0, n, l, r);
	}

	T get(int root, int pos) {
		return get(root, 0, n, pos, pos + 1);
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

	T get(int v, int tl, int tr, int l, int r) {
		if (tr <= l || r <= tl)
			return 0;
		if (l <= tl && tr <= r) {
			return tree[v].sum;
		}

		int mid = (tl + tr) / 2;
		return get(tree[v].left, tl, mid, l, r) + get(tree[v].right, mid, tr, l, r);
	}
};
