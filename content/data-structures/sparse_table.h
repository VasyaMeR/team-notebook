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

struct sparse_table {
    static const int K = 20;
    std::array<std::array<T, N>, K> ar;
    static std::array<int, N + 1> lg;
    
    sparse_table(int n, const vector<T>& a) {
        lg[1] = 0;
        for (int i = 2; i <= N; i++)
            lg[i] = lg[i >> 1] + 1;
    
        for (int i = 0; i < n; i++)
            ar[0][i] = a[i];

        for (int k = 0; k + 1 < K; k++) {
            for (int i = 0; i + (1 << k) < N; i++) {
                ar[k + 1][i] = min(ar[k][i], ar[k][i + (1 << k)]);
            }
        }
    }

    T get(int l, int r) {
        assert(0 <= l < N && l < r && r <= N);
        int power = lg[r - l];
        return min(ar[power][l], ar[power][r - (1 << power)]);
    }
};
