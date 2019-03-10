#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
#define SZ(v) ((ll)(v).size())  
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(ll i=(a);i<=(b);++i)  

struct solver {
    ll n, k;
    vector<ll> ai;
    ll ans;
    void doit(ll t) {
        read();
        solve();
        printf("Case #%lld: %lld\n", t, ans);
    }

    void read() {
        cin >> n >> k;
        ai.resize(n);
        REP(i,n) cin >> ai[i];
    }

    void solve() {
        sort(ai.begin(),ai.end());
        reverse(ai.begin(),ai.end());
        ll day = 0;
        ans = 0;
        while (!ai.empty()) {
            day++;
            while (!ai.empty() && ai.back() < day) ai.pop_back();
            if ((ll) ai.size() > k) {
                ans += k;
                REP(i,k) ai.pop_back();
            }
            else {
                ans += (ll) ai.size();
                ai.clear();
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
