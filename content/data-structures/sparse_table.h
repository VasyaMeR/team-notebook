/**
 * Author: Vasyl Merenych
 * Date: 2023-12-07
 * License: CC0
 * Source: peltorator
 * Description: Min sparse table.
 * Time: build - O(N * \log N), get - O(1)
 * Status: -
 */

#include <cassert>
#include <array>
#include <vector>

template<typename T>
struct sparse_table {
    static const int K = 20;
    std::array<std::vector<T>, K> ar;
    std::vector<int> lg;
    int n;
    
    sparse_table(int n, const vector<T>& a): n(n) {
        lg.resize(n + 1)
        lg[1] = 0;
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i >> 1] + 1;
    
        ar[0] = a;

        for (int k = 0; k + 1 < K; k++) {
            ar[k + 1].resize(n);
            for (int i = 0; i + (1 << k) < n; i++) {
                ar[k + 1][i] = min(ar[k][i], ar[k][i + (1 << k)]);
            }
        }
    }

    T get(int l, int r) {
        assert(0 <= l < n && l < r && r <= n);
        int power = lg[r - l];
        return min(ar[power][l], ar[power][r - (1 << power)]);
    }
};
