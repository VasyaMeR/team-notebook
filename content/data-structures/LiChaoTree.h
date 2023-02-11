/**
 * Author: Vasyl Merenych
 * Date: 2023-02-11
 * License: CC0
 * Source: folklore
 * Description: Li-Chao tree, online convex hull for maximizing f(x) = k * x + b
 * Time: add - O(\log N), get - O(\log N)
 * Status: -
 */

struct line
{
	int k = 0;
	int b = -INF;

    int f(int x) const {
        return k * x + b;
    }
};


struct li_chao_tree {
	const int MX = 1e9 + 100;
	struct node
	{
		line ln;
		node* left = nullptr;
		node* right = nullptr;
	};

	node* new_node() {
		const int N = 100000;
		static node* block;
		static int count = N;

		if (count == N) {
			block= new node[N];
			count = 0;
		} 
		return (block + count++);
	};

	node* root = new_node();

	int get(int x) {
		return get(root, 0, MX, x);
	}
    void add(line ln) {
        return add(root, 0, MX, ln);
    }

	int get(node*& v, int l, int r, int x) {
		if (!v) {
			return -INF;
		}
		int ans = v->ln.f(x);
		if (r == l) {
			return ans;
		}
		int mid = (r + l) / 2;
		if (x <= mid) {
			return max(ans, get(v->left, l, mid, x));
		} else {
          	return max(ans, get(v->right, mid + 1, r, x));
        }
	}

    void add(node*& v, int l, int r, line ln) {
        if (!v) {
            v = new_node();
        }
        int m = (r + l) / 2;
        bool left = v->ln.f(l) < ln.f(l);
		bool md = v->ln.f(m) < ln.f(m);
        if (md)
            swap(v->ln, ln);
        if (l == r) {
            return;
        }
        if (left != md) {
            add(v->left, l, m, ln);
        } else {
            add(v->right, m + 1, r, ln);
        }
    }
};