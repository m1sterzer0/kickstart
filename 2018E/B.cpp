#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
#define SZ(v) ((ll)(v).size())  
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(ll i=(a);i<=(b);++i)  

struct option { ll cost; string s; };
bool operator< (const option &a, const option &b) { return a.cost < b.cost; }

struct solver {
    ll n, m, p;
    vector<string> narr;
    set<string> marr;
    vector<option> scoreboard;
    ll ans;
    void doit(ll t) {
        read();
        calcCosts();
        findBest();
        printf("Case #%lld: %lld\n", t, ans);
    }

    void calcCosts() {
        scoreboard.push_back({0LL, ""});
        vector<option> newScoreboard;
        REP(i,p) {
            ll zeros = 0;
            ll ones = 0;
            REP(j,n) {
                if (narr[j][i] == '0') zeros++;
                else                   ones++;
            }
            newScoreboard.resize(2*scoreboard.size());
            ll idx = 0;
            for (auto &p : scoreboard) { 
                newScoreboard[idx] = { p.cost + zeros, p.s + '1'};
                idx++;
                newScoreboard[idx] = { p.cost + ones, p.s + '0'};
                idx++;
            }
            sort(newScoreboard.begin(),newScoreboard.end());
            scoreboard.assign(newScoreboard.begin(), ((ll) newScoreboard.size() > m+1 ? newScoreboard.begin()+(m+1) : newScoreboard.end()));
        }
    }

    void findBest() {
        for (auto &p : scoreboard) {
            if (marr.count(p.s) > 0) continue;
            ans = p.cost;
            return;
        }
    }

    void read() {
        cin >> n >> m >> p;
        narr.resize(n);
        REP(i,n) cin >> narr[i];
        REP(i,m) {
            string s;
            cin >> s;
            marr.insert(s);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("A.in","r",stdin);
    ll t; cin >> t;
    FORE(i,1,t) { solver ss; ss.doit(i); }
    return 0;
}
