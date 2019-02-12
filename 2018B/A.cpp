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

ll fix9(ll f) {
    ll ff = f;
    ll p = 10;
    while (ff) {
        if (ff % 10 == 9) return f + p/10;
        if (p < 1000000000000000000LL) p *= 10;
        ff /= 10;
    }
    return f;
}

void solve(ll t) {
    ll ans = 0;
    ll f, l; cin >> f >> l;
    while (f != l) {
        ll a = fix9(f);
        if (a != f) {
            f = a;
            continue;
        }
        if (f % 10 != 0 || f + 10 > l) {
            ans += (f % 9 == 0 ? 0 : 1);
            f++;
            continue;
        }

        ll aa = 8;
        ll bb = 10;
        while ( 10*bb <= l && f + 10*bb <= l && f % (10*bb) == 0) {
            aa *= 9;
            bb *= 10;
        }
        ans += aa;
        f += bb;
    }

    printf("Case #%lld: %lld\n", t, ans+1);
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
