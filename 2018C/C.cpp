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

const  ll mod = 1000000007;
inline ll madd(ll x, ll y) { ll r = x + y; if (r >= mod) { r -= mod; } return r; }
inline ll msub(ll x, ll y) { return x >= y ? x - y : x + mod - y; }
inline ll mmul(ll x, ll y) { return x * y % mod; }
inline ll mpow(ll x, ll p) { ll r=1; while (p) { if (p & 1) r = mmul(r,x); x = mmul(x,x); p = p >> 1; } return r; } 
inline ll minv(ll x)       { return mpow(x,mod-2); }

void solve(ll t) {
    ll n, k, x1, y1, c, d, e1, e2, f;
    cin >> n >> k >> x1 >> y1 >> c >> d >> e1 >> e2 >> f;
    ll xi = x1; ll yi = y1;

    // There is a simplification here, but it isn't worth anything 
    vector<ll> a(n); 
    REP(i,n) { 
        a[i] = (xi + yi) % f;
        ll nxi = (c * xi + d * yi + e1) % f;
        ll nyi = (d * xi + c * yi + e2) % f;
        xi = nxi;
        yi = nyi;
    }

    ll ans = 0;
    ll coeff = 0;
    REP(i,n) {
        ll lcoeff;
        if (i == 0) lcoeff = k;
        else {
            ll term1 = (i+1);
            ll term2 = msub(mpow(i+1,k),1);
            ll term3 = minv(i);
            lcoeff = mmul(mmul(term1,term2),term3);
        }
        coeff = madd(coeff,lcoeff);
        ans = madd(ans,mmul(a[i],mmul(n-i,coeff)));
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
