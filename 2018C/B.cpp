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

struct solver {
    ll ans;
    ll runningSum;
    ll runningMax;
    ll n;
    ll t;
    vector<bool> taken;
    vector<vector<ll>> adjm;

    void doit(ll tin) {
        t = tin;
        read();
        ans = 0; runningSum = 0; runningMax = 0;
        taken.assign(n,false);
        REP(i,n-1) search(i);
        printf("Case #%lld: %lld\n", t, ans);
    }

    void read() {
        cin >> n;
        adjm.resize(n);
        REP(i,n) {
            adjm[i].assign(n,0LL);
            REP(j,n) { cin >> adjm[i][j]; }
        }
    }

    void search(ll i) {
        FOR(j,i+1,n) {
            if (adjm[i][j] == 0) continue;
            if (taken[j]) continue;
            taken[i] = true;
            taken[j] = true;
            runningSum += adjm[i][j];
            ll oldRunningMax = runningMax;
            if (adjm[i][j] > runningMax) runningMax = adjm[i][j];
            if (runningSum > 2 * runningMax) ans++;
            FOR(k,i+1,n-1) { if (!taken[k]) search(k); }
            runningMax = oldRunningMax;
            runningSum -= adjm[i][j]; 
            taken[i] = false;
            taken[j] = false;
        }
    }
};


void solve(ll t) {
    solver s;
    s.doit(t);
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
