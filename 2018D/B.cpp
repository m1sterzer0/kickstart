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

void populate(vector<ll> &p, ll p1, ll p2, ll a, ll b, ll c, ll m, ll n) {
    p[0] = p1;
    p[1] = p2;
    FOR(i,2,n) { p[i] = ((a * p[i-1] + b*p[i-2] + c) % m) + 1; }
}

struct tower {ll x; ll y; };
bool operator< (const tower &a, const tower &b) { ll xxa = a.x - a.y; ll xxb = b.x - b.y; return xxa < xxb || (xxa == xxb && b.y < a.y); }
struct balloon {ll x; ll y; };
bool operator< (const balloon &a, const balloon &b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }

bool checkLeft(const tower &t, const balloon &b)  { return b.y <= t.y - (t.x - b.x); }
bool checkRight(const tower &t, const balloon &b) { return b.y <= t.y - (b.x - t.x); } 
bool envelopes(const tower &p, const tower &c)    { 
    ll p1 = p.x - p.y;
    ll p2 = p.x + p.y;
    ll c1 = c.x - c.y;
    ll c2 = c.x + c.y;
    return p1 <= c1 && c2 <= p2;
}

void solve(ll t) {
    ll n, k; cin >> n >> k;
    ll p1, p2, a1, b1, c1, m1; cin >> p1 >> p2 >> a1 >> b1 >> c1 >> m1;
    ll h1, h2, a2, b2, c2, m2; cin >> h1 >> h2 >> a2 >> b2 >> c2 >> m2;
    ll x1, x2, a3, b3, c3, m3; cin >> x1 >> x2 >> a3 >> b3 >> c3 >> m3;
    ll y1, y2, a4, b4, c4, m4; cin >> y1 >> y2 >> a4 >> b4 >> c4 >> m4;
    vector<ll> p(n);
    vector<ll> h(n);
    vector<ll> x(k);
    vector<ll> y(k);
    populate(p,p1,p2,a1,b1,c1,m1,n);
    populate(h,h1,h2,a2,b2,c2,m2,n);
    populate(x,x1,x2,a3,b3,c3,m3,k);
    populate(y,y1,y2,a4,b4,c4,m4,k);


    // Sort towers first by increasing (x-y) value, and then by decreasing height
    vector<tower> tt;
    REP(i,n) tt.push_back({p[i],h[i]});
    sort(tt.begin(),tt.end());

    vector<balloon> bb;
    REP(i,k) bb.push_back({x[i],y[i]});
    sort(bb.begin(),bb.end());

    ll ti = 0;
    ll bi = 0;
    ll ans = 0;
    while (bi < k && bb[bi].x < tt[ti].x) { if (checkLeft(tt[ti],bb[bi])) {ans++;} bi++; }
    FOR(i,1,n) {
        if (envelopes(tt[ti],tt[i])) continue;
        while (bi < k && bb[bi].x < tt[i].x) { if (checkRight(tt[ti],bb[bi]) || checkLeft(tt[i],bb[bi])) {ans++;} bi++; }
        ti = i;
    }
    while (bi < k) { if (checkRight(tt[ti],bb[bi])) {ans++;} bi++; }
    printf("Case #%lld: %lld\n", t, ans);
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
