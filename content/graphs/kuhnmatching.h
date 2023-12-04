/**
 * Author: Merenych Vasyl
 * Date: 2023-01-20
 * License: CC0
 * Source: folklore
 * Description: Fast pair matching algorithm
 * Time: O(n * (n + m))
 * Status: -
 */
#include <vector>
template<typename T>
using graph = std::vector<std::vector<T>>;

bool dfs(int v, graph<int>& g, std::vector<int>& mt, std::vector<int>& rev_mt, std::vector<int>& used) {
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
        if (dfs(mt[to], g, mt, rev_mt, used)) {
            rev_mt[v] = to;
            mt[to] = v;
            return true;
        }
    }
    return false;
}

std::vector<int> pair_matching(int n, int m, graph<int> g) {
    std::vector<int> mt(m, -1), used, rev_mt(n, -1);
    int cnt = 0;
    for (int it = 0; ; it++) {
        bool finded = false;
        used.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (rev_mt[i] == -1 && dfs(i, g, mt, rev_mt, used)) {
                cnt++;
                finded = true;
            }
        }
        if (!finded) {
            break;
        }
    }
}
