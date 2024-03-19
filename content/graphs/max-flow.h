
/**
 * Author: Vasyl Merenych
 * Date: 2024-03-13
 * License: CC0
 * Source: 
 * Description: Maximum flow problem
 * Time: O(min(n^{2/3} * m, m ^ {3 / 2})) - all capacities are 1, O(\min(n^2, m)) - general
 * Status: -
 */

template<typename Cap>
struct mf_graph {
    struct mf_edge {
        int from, to;
        Cap cap, flow;
        int back_id; 
        int _id;
    };
    int n;
    vector<vector<mf_edge>> g;
	bool need_clear = false;

    mf_graph(int n): n(n) {
        g.assign(n, {});
    }
    
    void add_edge(int from, int to, Cap cap, int id = -1) {
        int id1 = g[from].size();
        int id2 = g[to].size();

        g[from].push_back(mf_edge {
            .from = from,
            .to = to,
            .cap = cap,
            .flow = Cap(),
            .back_id = id2,
            ._id = id
        });
        g[to].push_back(mf_edge {
            .from = to,
            .to = from,
            .cap = Cap(),
            .flow = Cap(),
            .back_id = id1,
            ._id = -1
        });
    }

	void clear() {
		for (int i = 0; i < n; i++) {
			for (mf_edge& e: g[i])
				e.flow = Cap();
		}
	}

    Cap flow(int s, int t, Cap limit) {
		if (need_clear)
			clear();

        vector<int> dist(n, n + 1);
        auto bfs = [&](int s, int t) {
            dist.assign(n, n + 1);
            dist[s] = 0;
            deque<int> q;
            q.push_back(s);
            
            while (!q.empty())
            {
                int v = q.front();
                q.pop_front();

                for (mf_edge& e : g[v]) {
                    if (e.flow < e.cap && dist[e.to] == n + 1) {
                        dist[e.to] = dist[v] + 1;
                        q.push_back(e.to);
                    }
                }
            }

            return dist[t] != n + 1;
        };
        vector<int> lst(n);
        function<Cap(int, int, Cap)> dfs = [&](int v, int target, Cap F) {
            if (v == target)
                return F;

            Cap pushed = Cap();
            for (; lst[v] < g[v].size(); lst[v]++) {
                mf_edge& e = g[v][lst[v]];
                if (dist[e.to] == dist[v] + 1 && e.flow < e.cap) {
                    Cap x = dfs(e.to, target, min(F, e.cap - e.flow));

                    if (x) {
                        e.flow += x;
                        g[e.to][e.back_id].flow -= x;
                        pushed += x;
                        F -= x;
                    }
                }
            }
            return pushed;
        };

        Cap flow = 0;
        while (bfs(s, t)) {
            lst.assign(n, 0);
            while (Cap f = dfs(s, t, limit)) {
                flow += f;
            }
        }
		need_clear = true;
        return flow;
    }
};