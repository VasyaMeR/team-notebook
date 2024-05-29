// #pragma comment(linker, "/stack:200000000")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4")
// #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
 
// #define _GLIBCXX_DEBUG
// #define _GLIBCXX_DEBUG_PEDANTIC
 
#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <functional>
#include <array>
#include <numeric>
#include <queue>
#include <deque>
#include <cmath>
#include <climits>

using namespace std;
  
const int MOD = 998244353;
const long double PI = 3.141592653589793;
using ll = long long;
const ll INF = 1e18;
 
// #define int ll

// --------> sashko123`s defines:

#define itn int     //Vasya sorry :(
#define p_b push_back
#define fi first
#define se second
#define pii std::pair<int, int>
#define oo LLONG_MAX
#define big INT_MAX
#define elif else if

int input()
{
    int x;
    cin>>x;
    return x;
}

// ----------> end of sashko123`s defines (thank you Vasya <3)

template<typename T>
using graph = vector<vector<T>>;
 
template<typename T>
istream& operator>>(istream& in, vector<T>& a) {
    for (auto& i: a) {
        in >> i;
    }
    return in;
}
 
ll fast_pow(ll a, ll b, ll mod) {
    if (b == 0)
        return 1;
    if (b % 2) {
        return (1ll * a * fast_pow(a, b - 1, mod)) % mod;
    }
    ll k = fast_pow(a, b / 2, mod);
    return (1ll * k * k) % mod;
    
}
 
ll fast_pow(ll a, ll b) {
    if (b == 0)
        return 1;
    if (b % 2) {
        return (1ll * a * fast_pow(a, b - 1));
    }
    ll k = fast_pow(a, b / 2);
    return (1ll * k * k);
}
 
void solve() {
    
}
 
int32_t main(int32_t argc, const char * argv[]) {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    // insert code here...
    int tt= 1;
    // std::cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}
