/**
 * Author: Vasyl Merenych
 * Date: 2024-03-16
 * License: CC0
 * Source: folklore
 * Description: Polynomial hashes for strings
 * Time: O(n * log(M)), n - size of string s, m - module
 * Status: -
 */

template<int P, int MOD>
struct hash_st {
    int n;
    vector<int> hash_, rev_, p, rev_p;
    hash_st(string s) {
        n = s.size();
        hash_.resize(n);
        rev_.resize(n);
        p.resize(n);
        rev_p.resize(n);

        p[0] = 1;
        rev_p[0] = 1;
        for (int i = 1; i < n; i++) {
            p[i] = (p[i - 1] * P) % MOD;
            rev_p[i] = fast_pow(p[i], MOD - 2, MOD);
        }

        int last = 0;
        for (int i = 0; i < n; i++) {
            hash_[i] = (last + p[i] * (s[i] - 'a' + 1)) % MOD;
            last = hash_[i];
        }
        last = 0;
        for (int i = n - 1; i >= 0; i--) {
            rev_[i] = (last + p[n - 1 - i] * (s[i] - 'a' + 1)) % MOD;
            last = rev_[i];
        }
    }

    int get(int l, int r) {
        r--;
        if (l == 0)
            return hash_[r];
        int x = (MOD + hash_[r] - hash_[l - 1]) % MOD;
        return (x * rev_p[l]) % MOD;
    }

    int get_rev(int l, int r) {
        r--;
        if (r == n - 1)
            return rev_[l];
        int x = (MOD + rev_[l] - rev_[r + 1]) % MOD;
        int st = n - 1 - r;
        return (x * rev_p[st]) % MOD;
    }
};
