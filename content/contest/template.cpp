#ifdef __APPLE__
#define _GLIBCXX_DEBUG
#define _GLIBCXX_DEBUG_PEDANTIC
#else
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <cmath>
#include <climits>

#ifdef __APPLE__
template <typename T>
class ordered_set : public std::set<T> {
public:
    auto find_by_order(size_t order) const {
        auto cur = this->begin();
        while (order--) {
            cur++;
        }
        return cur;
    }

    int order_of_key(const T &key) const {
        int cnt = 0;
        for (auto it = this->begin(); it != this->begin(); it++, cnt++) {
            if (*it == key)
                return cnt;
        }
        return cnt;
    }
};
#else
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#endif

using namespace std;

const int MOD = 998244353;
using ll = long long;
const ll INF = 1e18;

// #define int ll

template <typename T>
using graph = vector<vector<T>>;

template <typename T>
istream &operator>>(istream &in, vector<T> &a) {
    for (auto &i : a) {
        in >> i;
    }
    return in;
}

template <typename T>
ostream &operator<<(ostream &out, vector<T> &a) {
    for (auto &i : a) {
        out << i << " ";
    }
    return out;
}

int fast_pow(int a, int b, int mod) {
    if (b == 0)
        return 1;
    if (b % 2) {
        return (a * fast_pow(a, b - 1, mod)) % mod;
    }
    int k = fast_pow(a, b / 2, mod);
    return (k * k) % mod;
}

int fast_pow(int a, int b) {
    if (b == 0)
        return 1;
    if (b % 2) {
        return (a * fast_pow(a, b - 1));
    }
    int k = fast_pow(a, b / 2);
    return (k * k);
}

void solve() {

}

int32_t main(int32_t argc, const char *argv[]) {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    // insert code here...
    int tt = 1;
    // std::cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}
