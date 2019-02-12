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

struct BIT {
    ll n;
    vector<ll> arr;
    BIT(ll nin) { n = nin; arr.assign(n+1,0LL); }
    void add(ll x, ll v) {
        for (ll xx = x; xx <= n; xx += (xx & -xx)) { arr[xx] += v; }
    }
    ll query(ll x) {
        ll ans = 0;
        for (ll xx = x; xx > 0; xx -= (xx & -xx)) { ans += arr[xx]; }
        return ans;
    }
};

void calcWest(ll m, ll n, vector<pair<ll,ll>> &cafe, vector<ll> &nw, vector<ll> &sw) {
    BIT b1(m); // m-1 is the maximum, but we need to add 1 since BIT starts at 1.
    ll lastidx = -1;
    ll b1tot = 0;
    REP(i,n) {
        if (lastidx == -1) { 
            sw[i] = 0;
            nw[i] = 0;
            lastidx = i;
            continue;
        }
        if (cafe[lastidx].first < cafe[i].first) {
            FOR(j,lastidx,i) { b1.add(cafe[j].second + 1,1LL); b1tot++; }
            lastidx = i;
        }

        sw[i] = b1.query(cafe[i].second);
        nw[i] = b1tot - b1.query(cafe[i].second+1);
    }
}

void calcEast(ll m, ll n, vector<pair<ll,ll>> &cafe, vector<ll> &ne, vector<ll> &se) {
    BIT b1(m); // m-1 is the maximum, but we need to add 1 since BIT starts at 1.
    ll lastidx = -1;
    ll b1tot = 0;
    for (ll i = n-1; i >= 0; i--) {
        if (lastidx == -1) { 
            se[i] = 0;
            ne[i] = 0;
            lastidx = i;
            continue;
        }
        if (cafe[lastidx].first > cafe[i].first) {
            FORE(j,i+1,lastidx) { b1.add(cafe[j].second + 1,1LL); b1tot++; }
            lastidx = i;
        }

        se[i] = b1.query(cafe[i].second);
        ne[i] = b1tot - b1.query(cafe[i].second+1);
    }
}


void solve(ll t) {
    ll n, v1, h1, a, b, c, d, e, f, m;
    cin >> n >> v1 >> h1 >> a >> b >> c >> d >> e >> f >> m;
    vector<pair<ll,ll>> cafe(n);
    cafe[0] = {h1,v1};
    ll vi = v1;
    ll hi = h1;
    FOR(i,1,n) {
        ll vn = (a * vi + b * hi + c) % m;
        ll hn = (d * vi + e * hi + f) % m;
        cafe[i] = {hn,vn};
        vi = vn; hi = hn;
    }

    sort(cafe.begin(),cafe.end());
    vector<ll> sw(n,0);
    vector<ll> nw(n,0);
    vector<ll> se(n,0);
    vector<ll> ne(n,0);
    calcWest(m,n,cafe,nw,sw);
    calcEast(m,n,cafe,ne,se);

    ll ans = n * (n-1) * (n-2) / 6;
    REP(i,n) {
        ans -= sw[i] * ne[i];
        ans -= se[i] * nw[i];
    }

    printf("Case #%lld: %lld\n", t, ans);
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
