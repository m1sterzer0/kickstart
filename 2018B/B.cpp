#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;
#define PB push_back  
#define MP make_pair  
#define SZ(v) ((ll)(v).size())  
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(ll i=(a);i<=(b);++i)  
#define REPE(i,n) FORE(i,0,n)  
#define FORSZ(i,a,v) FOR(i,a,SZ(v))  
#define REPSZ(i,v) REP(i,SZ(v)) 

struct constraint { ll a; ll b; ll c; };
bool operator<(const constraint &a, const constraint &b) { return a.a < b.a; }

void solve(ll t) {
    ll n, k, p; cin >> n >> k >> p;
    vector<constraint> cc(k);
    REP(i,k) { cin >> cc[i].a >> cc[i].b >> cc[i].c; cc[i].a--; cc[i].b--; }
    sort(cc.begin(),cc.end());
    ll mymax = 1000000000000000001LL;
    vector<vector<ll>> dp(n);

    ll lmax = 2;
    for (auto &p : cc) {
        ll next = 1LL << (p.b - p.a + 1);
        if (next > lmax) lmax = next;
    }
    ll lmask = lmax - 1;
    vector<ll> onecount(lmax, 0LL);

    onecount[0] = 0;
    onecount[1] = 1;
    FOR(i,2,lmax) { onecount[i] = onecount[i & 1] + onecount[i >> 1]; }

    for (ll i = n-1; i >= 0; i--) {
        dp[i].assign(lmax,1LL);
        while (!cc.empty() && cc.back().b == i) {
            ll n1 = cc.back().c;
            ll clen = cc.back().b - cc.back().a + 1;
            ll mask = (1 << clen) - 1;
            REP(j,lmax) { if (onecount[j & mask] != n1) dp[i][j] = 0; }
            cc.pop_back();
        }
        if (i != n-1) {
            REP(j,lmax) { 
                if (dp[i][j] == 0) continue;
                dp[i][j]  = dp[i+1][((j << 1) & lmask)    ];
                dp[i][j] += dp[i+1][((j << 1) & lmask) + 1];
                if (dp[i][j] > mymax) dp[i][j] = mymax;
            }
        } 
    }

    string s;
    ll pp = p;
    ll mask = 0;
    REP(i,n) {
        if (dp[i][mask] >= pp) { s += '0'; }
        else                   { s += '1'; pp -= dp[i][mask]; mask++; }
        mask = (mask << 1) & lmask;
    }

    printf("Case #%lld: %s\n", t, s.c_str());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("B.in","r",stdin);
    ll t; cin >> t;
    FORE(i,1,t) solve(i);
    return 0;
}
