/**
 * Author: Merenych Vasyl
 * Date: 2022-11-28
 * License: CC0
 * Source: folklore
 * Description: FFT implementation
 * Time: (n + m) * log(n + m) 
 * Status: -
 */

#include <vector>
#include <complex>
using cd = std::complex<double>;

void fft(std::vector<cd> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

template<typename T>
std::vector<T> multiply(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    std::vector<T> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    result.resize(a.size() + b.size() - 1);
    return result;
}