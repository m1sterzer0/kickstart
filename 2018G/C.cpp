#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
#define SZ(v) ((ll)(v).size())  
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(ll i=(a);i<=(b);++i)  

struct status { bool exit; ll energy; ll trapmask; bool reachable; };

struct solver {
    ll ans;
    ll n, m, e, sr, sc, tr, tc;
    bitset<10000> visited;
    vector<bool> analyzed;
    array<ll,10000> trap2id;
    vector<ll> id2cost;
    ll numtraps;
    vector<status> positions;
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
        identifyTraps();
        ll cases = 1 << numtraps;
        positions.resize(cases);
        REP(i,cases) solveCase(i);
        findBest();
    }

    void identifyTraps() {
        numtraps = 0;
        trap2id.fill(0LL);
        REP(i,m) {
            REP(j,n) {
                if (cave[i][j] < 0 && cave[i][j] > -100000) {
                    trap2id[m*j+i] = numtraps;
                    id2cost.push_back(-cave[i][j]);
                    numtraps++;
                } 
            }
        }
    }

    void solveCase(ll mask) {
        positions[mask].trapmask = 0;
        positions[mask].reachable = false;
        ll energy = e;
        visited.reset();
        stack<pair<ll,ll>> qq;
        visited.set(sr*m+sc);
        qq.push({sc,sr});
        while (!qq.empty()) {
            ll x = qq.top().first;
            ll y = qq.top().second;
            qq.pop();
            if (cave[x][y] <= -100000) continue;
            else {
                if (cave[x][y] < 0) {
                    ll tid = trap2id[m*y+x];
                    if (((1 << tid) & mask) == 0) { positions[mask].trapmask |= (1 << tid); continue; }
                }
                energy += cave[x][y];
                ll scr;
                if (x > 0   && !visited.test(scr = m*y+(x-1))) {visited.set(scr); qq.push({x-1,y}); }
                if (y > 0   && !visited.test(scr = m*(y-1)+x)) {visited.set(scr); qq.push({x,y-1}); }
                if (x+1 < m && !visited.test(scr = m*y+(x+1))) {visited.set(scr); qq.push({x+1,y}); }
                if (y+1 < n && !visited.test(scr = m*(y+1)+x)) {visited.set(scr); qq.push({x,y+1}); }
            }
        }
        positions[mask].energy = energy;
        positions[mask].exit = visited.test(tr*m+tc);
    } 

    void findBest() {
        ans = -1;
        ll cases = 1 << numtraps;
        positions[0].reachable = true;
        REP(mask,cases) {
            ll i = 0;
            while (i < numtraps && !positions[mask].reachable) {
                ll tmask = 1 << i;
                if (mask & tmask) {
                    ll child = mask & (~tmask);
                    if (positions[child].reachable && (positions[child].trapmask & tmask) && (positions[child].energy >= id2cost[i])) positions[mask].reachable = true;
                }
                i++;
            }
            if (positions[mask].reachable && positions[mask].exit && positions[mask].energy > ans) ans = positions[mask].energy;
        }
    }
};
    
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
         //freopen("C.in2","r",stdin);
    ll t; cin >> t;
    FORE(i,1,t) { solver ss; ss.doit(i); }
    return 0;
}
