/**
 * Author: Sashko123
 * Date: 2024-03-13
 * License: CC0
 * Source: folklore
 * Description: Finds eulerian path and cycle for undirected graph
 * Time: O(m * log m) 
 * Status: -
 */


#include <vector>
#include <set>

using namespace std;

struct eulerian_path
{
    vector<multiset<int>>graph;
    eulerian_path(vector<vector<int>>g)
    {
        graph.resize(g.size());
        for(int i=0;i<g.size();i++)
        {
            for(int j:g[i])
            {
                graph[i].insert(j);
            }
        }
    }

    void dfs(int u, vector<int>&cycle)
    {
        auto p = graph[u];
        for(int j:p)
        {
            if(graph[u].find(j) != graph[u].end())
            {
                graph[u].erase(graph[u].find(j));
                graph[j].erase(graph[j].find(u));
                dfs(j, cycle);
            }
        }
        cycle.push_back(u);
    }

    vector<int> find_cycle(int v = 0)
    {
        for(int i = 0;i < graph.size();i++)
        {
            if(graph[i].size() % 2)
                return {};
        }
        vector<int>cycle;
        dfs(v, cycle);
        return cycle;
    }

    vector<int> find_path()
    {
        int st = -1, fi = -1;
        for(int i = 0;i < graph.size();i++)
        {
            if(graph[i].size() % 2)
            {
                if(st == -1)
                    st = i;
                else
                if(fi == -1)
                    fi = i;
                else
                    return {};
            }
        }
        if(fi == -1)
        return {};
        graph[st].insert(fi);
        graph[fi].insert(st);
        auto cycle = find_cycle(st);
        vector<int>path;
        for(int i=0;;i++)
        {
            if(cycle[i] == st and cycle[i+1] == fi or cycle[i] == fi and cycle[i+1] == st)
            {
                for(int j = i + 1;j < cycle.size();j++)
                {
                    path.push_back(cycle[j]);
                }
                for(int j = 0;j < i;j++)
                {
                    path.push_back(cycle[j]);
                }
                break;
            }
        }
        return path;
    }

};