#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
#define SZ(v) ((ll)(v).size())  
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(ll i=(a);i<=(b);++i)  

struct edge { ll a,b,l; };
bool operator< (const edge &a, const edge &b) { return a.l < b.l; }

struct solver {
    ll ans;
    ll v, e;
    vector<edge> edges;
    void doit(ll t) {
        read();
        solve();
        printf("Case #%lld: %lld\n", t, ans);
    }

    void read() {
        cin >> v >> e;
        edges.resize(e);
        REP(i,e) { cin >> edges[i].a >> edges[i].b >> edges[i].l; }
    }

    void solve() {
        vector<bool> visited(v+1,false);
        vector<bool> special(v+1,false); // endpoints of the zero length road, if it exists

        sort(edges.begin(),edges.end());
        ans = 1;
        if (edges[0].l == 0) { special[edges[0].a] = true; special[edges[0].b] = true; }
        for (auto &ee : edges) {
            if (visited[ee.a] && visited[ee.b]) continue;
            else if (!visited[ee.a] && !visited[ee.b]) ans *= 2;
            else if (!visited[ee.a] && visited[ee.b] && special[ee.b]) ans *= 2;
            else if ( visited[ee.a] && !visited[ee.b] && special[ee.a]) ans *= 2;
            visited[ee.a] = true;
            visited[ee.b] = true;
        }
    }

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("B.in","r",stdin);
    ll t; cin >> t;
    FORE(i,1,t) { solver ss; ss.doit(i); }
    return 0;
}
