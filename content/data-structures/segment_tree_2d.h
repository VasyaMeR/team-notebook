/**
 * Author: Vasyl Merenych
 * Date: 2023-12-07
 * License: CC0
 * Source: peltorator
 * Description: 2D segment tree, update(+=) at element, sum at segment. R is excluded.
 * Time: update - O(\log N * \log M), get - O(\log N * \log M)
 * Status: -
 */

template<typename T>
struct segment_tree_2d {
    int n, m;
    vector<vector<T>> tree;
 
    segment_tree_2d(const vector<vector<T>>& arr) {
        n = arr.size();
        m = arr[0].size();
        tree.assign(2 * n, vector<T>(2 * m));
        for (int i = 2 * n - 1; i > 0; i--) {
            for (int j = 2 * m - 1; j > 0; j--) {
                if (i < n) {
                    tree[i][j] = tree[2 * i][j] + tree[2 * i + 1][j];
                } else if (j < m) {
                    tree[i][j] = tree[i][2 * j] + tree[i][2 * j + 1];
                } else {
                    tree[i][j] = arr[i - n][j - m];
                }
            }
        }
    }
 
    void update_point(int x, int y, T newval) { // arr[x][y] := newval
        x += n;
        y += m;
        int curx = x;
        while (curx > 0) {
            int cury = y;
            while (cury > 0) {
                if (curx < n) {
                    tree[curx][cury] = tree[2 * curx][cury] + tree[2 * curx + 1][cury];
                } else if (cury < m) {
                    tree[curx][cury] = tree[curx][2 * cury] + tree[curx][2 * cury + 1];
                } else {
                    tree[curx][cury] = newval;
                }
                cury >>= 1;
            }
            curx >>= 1;
        }
    }
 
    T find_sum(int lx, int rx, int ly, int ry) { // [lx, rx) * [ly, ry)
        lx += n;
        rx += n;
 
        T ans = 0;
        while (lx < rx) {
            int curly = ly + m;
            int curry = ry + m;
            while (curly < curry) {
                if (curly & 1) {
                    if (lx & 1) {
                        ans += tree[lx][curly];
                    }
                    if (rx & 1) {
                        ans += tree[rx - 1][curly];
                    }
                }
                if (curry & 1) {
                    if (lx & 1) {
                        ans += tree[lx][curry - 1];
                    }
                    if (rx & 1) {
                        ans += tree[rx - 1][curry - 1];
                    }
                }
                curly = (curly + 1) >> 1;
                curry >>= 1;
            }
            lx = (lx + 1) >> 1;
            rx >>= 1;
        }
        return ans;
    }
};
