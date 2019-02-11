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

ll solveCase(ll n, ll mode) {
    ll nn = n;
    ll pv = 1;
    while (10*pv <= n) { pv *= 10; };
    while (pv) {
        ll digit = nn / pv;
        if (digit % 2 != 0) {
            if (mode == 0) { 
                ll adder = (digit+1) * pv - nn;
                return adder + solveCase(n+adder,mode);
            }
            else {
                ll subtrahend = nn - digit * pv + 1;
                return subtrahend + solveCase(n-subtrahend,mode); 
            } 
        }
        nn -= digit*pv;
        pv /= 10;
    }
    return 0LL;
}

void solve(ll t) {
    ll n; cin >> n;
    ll up = solveCase(n,0);
    ll down = solveCase(n,1);
    ll ans = min(up,down);    
    printf("Case #%lld: %lld\n",t, ans);
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
