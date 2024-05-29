/**
 * Author: Vasyl Merenych
 * Date: 2023-12-07
 * License: CC0
 * Source: folklore
 * Description: 2d fenwick tree, update(+=) at element, sum at 2d segment. R is excluded.
 * Time: update - O(\log N * \log M), get - O(\log N * \log M)
 * Status: -
 */

template <class T> struct fenwick_tree_2d{
    struct fenwick_tree {
        int n;
        unordered_map<int, T> data;
        fenwick_tree(): n(0) {};
        fenwick_tree(int n): n(n) {};

        void add(int p, T x) {
            assert(0 <= p && p < n);
            p++;
            while (p <= n) {
                data[p - 1] += T(x);
                p += p & -p;
            }
        }
        
        T pref_sum(int r){
            T s = 0;
            while (r > 0) {
                s += data[r - 1];
                r -= r & -r;
            }
            return s;
        }
    };

	int n, m;
	std::vector<fenwick_tree> data;

	fenwick_tree_2d(int n,int m): n(n), m(m), data(n, fenwick_tree(m)) {};

	void add(int x, int y, T val) {
        assert(0 <= x && x < n);
		x++;
        while (x <= n) {
            data[x - 1].add(y, val);
            x += x & -x;
        }
	}

	T pref_sum(int xr, int yr){
        T s = 0;
        while (xr > 0) {
            s += data[xr - 1].pref_sum(yr);
            xr -= xr & -xr;
        }
        return s;
    }

    T sum(int xl, int yl, int xr, int yr) {
        return pref_sum(xr, yr) - pref_sum(xr, yl) - pref_sum(xl, yr) + pref_sum(xl, yl);
    }
};
