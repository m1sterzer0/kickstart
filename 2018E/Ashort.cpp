#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
#define SZ(v) ((ll)(v).size())  
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(ll i=(a);i<=(b);++i)  


struct pileSum {ll p1, p2, p3, idx;};

struct solver {
    ll n;
    vector<ll> a;
    vector<ll> b;
    vector<pileSum> acomb;
    vector<pileSum> bcomb;

    // Scratch for the dfs
    ll cnt1, cnt2, cnt3;
    ll sum1, sum2, sum3;
    ll n3;

    void doit(ll t) {
        read();
        cnt1 = n; cnt2 = n; cnt3 = n;
        sum1 = 0; sum2 = 0; sum3 = 0;
        n3 = 3 * n;
        dfs(a,acomb,0);
        dfs(b,bcomb,0);
        ll best = 0;
        for (auto &aa : acomb) {
            ll running = 0;
            for (auto &bb : bcomb) {
                ll s = 0;
                if (aa.p1 > bb.p1) s++;
                if (aa.p2 > bb.p2) s++;
                if (aa.p3 > bb.p3) s++;
                if (s >= 2) running++;
            }
            if (running > best) best = running;
        }
        ll denom = (ll) bcomb.size();
        double ans = (double) best / (double) denom;
        printf("Case #%lld: %.12f\n", t, ans);
    }

    void read() {
        cin >> n;
        a.resize(3*n);
        b.resize(3*n);
        REP(i,3*n) cin >> a[i];
        REP(i,3*n) cin >> b[i];
    }

    void dfs(vector<ll> &a, vector<pileSum> &acomb, ll idx) {
        if (idx == n3) { acomb.push_back({sum1,sum2,sum3, 0}); return; }
        if (cnt1 > 0) { sum1 += a[idx]; cnt1--; dfs(a, acomb, idx+1); cnt1++; sum1 -= a[idx]; }
        if (cnt2 > 0) { sum2 += a[idx]; cnt2--; dfs(a, acomb, idx+1); cnt2++; sum2 -= a[idx]; }
        if (cnt3 > 0) { sum3 += a[idx]; cnt3--; dfs(a, acomb, idx+1); cnt3++; sum3 -= a[idx]; }
    }

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("A.in","r",stdin);
    ll t; cin >> t;
    FORE(i,1,t) { solver ss; ss.doit(i); }
    return 0;
}
