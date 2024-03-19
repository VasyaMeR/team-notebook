/**
 * Author: Sashko123
 * Date: 2024-03-19
 * License: CC0
 * Source: library-checker
 * Description: for given n finds  all a, s.t. a*a = n (mod p) 
 * Time: O(log^2(p))
 * Status: -
 */


unsigned xrand() {
  static unsigned x = 314159265, y = 358979323, z = 846264338, w = 327950288;
  unsigned t = x ^ x << 11; x = y; y = z; z = w; return w = w ^ w >> 19 ^ t ^ t >> 8;
}

int jacobi(ll a, ll m) {
  int s = 1;
  if (a < 0) a = a % m + m;
  for (; m > 1; ) {
    a %= m;
    if (a == 0) return 0;
    const int r = __builtin_ctz(a);
    if ((r & 1) && ((m + 2) & 4)) s = -s;
    a >>= r;
    if (a & m & 2) s = -s;
    std::swap(a, m);
  }
  return s;
}

vector<ll> mod_sqrt(ll a, ll p) {
  if (p == 2) return {a & 1};
  const int j = jacobi(a, p);
  if (j == 0) return {0};
  if (j == -1) return {};
  ll b, d;
  for (; ; ) {
    b = xrand() % p;
    d = (b * b - a) % p;
    if (d < 0) d += p;
    if (jacobi(d, p) == -1) break;
  }
  ll f0 = b, f1 = 1, g0 = 1, g1 = 0, tmp;
  for (ll e = (p + 1) >> 1; e; e >>= 1) {
    if (e & 1) {
      tmp = (g0 * f0 + d * ((g1 * f1) % p)) % p;
      g1 = (g0 * f1 + g1 * f0) % p;
      g0 = tmp;
    }
    tmp = (f0 * f0 + d * ((f1 * f1) % p)) % p;
    f1 = (2 * f0 * f1) % p;
    f0 = tmp;
  }
  return (g0 < p - g0) ? vector<ll>{g0, p - g0} : vector<ll>{p - g0, g0};
}
