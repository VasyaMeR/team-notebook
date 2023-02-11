/**
 * Author: Merenych Vasyl
 * Date: 2023-01-20
 * License: CC0
 * Source: folklore
 * Description: Dinitz algorithm, finds max flow in network
 * Time: O(V^2 * E)
 * Status: -
 */

struct Edge {
	int from, to;
	int cap, flow;
	Edge(int from_, int to_, int cap_): from(from_), to(to_), cap(cap_), flow(0) {}

	int other(int v) const {
		if (v == from)
			return to;
		return from;
	}
	int capacity(int v) const {
		if (v == from)
			return (cap - flow);
		return flow;
	}
	void add(int df, int v) {
		if (v == from) {
			flow += df;
		} else {
			flow -= df;
		}
	}
};

vector<int> dinitz_bfs(int v, const graph<Edge*>& g) {
	int n = g.size();
	vector<int> dist(n, n + 100);
	dist[v] = 0;
	queue<int> q;
	q.push(v);

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		for (auto& e : g[v]) {
			int to = e->other(v);
			if (!e->capacity(v))
				continue;
			if (dist[to] > n) {
				dist[to] = dist[v] + 1;
				q.push(to);
			}
		}
	}
	return dist;
}
vector<bool> blocked;
vector<int> dist;
int dinitz_dfs(int v, int F, graph<Edge*>& g, int t) {
	if (v == t || F == 0)
		return F;
	bool all_blocked = true;
	int pushed = 0;
	for (auto& e : g[v]) {
		int to = e->other(v);
		if (dist[to] != dist[v] + 1)
			continue;
		
		if (e->capacity(v) && !blocked[to]) {	 		
			int df = dinitz_dfs(to, min(F, e->capacity(v)), g, t);
			e->add(df, v);
			pushed += df;
			F -= df;
		}

		if (!blocked[to] && e->capacity(v))
			all_blocked = false;
	}

	if (all_blocked)
		blocked[v] = true;
	return pushed;
}
	
while (true) {
	dist = dinitz_bfs(s, g);

	if (dist[t] > dist.size())
		break;

	blocked.assign(dist.size(), false);
	dinitz_dfs(s, INF, g, t);
}
