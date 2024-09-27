/**
 * Author: Vasyl Merenych
 * Date: 2024-09-26
 * License: CC0
 * Source: folklore
 * Description: returns the array of indexes of points of convex-hull for given set of point in clockwise order.
 * Time: O(n * \log(n))
 * Status: -
 */

int is_left(pii a, pii b, pii c)
{
    b.first -= a.first;
    b.second -= a.second;

    c.first -= a.first;
    c.second -= a.second;

    return (1ll * b.first * c.second - 1ll * b.second * c.first) > 0;
}

#define PREV(a) a[a.size() - 2]
#define LAST(a) a[a.size() - 1]

vector<int> convex_hull(vector<pair<int, int>>&points)
{
    int n = points.size();
    vector<pair<pair<int, int>, int>>px(n);
    for(int i = 0;i < points.size();i++)
    {
        px[i] = {points[i], i};
    }
    sort(px.begin(), px.end());
    vector<int> up = {0}, down = {0};
    for (int i = 1; i < n; i++)
    {
        if (i == n - 1 || is_left(px[0].first, px.back().first, px[i].first))
        {
           while (up.size() >= 2 && is_left(px[PREV(up)].first, px[LAST(up)].first, px[i].first))
            {
                up.pop_back();
            }
            up.push_back(i);
        }
    }
    for (int i = 1; i < n; i++)
    {
        if (i == n - 1 || !is_left(px[0].first, px.back().first, px[i].first))
        {
            while (down.size() >= 2 && !is_left(px[PREV(down)].first, px[LAST(down)].first, px[i].first))
            {
                down.pop_back();
            }
            down.push_back(i);
        }
    }
    down.pop_back();
    for (int i = down.size() - 1; i > 0; i--)
        up.push_back(down[i]);
    for (int i = 0; i < up.size(); i++)
    {
        up[i] = px[up[i]].second;
    }
    return up;
}
