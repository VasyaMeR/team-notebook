/**
 * Author: Merenych Vasyl
 * Date: 2022-11-28
 * License: CC0
 * Source: folklore
 * Description: NNT implementation by modulo 998244353
 * Time: (n + m) * log(n + m) 
 * Status: -
 */

#include <vector>
const int root = 31; // primitive root of module
const int root_1 = fast_pow(root, MOD - 2, MOD); // (primitive root) ^ -1
const int root_pw = 1 << 23; // max power of 2 in MOD - 1
 
inline int inverse(int n, int mod) {
	return fast_pow(n, mod - 2, mod);
}
 
void nnt(std::vector<int> &a, bool invert, int mod) {
    int n = a.size();
 
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
 
        if (i < j)
            std::swap(a[i], a[j]);
    }
 
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);
 
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i+j], v = (int)(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (1ll * w * wlen % mod);
            }
        }
    }
 
    if (invert) {
        int n_1 = inverse(n, mod);
        for (int& x : a)
            x = (1ll * x * n_1 % mod);
    }
}
 
std::vector<int> multiply(const std::vector<int>& a, const std::vector<int>& b, int mod) {
	int n = a.size(), m = b.size();
	int k = n + m - 1;
	int l = 1;
	while (l < k)
		l <<= 1;
	
	std::vector<int> A(l), B(l);
	for (int i = 0; i < n; i++) {
		A[i] = a[i];
	}
	for (int i = 0; i < m; i++) {
		B[i] = b[i];
	}
 
	nnt(A, false, mod);
	nnt(B, false, mod);
	for (int i = 0; i < B.size(); i++) {
		A[i] = (1ll * A[i] * B[i]) % mod;
	}
	nnt(A, true, mod);
	A.resize(k);
	return A;
}
