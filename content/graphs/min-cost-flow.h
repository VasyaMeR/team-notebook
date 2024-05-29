/**
 * Author: Vasyl Merenych
 * Date: 2024-03-15
 * License: CC0
 * Source: 
 * Description: Solves minimum-cost flow problem for specific flow value (or infinity).
 * Time: O(F * (n+m) * log(n+m)), where F is the amount of the flow and m is the number of added edges.
 * Status: -
 */

template<typename Cap, typename Cost>
struct mcf_graph
{
    struct mcf_edge {
        int from, to;
        Cap cap, flow;
        Cost cost;
        int back_id;
        int _id;
    };
    int n;
    vector<vector<mcf_edge>> g;
    mcf_graph(int n): n(n) {
        g.assign(n, {});
    }

    void add_edge(int from, int to, Cap cap, Cost cost, int _id = -1) {
        int id1 = g[from].size();
        int id2 = g[to].size();
        g[from].push_back(mcf_edge{
            .from = from,
            .to = to,
            .cap = cap,
            .flow = Cap(),
            .cost = cost,
            .back_id = id2,
            ._id = _id
        });

        g[to].push_back(mcf_edge{
            .from = to,
            .to = from,
            .cap = Cap(),
            .flow = Cap(),
            .cost = -cost,
            .back_id = id1,
            ._id = -1
        });
    }

    pair<Cap, Cost> flow(int s, int t, Cap target_flow) {
        Cap flow = Cap();
        vector<pair<int, int>> pred(n);
        vector<Cost> dist(n), dual(n, 0);
        auto shortests_path = [&](int s, int t) {
            pred.assign(n, {-1, -1});
            dist.assign(n, numeric_limits<Cost>::max());
            dist[s] = Cost();
            set<pair<int, int>> q;
            q.insert({dist[s], s});
        
            while (!q.empty()) {
                int v = q.begin()->second;
                q.erase(q.begin());
                
                for (int i = 0; i < g[v].size(); i++) {
                    mcf_edge& e = g[v][i];
                    if (e.flow >= e.cap)
                        continue;

                    Cost cost = e.cost - dual[e.to] + dual[v];
                    if (dist[e.to] > dist[v] + cost) {
                        q.erase({dist[e.to], e.to});
                        dist[e.to] = dist[v] + cost;
                        pred[e.to] = {v, i};
                        q.insert({dist[e.to], e.to});
                    }
                }
            }
            if (dist[t] == numeric_limits<Cost>::max())
                return false;
            for (int v = 0; v < n; v++) {
                if (dist[v] == numeric_limits<Cost>::max())
                    continue;
                dual[v] -= dist[t] - dist[v];
            }
    
            return true;
        };
        Cost total_cost = {};
        while (flow < target_flow) {
            if (!shortests_path(s, t))
                break;
            Cap f = target_flow - flow;
            int cur = t;
            while (cur != s) {
                auto [p, id] = pred[cur];
                mcf_edge& e = g[p][id];
                f = min(f, e.cap - e.flow);
                cur = p;
            }
            cur = t;
            while (cur != s) {
                auto [p, id] = pred[cur];
                mcf_edge& e = g[p][id];
                e.flow += f;
                g[e.to][e.back_id].flow -= f;
                cur = p;
            }
            Cost d = -dual[s];
            flow += f;
            total_cost += f * d;
        }
        return {flow, total_cost};
    }
};
