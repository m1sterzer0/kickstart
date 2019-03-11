#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
#define SZ(v) ((ll)(v).size())  
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(ll i=(a);i<=(b);++i)  

struct ftable { 
    array<char,26> ft;
};

bool operator== (const ftable &a, const ftable &b) { 
    REP(i,26) if (a.ft[i] != b.ft[i]) return false;
    return true;
}

struct solver {
    ll ans;
    ll l;
    string a;
    string b;
    void doit(ll t) {
        read();
        solve();
        printf("Case #%lld: %lld\n", t, ans);
    }
    void read() { cin >> l >> a >> b; }

    void solve() {
        ans = 0;
        ftable fta;
        REP(i,l) {
            FOR(j,i,l) {
                fta.ft.fill(0);
                FORE(k,i,j) fta.ft[a[k]-'A']++;
                if (findInB(j-i+1,fta)) ans++;
            }
        }
    }

    bool findInB(ll n, const ftable fta) {
        ll i = 0;
        ll j = i + n -1;
        ftable ftb;
        ftb.ft.fill(0);
        FORE(k,i,j) ftb.ft[b[k]-'A']++;
        while (j < l) {
            if (fta == ftb) return true;
            ftb.ft[b[i]-'A']--;
            i++;
            j++;
            if (j < l) ftb.ft[b[j]-'A']++;
        }
        return false;
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
