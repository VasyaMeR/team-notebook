/**
 * Author: Sashko123
 * Date: 2024-03-16
 * License: CC0
 * Source: cp algorithms
 * Description: checks whether given number (up to 1e18) is prime
 * Time: +- O(log^3(n))
 * Status: Tested
 */

using u128 = __uint128_t;

ll fast_pow(ll a, ll b, ll mod) {
    if (b == 0)
        return 1;
    if (b % 2) {
        return ((u128) a * fast_pow(a, b - 1, mod)) % mod;
    }
    ll k = fast_pow(a, b / 2, mod);
    return ((u128) k * k) % mod;
}

bool check_composite(ll n, ll a, ll d, int s) {
    ll x = fast_pow(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool miller_rabin(ll n) { 
    if (n < 2)
        return false;

    int r = 0;
    ll d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}
