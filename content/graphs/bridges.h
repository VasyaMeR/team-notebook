/**
 * Author: Vasyl Merenych
 * Date: 2023-12-07
 * License: CC0
 * Source: folklore
 * Description: Finds all bridges in the undirected graph.
 * Time: O(N + M)
 * Status: -
 */


#include <vector>
template<typename T>
using graph = std::vector<std::vector<T>>;

std::vector<std::pair<int, int>> find_bridges(int n, graph<int> g) {
    std::vector<int> used(n), tin(n), fup(n);
    int T = 0;
    std::vector<std::pair<int, int>> edges;
    std::function<void(int, int)> dfs = [&](int v, int p = -1) {
        used[v] = true;
        tin[v] = fup[v] = T++;
        for (auto to : g[v]) {
            if (to == p)
                continue;
            if (used[to]) {
                fup[v] = min(fup[v], tin[to]);
            } else {
                dfs(to, v);
                fup[v] = min(fup[v], fup[to]);
                if (fup[to] ==  tin[to]) {
                    edges.push_back({v, to});
                }
            }
        }
    };
    for (int i = 0; i < n; i++) {
        if (!used[i])
            dfs(i, -1);
    }
    return edges;
}
