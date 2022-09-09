/**
 * Author: Vasyl Merenych
 * Date: 2022-09-09
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed sum-tree. Bounds are inclusive to the left and to the right.
 * Time: update - O(\log N), get - O(\log N)
 * Status: -
 */
#pragma once

#include <vector>

struct segment_tree {
	struct node{
		int val = 0;
		node *left = nullptr;
		node *right = nullptr;
	};

	node* new_node() {
		const int SZ = 100000;
		static node *block;
		static int count = SZ;

		if (count == SZ) {
			block= new node[SZ];
			count = 0;
		} 
		return (block + count++);
	};

	const int N = 100000;
	void update(int pos, int val) {
		update(root, 0, N, pos, val);
	}

	int get(int l, int r) {
		return get(root, 0, N, l, r);
	}
	node *root = new_node();

	void update(node*& v, int tl, int tr, int pos, int value) {
		if (!v)
			v = new_node();
		if (tl == tr) {
			v->val += value;
			return;
		}
		int mid = (tl + tr) / 2;
		if (pos <= mid)
			update(v->left, tl, mid, pos, value);
		else
			update(v->right, mid + 1, tr, pos, value);
		v->val = (v->left ? v->left->val : 0) + (v->right ? v->right->val : 0);
	}

	int get(node*& v, int tl, int tr, int l, int r)
	{
		if (!v || r < tl || tr < l)
			return 0;
		if (l <= tl && tr <= r)
			return v->val;
		int mid = (tl + tr) / 2;
		return get(v->left, tl, mid, l, r) + get(v->right, mid + 1, tr, l, r);
	}
};
