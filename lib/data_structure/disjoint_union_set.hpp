#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;

struct DSU {
    vector<int> f;
    
    DSU(int _n = 0) : f(_n, -1) {}

    int find(int u) {
        return f[u] < 0 ? u : f[u] = find(f[u]);
    }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        f[u] < f[v] ?
        (f[u] += f[v], f[v] = u):
        (f[v] += f[u], f[u] = v);
        return true;
    }
};