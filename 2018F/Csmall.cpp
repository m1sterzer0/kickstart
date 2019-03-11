#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
#define SZ(v) ((ll)(v).size())  
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(ll i=(a);i<=(b);++i)  

struct solver {
    ll ans;
    ll l, n, k;
    vector<ll> lpow;
    ll powmax;
    void doit(ll t) {
        read();
        solve();
        printf("Case #%lld: %lld\n", t, ans);
    }

    void read() { cin >> l >> n >> k; }

    void solve() {
        if (k <= n) { ans = k; return; } //repeated 'a's
        if (l == 1) { ans = 0; return; }
        ll x = 1; lpow.push_back(x);
        while (x <= k) { x *= l; lpow.push_back(x); }
        powmax = (ll) lpow.size() - 1;

        string prefix;
        while (k>0) {
            if (isPalindrome(prefix)) { 
                k--; 
                if (k == 0) {
                    ans = (ll) prefix.size();
                    return;
                }
            }
            char c;
            bool found = false;
            for (c = 'a'; c < 'a' + l; c++) {
                ll x = countPalindromes(prefix+c);
                if (x >= k) { prefix = prefix + c; found = true; break; }
                else        { k -= x; }
            }
            if (!found) { ans = 0; return; }
        }
    }

    bool isPalindrome(const string &s) { 
        ll i = 0; 
        ll j = (ll) s.size() - 1;
        if (j < 0) return false;
        while (i <= j) {
            if (s[i] != s[j]) return false;
            i++; j--;
        }
        return true;
    }

    ll countPalindromes(const string &prefix) {
        // First count where we have degrees of freedom
        ll cnt = 0;
        ll prefixSize = (ll) prefix.size(); 

        // First do the sizes where there are degrees of freedom
        for (ll psize = n; psize >= prefixSize; psize--) {
            if (psize >= prefixSize+prefixSize-1) {
                ll choices = (psize+1) / 2 - prefixSize;
                if (choices >= powmax) return (k+1);
                if (lpow[choices] > k) return (k+1);
                cnt += lpow[choices];
                if (cnt > k) return (k+1);
            }
            else {
                ll plen = prefixSize + prefixSize - psize;
                ll sidx = psize - prefixSize;
                if (isPalindrome(prefix.substr(sidx,plen))) cnt++;
            }
        }
        return cnt;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("C.in3","r",stdin);
    ll t; cin >> t;
    FORE(i,1,t) { solver ss; ss.doit(i); }
    return 0;
}
