#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;

template <class meta>
struct segment_tree {
    vector<meta> data;
    segment_tree(int _n = 1) : data(4 << __lg(_n)) {}
    inline int lson(int p) { return p * 2 + 1; }
    inline int rson(int p) { return p * 2 + 2; }
    void push(int p, int l, int r) {
        int m = (l + r) >> 1;
        data[lson(p)].upd(data[p], l, m);
        data[rson(p)].upd(data[p], m, r);
        data[p].cls();
    }
    meta pull(meta lhs, meta rhs) {
        return meta{max(lhs.val, rhs.val)};
    }
    void set(int l, int r, auto&& call, int p = 0) {
        if (l + 1 == r) return data[p] = call(l), void();
        int m = (l + r) >> 1;
        set(l, m, call, lson(p));
        set(m, r, call, rson(p));
        data[p] = pull(data[lson(p)], data[rson(p)]);
    }
    void upd(int l, int r, int L, int R, const meta& x, int p = 0) {
        if (R <= l || r <= L) return;
        if (L <= l && r <= R) return data[p].upd(x, l, r);
        push(p, l, r);
        int m = (l + r) >> 1;
        upd(l, m, L, R, x, lson(p));
        upd(m, r, L, R, x, rson(p));
        data[p] = pull(data[lson(p)], data[rson(p)]);
    }
    meta ask(int l, int r, int L, int R, int p = 0) {
        if (R <= l || r <= L) return meta{};
        if (L <= l && r <= R) return data[p];
        push(p, l, r);
        int m = (l + r) >> 1;
        return pull(ask(l, m, L, R, lson(p)), ask(m, r, L, R, rson(p)));
    }
    auto find_pref(int l, int r, int L, int R, meta& pref, auto&& check, int p = 0) {
        if (R <= l || r <= L) return R;
        if (L <= l && r <= R) {
            meta cur = pull(pref, data[p]);
            if (!check(cur)) return pref = move(cur), R;
            if ( l + 1 == r) return l;
        }
        push(p, l, r);
        int m = (l + r) >> 1;
        int res = find_pref(l, m, L, R, pref, check, lson(p));
        return res != R ? res : find_pref(m, r, L, R, pref, check, rson(p));
    }
    auto find_suff(int l, int r, int L, int R, meta& suff, auto&& check, int p = 0) {
        if (R <= l || r <= L) return L - 1;
        if (L <= l && r <= R) {
            meta cur = pull(data[p], suff);
            if (!check(cur)) return suff = move(cur), L - 1;
            if ( l + 1 == r) return l;
        }
        push(p, l, r);
        int m = (l + r) >> 1;
        int res = find_suff(m, r, L, R, suff, check, rson(p));
        return res != L - 1 ? res : find_suff(l, m, L, R, suff, check, lson(p));
    }
};

struct meta {
    meta() {}
    void cls() { /* 清除懒标记 */ }
    void upd(const meta& x, int l, int r) { /* 更新当前节点 */ }
};