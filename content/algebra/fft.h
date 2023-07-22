
vector<complex<double>> fft(vector<complex<double>> a, bool inverse = true) {
    int n = a.size();
    if (n == 1) {
        return {a[0]};
    }

    int k = n / 2;
    vector<complex<double>> par(k), nepar(k);
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0)
            par[i / 2] = a[i];
        else
            nepar[i / 2] = a[i];
    }

    par = fft(par, inverse);
    nepar = fft(nepar, inverse);
    vector<complex<double>> ans(n);
    for (int i = 0; i < n; i++) {
        auto x = complex(cos(2 * i * PI / n), sin(2 * i * PI / n));
        if (inverse)
            x = complex(cos(2 * i * PI / n), sin(-2 * i * PI / n));
        ans[i] = par[i % k] + nepar[i % k] * x;
    }
    return ans;
}

vector<int> mult(vector<int> a, vector<int> b) {
    int n = a.size();
    int m = b.size();
    int k = n + m - 1;

    int l = 1;
    while (l < k)
    {
        l *= 2;
    }
    vector<complex<double>> A(l), B(l);
    for (int i = 0; i < n; i++)
        A[i] = a[i];
    for (int j = 0; j < m; j++)
        B[j] = b[j];
    A = fft(A, 0);
    B = fft(B, 0);

    for (int i = 0; i < l; i++) {
        A[i] *= B[i];
    }
    A = fft(A, 1);

    vector<int> ans(l);
    for (int i = 0; i < l; i++) {
        A[i] /= l;
        ans[i] = int(A[i].real() + 0.5);
    }
    return ans;
}
