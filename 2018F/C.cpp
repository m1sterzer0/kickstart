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
        if (k <= n) { ans = k; } //repeated 'a's
        else if (l == 1) { ans = 0; }
        else {
            prepPowers();
            if (n >= 84) { solveBig();        } // Sloppy bound for when l = 2 and k = 1e12
            else         { solveSmall(false); }
        }
    }

    void prepPowers() {
        ll x = 1; lpow.push_back(x);
        while (x <= k) { x *= l; lpow.push_back(x); }
        powmax = (ll) lpow.size() - 1;
    }

    void solveSmall(bool large) {
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
                if (large && c == 'a' && prefix.size() == 0) continue;
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

    void solveBig() {
        // In this case, we know that we are going to have 
        // (long string of aaa...a) (core palindrome that does NOT begin with an a) (long string of aaa.....a)
        // To figure out where we are in the sequence
        k -= n;
        ll aprefix = findAPrefix();
        n -= (aprefix + aprefix);
        solveSmall(true);
        ans += aprefix + aprefix;
    }

    ll findAPrefix() {
        vector<ll> palCount;
        palCount.push_back(0);
        palCount.push_back(l-1);
        palCount.push_back(l-1);
        for (ll i = 3; i < 100; i++) {
            palCount.push_back(l * palCount[i-2]);
            if (palCount[i] > k) palCount[i] = k+1;
        }

        vector<ll> cumPalCount(palCount.size(), 0LL);
        cumPalCount[0] = 0;
        FOR(i,1,(ll) palCount.size()) {
            cumPalCount[i] = cumPalCount[i-1] + palCount[i];
            if (cumPalCount[i] > k) cumPalCount[i] = k+1; // Just caution to prevent overflow
        }

        ll aprefix = (n-1)/2;
        ll maxPal = n - aprefix - aprefix;
        while (cumPalCount[maxPal] < k) {
            k -= cumPalCount[maxPal];
            aprefix--;
            maxPal += 2;
        }
        return aprefix;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("C.in5","r",stdin);
    ll t; cin >> t;
    FORE(i,1,t) { solver ss; ss.doit(i); }
    return 0;
}
