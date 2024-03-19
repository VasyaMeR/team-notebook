/**
 * Author: Vasya Merenych
 * Date: 2024-03-13
 * License: CC0
 * Source: 
 * Description: Cartesian tree
 * Time: all get queries O(\log N)
 * Status: -
 */


struct Node {
    int val;
    int y;
    int l, r;
    int cnt;

    Node(int val = -1) {
        this->val = val;
        y = rand();
        l = -1;
        r = -1;
        cnt = 1;
    }
};
array<Node, 2 * N> tree;

int getCnt(int v) {
    if (v == -1)
        return 0;
    return tree[v].cnt;
} 

void upd(int v) {
    tree[v].cnt = getCnt(tree[v].l) + getCnt(tree[v].r) + 1;
}

pair<int, int> split(int v, int k) {
    if (v == -1)
        return {-1, -1};
    if (k == 0)
        return {-1, v};
    pair<int, int> res;
    if (getCnt(tree[v].l) >= k) {
        res = split(tree[v].l, k);
        tree[v].l = res.second;
        res.second = v;
    } else {
        res = split(tree[v].r, k - getCnt(tree[v].l) - 1);
        tree[v].r = res.first;
        res.first = v;
    }
    upd(v);
    return res;
}

int merge(int u, int v) {
    if (u == -1)
        return v;
    if (v == -1)
        return u;
    int res = -1;
    if (tree[u].y > tree[v].y) {
        res = merge(tree[u].r, v);
        tree[u].r = res;
        res = u;
    } else {
        res = merge(u, tree[v].l);
        tree[v].l = res;
        res = v;
    }
    upd(res);
    return res;
}