/**
 * Author: Vasyl Merenych
 * Date: 2023-12-07
 * License: CC0
 * Source: folklore
 * Description: Finds all articulation points.
 * Time: O(N + M)
 * Status: -
 */
#include <set>
#include <vector>
template<typename T>
using graph = std::vector<std::vector<T>>;

std::set<int> find_articulation_points(int n, graph<int> g) {
    std::vector<int> used(n), tin(n), fup(n);
    int T = 0;
    std::set<int> nodes;
    std::function<void(int, int)> dfs = [&](int v, int p = -1) {
        used[v] = true;
        tin[v] = fup[v] = T++;
        int cnt = 0;
        for (auto to : g[v]) {
            if (to == p)
                continue;
            if (used[to]) {
                fup[v] = min(fup[v], tin[to]);
            } else {
                dfs(to, v);
                fup[v] = min(fup[v], fup[to]);
                if (fup[to] >= tin[v] && p != -1) {
                    nodes.insert(v);
                }
                cnt++;
            }
        }

        if (cnt > 1 && p == -1)
            nodes.insert(v);
    };
    for (int i = 0; i < n; i++) {
        if (!used[i])
            dfs(i, -1);
    }
    return nodes;
}
