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

void solve(ll t) {
    ll n,o,d; cin >> n >> o >> d;
    ll x1, x2, a, b, c, m, l; cin >> x1 >> x2 >> a >> b >> c >> m >> l;
    vector<ll> s(n);
    vector<ll> x(n);
    x[0] = x1; x[1] = x2;
    FOR(i,2,n) x[i] = (a * x[i-1] + b * x[i-2] + c) % m;
    REP(i,n) s[i] = x[i] + l;


    vector<ll> prefixSum(n+1);
    prefixSum[0] = 0;
    FORE(i,1,n) prefixSum[i] = prefixSum[i-1] + s[i-1];


    ll best = LONG_LONG_MIN;
    ll tidx = 0;
    ll oddcnt = 0;
    multiset<ll> sums;
    sums.insert(0);
    REP(i,n) {
        if (x[i] & 1) oddcnt += 1;
        while (oddcnt > o) {
            auto itr = sums.find(prefixSum[tidx]);
            sums.erase(itr);
            if (s[tidx] & 1) oddcnt--;
            tidx++;
        }
        if (!sums.empty()) {
            auto it = sums.upper_bound(prefixSum[i+1] - d - 1);
            if (it != sums.end()) {
                best = max(best, prefixSum[i+1] - *it);
            }
        }
        sums.insert(prefixSum[i+1]);
    }
    if (best == LONG_LONG_MIN) printf("Case #%lld: IMPOSSIBLE\n", t);
    else                       printf("Case #%lld: %lld\n", t, best);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("A.in","r",stdin);
    ll t; cin >> t;
    FORE(i,1,t) solve(i);
    return 0;
}
