/**
 * Author: Merenych Vasyl
 * Date: 2024-09-10
 * License: CC0
 * Source: folklore
 * Description: Calculate the proper edge coloring which gives the edge chromatic number on biparty graph. Returns colors from 1 to $D$, where $D = \max degree[v]$. $N$ - number of verices, $M$ - max degree.
 * Can be done for bipartite graphs by repeated matchings of max-degree nodes.
 * Time: O(n * m)
 * Status: -
 */

pair<int, int> has[2][N][M];
int color[M];
int c[2];
void dfs(int v, int p) {
	auto [to, ed] = has[p][v][c[!p]];
    
    if (has[!p][to][c[p]].second) 
        dfs(to, !p);
	else 
        has[!p][to][c[!p]] = {0,0};

	has[p][v][c[p]] = {to, ed};
	has[!p][to][c[p]] = {v, ed};
	color[ed] = c[p];
}

void colorize(vector<vector<int>> x) { // x[0], x[1] - edge
	for (int i = 0; i < x.size(); i++) {
		for (int d = 0; d < 2; d++) {
			for (c[d] = 1; has[d][x[d]][c[d]].second; c[d]++); // The smallest color that is free at the vertex x[d]
		}
		if (c[0] != c[1])
			dfs(x[1], 1);
		
		for (int d = 0; d < 2; d++)
			has[d][x[d]][c[0]] = {x[!d], i};
		color[i] = c[0];
	}
}
