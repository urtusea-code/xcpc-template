#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;

using CP = complex<double>;
constexpr double PI = numbers::pi;

struct fft_base : vector<CP> {
    static inline int m;
    static inline double inv_m;
    static inline vector<CP> rpt;
    static inline vector<int> rev;

    fft_base(int _n = 0) : vector<CP>(_n) {}

    void init(int M) {
        for (m = 1; m < M; m <<= 1);
        inv_m = 1.0 / m;
        rev.resize(m), rpt.resize(m);
        for (int i = 1; i < m; i <<= 1) {
            rpt[i] = 1;
            for (int j = 1; j < i; j++)
                rpt[i + j] = polar(1.0, PI * j / i);
        }
        for (int i = 1; i < m; i++) {
            rev[i] = (rev[i >> 1] >> 1) | (((i & 1) * m) >> 1);
        }
    }
    void dft() {
        auto& t = *this; t.resize(m);
        for (int i = 1; i < m; i++)
            if (i < rev[i]) std::swap(t[i], t[rev[i]]);
        for (int i = 1; i < m; i <<= 1) {
            for (int j = 0; j < m; j += i << 1) {
                for (int k = 0; k < i; k++) {
                    CP x = t[i + j + k] * rpt[i + k];
                    t[i + j + k] = t[j + k] - x;
                    t[j + k] += x;
                }
            }
        }
    }
    void idft() {
        dft(); auto& t = *this; reverse(t.begin() + 1, t.end());
        for (int i = 0; i < m; i++) t[i] *= inv_m;
    }
    friend fft_base operator* (fft_base lhs, fft_base rhs) {
        fft_base{}.init(lhs.size() + rhs.size() - 1);
        lhs.dft();
        rhs.dft();
        for (int i = 0; i < m; i++) lhs[i] *= rhs[i];
        lhs.idft(); return lhs;
    }
};