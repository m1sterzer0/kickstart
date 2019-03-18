#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
#define SZ(v) ((ll)(v).size())  
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(ll i=(a);i<=(b);++i)  

struct solver {
    ll ans;
    ll n;
    vector<ll> a;
    void doit(ll t) {
        read();
        solve();
        printf("Case #%lld: %lld\n", t, ans);
    }

    void read() {
        cin >> n;
        a.resize(n);
        REP(i,n) cin >> a[i];
    }

    void solve() {
        vector<ll> count(200001,0LL);
        vector<ll> values;
        sort(a.begin(),a.end());
        for (auto x : a) { if (count[x] == 0) values.push_back(x); count[x]++; }

        ans = 0;
        // Deal with the triple zeros
        if (count[0] >= 3) ans += (count[0]) * (count[0] - 1) * (count[0] - 2) / 6;

        // Deal with the double zeros
        if (count[0] >= 2) ans += (count[0]) * (count[0] - 1) / 2 * (n - count[0]); 

        // Deal with the triple ones
        if (count[1] >= 3) ans += (count[1]) * (count[1] - 1) * (count[1] - 2) / 6;

        // Deal with the single ones
        if (count[1] >= 1) {
            for (auto v : values) {
                if (v <= 1) continue;
                if (count[v] <= 1) continue;
                ans += (count[1]) * (count[v]) * (count[v]-1) / 2;
            }
        }

        // Deal with the doubles greater than 1
        for (auto v : values) {
            if (v <= 1) continue;
            if (count[v] <= 1) continue;
            ll x = v * v;
            if (x > 200000) break;
            if (count[x] == 0) continue;
            ans += (count[v]) * (count[v]-1) / 2 * count[x];
        }

        // Deal with the triples
        REP(i,(ll) values.size()-2) {
            ll vi = values[i];
            if (vi <= 1) continue;
            if (vi * vi > 200000) break;
            FOR(j, i+1, (ll) values.size()-1) {
                ll vj = values[j];
                ll x = vi * vj;
                if (x > 200000) break;
                if (count[x] == 0) continue;
                ans += count[vi] * count[vj] * count[x];
            }
        }
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
