/**
 * Author: Vasyl Merenych
 * Date: 2022-09-09
 * License: CC0
 * Source: peltorator
 * Description: Segment tree from below.
 * Time: update - O(\log N), get - O(\log N)
 * Status: -
 */

struct SegmentTree {
	static const int N = (1 << 18);
	array<int, N> tree;
	SegmentTree() {
		tree.fill(0);
	}

	void update(int pos, int val) {
		pos += N;
		tree[pos] = val;
		pos >>= 1;
		while (pos > 0) {
			tree[pos] = tree[pos << 1] + tree[(pos << 1) | 1];
			pos >>= 1;
		}
	}

	int get_sum(int l, int r) {
		l += N;
		r += N;
		r++;

		int ans = 0;
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
};
