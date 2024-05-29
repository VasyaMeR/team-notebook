/**
 * Author: Vasyl Merenych
 * Date: 2023-12-04
 * License: CC0
 * Source: cp-algorithms
 * Description: Finds divider of n.
 * Time: O(n ^ {1/4} * \log(n))
 * Status: -
 */

#include<numeric>

long long mult(long long a, long long b, long long mod) {
    return (__int128)a * b % mod;
}

long long f(long long x, long long c, long long mod) {
    return (mult(x, x, mod) + c) % mod;
}

long long rho(long long n, long long x0=2, long long c=1) {
    long long x = x0;
    long long y = x0;
    long long g = 1;
    while (g == 1) {
        x = f(x, c, n);
        y = f(y, c, n);
        y = f(y, c, n);
        g = std::gcd(abs(x - y), n);
    }
    return g;
}
