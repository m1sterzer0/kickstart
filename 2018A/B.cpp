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
    ll n, k; cin >> n >> k;
    vector<ll> v(n);
    REP(i,n) cin >> v[i];
    sort(v.begin(),v.end());

    double sum = 0.0;
    REP(i,n) sum += (double) v[i];
    ll trade = 0;
    double ev = 0.0;
    ev = ((double) trade * ev + sum) / (double) n;

    REP(i,k) {
        while (trade < n && (double) v[trade] < ev) { sum -= (double) v[trade]; trade++; }
        ev = ((double) trade * ev +  sum) / (double) n;
    } 
   
    printf("Case #%lld: %.15e\n",t, ev);
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
