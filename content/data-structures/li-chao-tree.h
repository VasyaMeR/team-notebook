/**
 * Author: Vasyl Merenych
 * Date: 2023-02-11
 * License: CC0
 * Source: folklore
 * Description: Li-Chao tree, online convex hull for maximizing f(x) = k * x + b, for minimization use (-k) * x + (-b)
 * Time: add - O(\log N), get - O(\log N)
 * Status: -
 */

template<typename T> struct li_chao_tree {
	const T MX = 1e9 + 1;
	struct line {
		T k = 0;
		T b = -INF;

		T f(T x) const {
			return k * x + b;
		}
	};
	struct node {
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

	T get(T x) {
		return get(root, -MX, MX, x);
	}
    void add(line ln) {
        add(root, -MX, MX, ln);
    }

	T get(node*& v, T l, T r, T x) {
		if (!v || l > r) {
			return -INF;
		}
		T ans = v->ln.f(x);
		if (r == l) {
			return ans;
		}
		T mid = (r + l) / 2;
		if (x <= mid) {
			return max(ans, get(v->left, l, mid, x));
		} else {
          	return max(ans, get(v->right, mid + 1, r, x));
        }
	}

    void add(node*& v, T l, T r, line ln) {
		if (l > r)
			return;
        if (!v) {
            v = new_node();
        }
		T m = (r + l) / 2;
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