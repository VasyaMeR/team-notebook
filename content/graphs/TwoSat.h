struct TwoSat {
    graph<int> g, rev;
    vector<int> used, order, comp, ans;
    int n;
    
    TwoSat(int _n) {
        this->n = _n;
        g.assign(2 * n, {});
        rev.assign(2 * n, {});
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        rev[v].push_back(u);
    }

    void add_clause_or(int a, bool val_a, int b, bool val_b) {
        add_edge(a + val_a * n, b + !val_b * n);
        add_edge(b + val_b * n, a + !val_a * n);
    }

    void add_clause_xor(int a, bool val_a, int b, bool val_b) {
        add_clause_or(a, val_a, b, val_b);
        add_clause_or(a, !val_a, b, !val_b);
    }

    void add_clause_and(int a, bool val_a, int b, bool val_b) {
        add_clause_xor(a, !val_a, b, val_b);
    }

    void top_sort(int v) {
        used[v] = 1;
        for (auto to : g[v]) {
            if (!used[to])
                top_sort(to);
        }
        order.push_back(v);
    }

    void compress(int v, int id) {
        comp[v] = id;
        for (auto to : rev[v]) {
            if (comp[to] == -1)
                compress(to, id);
        }
    }

    bool satisfiable() {
        order.clear();
        used.assign(2 * n, 0);
        comp.assign(2 * n, -1);
        ans.assign(n, 0);
    
        for (int i = 0; i < 2 * n; i++) {
            if (!used[i])
                top_sort(i);
        }
        reverse(order.begin(), order.end());
        int id = 0;
        for (auto v : order) {
            if (comp[v] == -1)
                compress(v, id++);
        }

        for (int i = 0; i < n; i++) {
            if (comp[i] == comp[i + n])
                return false;
            ans[i] = (comp[i + n] < comp[i]);
        }
        return true;
    }
};
