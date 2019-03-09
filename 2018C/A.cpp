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
    ll n;
    ll t;
    vector<vector<ll>> adj;
    vector<ll> par;
    vector<ll> color; // from https://cp-algorithms.com/graph/finding-cycle.html
    vector<ll> ans;
    vector<ll> cycle;
    ll cycle_start;
    ll cycle_end;

    void doit(ll tin) {
        t = tin;
        read();
        findCycle();
        fillInAns();
        printf("Case #%lld:", t);
        FORE(i,1,n) printf(" %lld", ans[i]);
        printf("\n");
    }

    void read() {
        cin >> n;
        adj.resize(n+1);
        REP(i,n) { ll x,y; cin >> x >> y; adj[x].push_back(y); adj[y].push_back(x); }
    }

    void findCycle() {
        color.assign(n+1,0);
        par.assign(n+1,-1);
        cycle_start = -1;
        //FORE(i,1,n) { if (dfs1(i)) break; }
        dfs1(1,-1);
        for (ll v = cycle_end; v != cycle_start; v = par[v]) cycle.push_back(v);
        cycle.push_back(cycle_start); 
    }

    bool dfs1(ll v, ll p) {
        color[v] = 1;
        for (auto u : adj[v]) {
            if (u == p) continue;
            if (color[u] == 0) {
                par[u] = v;
                if (dfs1(u,v)) return true;
            }
            else if (color[u] == 1) {
                cycle_end = v;
                cycle_start = u;
                return true;
            }
        }
        color[v] = 2;
        return false;
    }

    void fillInAns() {
        ans.assign(n+1,-1);
        for (auto c : cycle) { ans[c] = 0; }
        for (auto c : cycle) { dfs2(c,-1,0); }
    }

    void dfs2(ll v, ll p, ll val) {
        ans[v] = val;
        for (auto u: adj[v]) {
            if (u == p) continue;
            if (ans[u] >= 0) continue;
            dfs2(u,v,val+1);
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
    //freopen("A.in","r",stdin);
    ll t; cin >> t;
    FORE(i,1,t) solve(i);
    return 0;
}
