#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;

template <int P>
struct ntt_base : vector<int> {
    static constexpr int N = 1 << 23;
    static inline int rev[N], rpt[N], m, inv_m;

    ntt_base(int _n = 0) : vector<int>(_n) {}
    
    int qpow(int a, int b) {
        int res = 1;
        for (; b; a = u64(a) * a % P, b >>= 1)
            if (b & 1) res = u64(res) * a % P;
        return res;
    }
    void init(int M) {
        for (m = 1; m < M; m <<= 1);
        inv_m = P - (P - 1) / m;
        for (int i = 1; i < m; i <<= 1) {
            rpt[i] = 1;
            for (int j = 1, w = qpow(3, P / i / 2); j < i; j++)
                rpt[i + j] = u64(rpt[i + j - 1]) * w % P;
        }
        for (int i = 1; i < m; i++) {
            rev[i] = (rev[i >> 1] >> 1) | (((i & 1) * m) >> 1);
        }
    }
    void dft() {
        static u64 a[N]; auto& t = *this; t.resize(m);
        for (int i = 0; i < m; i++) a[i] = t[rev[i]];
        for (int i = 1; i < m; i <<= 1) {
            if (i >> 18 & 1) for (int j = 0; j < m; j++) a[j] %= P;
            for (int j = 0; j < m; j += i << 1) {
                for (int k = 0; k < i; k++) {
                    u64 x = a[i + j + k] * rpt[i + k] % P;
                    a[i + j + k] = a[j + k] + (P - x);
                    a[j + k] += x;
                }
            }
        }
        for (int i = 0; i < m; i++) t[i] = a[i] % P;
    }
    void idft() {
        dft(); auto& t = *this; reverse(t.begin() + 1, t.end());
        for (int i = 0; i < m; i++) t[i] = u64(t[i]) * inv_m % P;
    }
    friend ntt_base operator* (ntt_base lhs, ntt_base rhs) {
        assert(lhs.size() && rhs.size());
        ntt_base{}.init(lhs.size() + rhs.size() - 1);
        lhs.dft();
        rhs.dft();
        for (int i = 0; i < m; i++) lhs[i] = u64(lhs[i]) * rhs[i] % P;
        lhs.idft(); return lhs;
    }
};