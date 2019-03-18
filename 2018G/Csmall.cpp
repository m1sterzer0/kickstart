#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
#define SZ(v) ((ll)(v).size())  
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(ll i=(a);i<=(b);++i)  

struct pt { ll x; ll y; ll d;};
bool operator< (const pt &a, const pt &b) { return a.d < b.d || (a.d == b.d && (a.x < b.x || (a.x == b.x && a.y < b.y))); }
bool operator> (const pt &a, const pt &b) { return a.d > b.d || (a.d == b.d && (a.x > b.x || (a.x == b.x && a.y > b.y))); }

struct solver {
    ll ans;
    ll n, m, e, sr, sc, tr, tc;
    array<array<int,100>,100> cave;
    void doit(ll t) {
        read();
        solve();
        printf("Case #%lld: %lld\n", t, ans);
    }

    void read() {
        cin >> n >> m >> e >> sr >> sc >> tr >> tc;
        sr--; sc--; tr--; tc--;
        REP(j,n) {
            REP(i,m) {
                cin >> cave[i][j];
            }
        }
    }

    void solve() {
        // Just run Dijkstra
        array<array<ll,100>,100> dist;
        REP(i,100) dist[i].fill(LONG_LONG_MAX);
        priority_queue<pt, vector<pt>, greater<pt>> qq;
        qq.push({sc,sr,0LL});
        while (!qq.empty()) {
            ll x = qq.top().x;
            ll y = qq.top().y;
            ll d = qq.top().d;
            qq.pop();
            if (dist[x][y] < LONG_LONG_MAX) continue;
            dist[x][y] = d;
            if (x > 0)   { ll nd = -cave[x-1][y]; if (nd < 100000) qq.push({x-1,y,d+nd}); }
            if (y > 0)   { ll nd = -cave[x][y-1]; if (nd < 100000) qq.push({x,y-1,d+nd}); }
            if (x+1 < m) { ll nd = -cave[x+1][y]; if (nd < 100000) qq.push({x+1,y,d+nd}); }
            if (y+1 < n) { ll nd = -cave[x][y+1]; if (nd < 100000) qq.push({x,y+1,d+nd}); }
        }
        if (dist[tc][tr] <= e) ans = e - dist[tc][tr];
        else                   ans = -1;
    }

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //   freopen("C.in2","r",stdin);
    ll t; cin >> t;
    FORE(i,1,t) { solver ss; ss.doit(i); }
    return 0;
}
