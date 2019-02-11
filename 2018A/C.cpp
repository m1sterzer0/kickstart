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

struct word { 
    char f; 
    char l; 
    array<ll,26> ft;
    word() { ft.fill(0LL); }
};
bool operator<(const word &a, const word &b) { 
    return a.f < b.f || (a.f == b.f && (a.l < b.l || (a.l == b.l && a.ft < b.ft)));
}

void solve(ll t) {
    ll ans = 0;

    ll L; cin >> L;
    map<ll,vector<string>> len2words;
    set<ll> lens;
    REP(i,L) {
        string s; cin >> s;
        ll l = s.size();
        lens.insert(l);
        len2words[l].push_back(s);
    }
    char s1; cin >> s1;
    char s2; cin >> s2;
    ll n,a,b,c,d; cin >> n >> a >> b >> c >> d;
    string s(n,'a');
    vector<ll> x(n);
    x[0] = (ll) s1; s[0] = s1;
    x[1] = (ll) s2; s[1] = s2;
    FOR(i,2,n) { x[i] = (a * x[i-1] + b * x[i-2] + c) % d; s[i] = (char) (97 + x[i] % 26); }

    for (auto l : lens) {
        multiset<word> words;
        for (auto ss : len2words[l]) {
            word w;
            w.f = ss[0];
            w.l = ss[l-1];
            for (auto cc : ss) w.ft[cc-'a']++;
            words.insert(w);
        }

        if (l > n) continue;
        word cw;
        cw.f = s[0];
        cw.l = s[l-1];
        REP(i,l) cw.ft[s[i]-'a']++;
        auto cnt = words.count(cw);
        if (cnt > 0) { ans += cnt; words.erase(cw); }
        for (ll i = 1; i + l <= n; i++) {
            cw.ft[cw.f-'a']--;
            cw.f = s[i];
            cw.l = s[i+l-1];
            cw.ft[cw.l-'a']++;
            cnt = words.count(cw);
            if (cnt > 0) { ans += cnt; words.erase(cw); }
        } 
    }
    printf("Case #%lld: %lld\n",t, ans);
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
