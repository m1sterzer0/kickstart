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

struct solBag {
    vector<vector<vector<ll>>> rowraw;
    vector<vector<vector<ll>>> rowdata;
    vector<vector<vector<ll>>> colraw;
    vector<vector<vector<ll>>> coldata;
    ll m, n;
    void init (ll r, ll c) { 
        m = r;
        n = c;
        rowraw.resize(r);
        rowdata.resize(r);
        REP(i,r) {
            rowraw[i].resize(c);
            rowdata[i].resize(c);
            REP(j,c) {
                rowraw[i][j].assign(c,0LL);
                rowdata[i][j].assign(c,0LL);
            }
        }

        colraw.resize(c);
        coldata.resize(c);
        REP(i,c) {
            colraw[i].resize(r);
            coldata[i].resize(r);
            REP(j,r) {
                colraw[i][j].assign(r,0LL);
                coldata[i][j].assign(r,0LL);
            }
        }
    }

    void analyze() {
        // Do rows first
        REP(i,m) {
            FOR(off,0,n) {
                REP(c1,n-off) {
                    ll c2 = c1 + off;
                    if (off == 0)      rowdata[i][c1][c2] = rowraw[i][c1][c2];
                    else if (off == 1) rowdata[i][c1][c2] = rowraw[i][c1][c1] + rowraw[i][c2][c2] + rowraw[i][c1][c2];
                    else               rowdata[i][c1][c2] = rowraw[i][c1][c2] + rowdata[i][c1][c2-1] + rowdata[i][c1+1][c2] - rowdata[i][c1+1][c2-1];
                }
            }
        }

        // Do columns next
        REP(i,n) {
            FOR(off,0,m) {
                REP(r1,m-off) {
                    ll r2 = r1 + off;
                    if (off == 0)      coldata[i][r1][r2] = colraw[i][r1][r2];
                    else if (off == 1) coldata[i][r1][r2] = colraw[i][r1][r1] + colraw[i][r2][r2]    + colraw[i][r1][r2];
                    else               coldata[i][r1][r2] = colraw[i][r1][r2] + coldata[i][r1][r2-1] + coldata[i][r1+1][r2] - coldata[i][r1+1][r2-1];
                }
            }
        }
    }
    void addRowMatch(ll r, ll c1, ll c2) { rowraw[r][c1][c2] += (c2-c1+1); }
    void addColMatch(ll c, ll r1, ll r2) { colraw[c][r1][r2] += (r2-r1+1); }
    ll queryRow(ll r, ll c1, ll c2)      { return rowdata[r][c1][c2]; }
    ll queryCol(ll c, ll r1, ll r2)      { return coldata[c][r1][r2]; }
};

struct solver {
    ll r, c, w;
    vector<string> words;
    vector<string> grid;
    solBag sbag;
    ll bestNum;
    ll bestDenom;
    ll count;

    void read() {
        cin >> r >> c >> w;
        grid.resize(r);
        words.resize(w);
        REP(i,r) cin >> grid[i];
        REP(i,w) cin >> words[i];
    }

    void doit(ll t) {
        read();
        sbag.init(r,c);
        doWordSearch();
        sbag.analyze();
        iterateThroughSubgrids();
        printf("Case #%lld: %lld/%lld %lld\n", t, bestNum, bestDenom, count);
    }

    void doWordSearch() {
        for (auto &ww : words) {
            REP(r1,r) {
                REP(c1,c) {
                    if (checkRight(r1,c1,ww)) sbag.addRowMatch(r1,c1,c1+ww.size()-1);
                    if (checkLeft(r1,c1,ww))  sbag.addRowMatch(r1,c1-ww.size()+1,c1);
                    if (checkDown(r1,c1,ww))  sbag.addColMatch(c1,r1,r1+ww.size()-1);
                    if (checkUp(r1,c1,ww))    sbag.addColMatch(c1,r1-ww.size()+1,r1);
                }
            }
        }
    }

    bool checkRight(ll r1, ll c1, string &s) {
        ll cend = c1 + (ll) s.size() - 1;
        if ( cend >= c) return false;
        REP(i,(ll) s.size()) { if (grid[r1][c1+i] != s[i]) return false; }
        return true;
    }

    bool checkLeft(ll r1, ll c1, string &s) {
        ll cend = c1 - (ll) s.size() + 1;
        if ( cend < 0) return false;
        REP(i,(ll) s.size()) { if (grid[r1][c1-i] != s[i]) return false; }
        return true;
    }

    bool checkDown(ll r1, ll c1, string &s) {
        ll rend = r1 + (ll) s.size() - 1;
        if ( rend >= r) return false;
        REP(i,(ll) s.size()) { if (grid[r1+i][c1] != s[i]) return false; }
        return true;
    }

    bool checkUp(ll r1, ll c1, string &s) {
        ll rend = r1 - (ll) s.size() + 1;
        if ( rend < 0) return false;
        REP(i,(ll) s.size()) { if (grid[r1-i][c1] != s[i]) return false; }
        return true;
    }

    void iterateThroughSubgrids() {
        bestNum = 0; bestDenom = 1; count = 0;
        vector<vector<ll>> rowLetters(r);
        vector<vector<ll>> colLetters(r);
        REP(i,r) { rowLetters[i].assign(c,0LL); colLetters[i].assign(c,0LL); }
        REP(r1,r) {
            REP(c1, c) {
                FOR(r2,r1,r) {
                    FOR(c2,c1,c) {
                        rowLetters[r2][c2] = sbag.queryRow(r2,c1,c2) + (r2 > r1 ? rowLetters[r2-1][c2] : 0LL);
                        colLetters[r2][c2] = sbag.queryCol(c2,r1,r2) + (c2 > c1 ? colLetters[r2][c2-1] : 0LL);
                        ll totLetters = rowLetters[r2][c2] + colLetters[r2][c2];
                        ll totSize = (c2-c1+1) + (r2-r1+1);
                        if      (totLetters * bestDenom > totSize * bestNum)  { bestNum = totLetters; bestDenom = totSize; count = 1; }
                        else if (totLetters * bestDenom == totSize * bestNum) { count++; }
                    }
                }
            }
        }
        ll g = __gcd(bestNum,bestDenom);
        bestNum /= g;
        bestDenom /= g;
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
    //freopen("C.in","r",stdin);
    ll t; cin >> t;
    FORE(i,1,t) solve(i);
    return 0;
}
