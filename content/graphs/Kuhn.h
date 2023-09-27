/**
 * Author: Merenych Vasyl
 * Date: 2023-01-20
 * License: CC0
 * Source: folklore
 * Description: Fast pair matching algorithm
 * Time: O(n * (n + m))
 * Status: -
 */


graph<int> g;
vector<int> mt, used, rev_mt;
bool dfs(int v) {
    if (used[v] == 1)
        return false;
    used[v] = 1;
    for (auto to : g[v]) {
        if (mt[to] == -1) {
            rev_mt[v] = to;
            mt[to] = v;
            return true;
        }
    }
    for (auto to : g[v]) {
        if (dfs(mt[to])) {
            rev_mt[v] = to;
            mt[to] = v;
            return true;
        }
    }
    return false;
}

void pair_matching() {
    for (int it = 0; ; it++) {
        bool finded = false;
        used.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (rev_mt[i] == -1 && dfs(i)) {
                cnt++;
                finded = true;
            }
        }
        if (!finded) {
            break;
        }
    }
}
