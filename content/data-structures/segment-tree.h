/**
 * Author: Vasyl Merenych
 * Date: 2022-09-09
 * License: CC0
 * Source: peltorator
 * Description: Segment tree, update(+=) at element, sum at segment. R is excluded.
 * Time: update - O(\log N), get - O(\log N)
 * Status: -
 */

#include <array>

template<typename T, int N = (1 << 18)> struct segment_tree {
	std::array<T, 2 * N> tree;
	segment_tree() {
		tree.fill(T());
	}

	void update(int pos, T val) {
		pos += N;
		tree[pos] += val;
		pos >>= 1;
		while (pos > 0) {
			tree[pos] = tree[pos << 1] + tree[(pos << 1) | 1];
			pos >>= 1;
		}
	}

	T get_sum(int l, int r) {
		l += N;
		r += N;

		T ans = T();
		while (l < r) {
			if (l & 1) {
				ans += tree[l++];
			}
			if (r & 1) {
				ans += tree[--r];
			}
			l >>= 1;
			r >>= 1;
		}
		return ans;
	}

	T get(int pos) {
		return tree[N + pos];
	}
};