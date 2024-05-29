/**
 * Author: Vasya Merenych
 * Date: 2024-03-19
 * License: CC0
 * Source: folklore
 * Description: Single source shortest path with negative weight edges in dirceted graph
 * Time: O(n * m) 
 * Status: -
 */

vector<int> d(n, INF);
d[v] = 0;
vector<int> p(n, -1);

for (;;) {
	bool any = false;
	for (Edge e : edges)
		if (d[e.a] < INF)
			if (d[e.b] > d[e.a] + e.cost) {
				d[e.b] = d[e.a] + e.cost;
				p[e.b] = e.a;
				any = true;
			}
	if (!any)
		break;
}