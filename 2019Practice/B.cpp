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
    ll n; cin >> n;
    string s; cin >> s;
    vector<ll> prefixSum(n+1,0);
    REP(i,n) prefixSum[i+1] = prefixSum[i] + (s[i]-'0');
    ll seglen = (n+1)/2;
    ll best = 0;
    for (ll i = 0; i + seglen <= n; i++) {
        best = max(best, prefixSum[i+seglen]-prefixSum[i]);
    }
    printf("Case #%lld: %lld\n", t, best);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    ll t; cin >> t;
    FORE(i,1,t) solve(i);
    return 0;
}
