/**
 * Author: Merenych Vasyl
 * Date: 2023-01-20
 * License: CC0
 * Source: folklore
 * Description: Fast pair matching algorithm. To find the minimum vertex cover start dfs from each vertice in the left that is not in maximum matching, from the left side choce unvisited vertices and from right chose visited.
 * Time: O(n * (n + m))
 * Status: -
 */
#include <vector>
#include <utility>
using namespace std;

template<typename T>
using graph = vector<vector<T>>;

bool dfs(int v, graph<int>& g, vector<int>& mt, vector<int>& rev_mt, vector<int>& used) {
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

pair<int, vector<int>> pair_matching(int n, int m, graph<int> g) {
    vector<int> mt(m, -1), used, rev_mt(n, -1);
    int cnt = 0;
    for (int it = 0; ; it++) {
        bool found = false;
        used.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (rev_mt[i] == -1 && dfs(i, g, mt, rev_mt, used)) {
                cnt++;
                found = true;
            }
        }
        if (!found) {
            break;
        }
    }
    return {cnt, mt};
}
