#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
#define SZ(v) ((ll)(v).size())  
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(ll i=(a);i<=(b);++i)  


struct pileSum {ll p1, p2, p3, idx;};
bool sort12( const pileSum &a, const pileSum &b) { return a.p1 < b.p1 || (a.p1 == b.p1 && a.p2 < b.p2); }
bool sort13( const pileSum &a, const pileSum &b) { return a.p1 < b.p1 || (a.p1 == b.p1 && a.p3 < b.p3); }
bool sort23( const pileSum &a, const pileSum &b) { return a.p2 < b.p2 || (a.p2 == b.p2 && a.p3 < b.p3); }
bool operator<  (const pileSum &a, const pileSum &b) { return a.p1 < b.p1 || (a.p1 == b.p1 && a.p2 < b.p2); }
bool operator== (const pileSum &a, const pileSum &b) { return a.p1 == b.p1 && a.p2 == b.p2 && a.p3 == b.p3 && a.idx == b.idx; }

struct BIT1 {
    ll n;
    vector<ll> arr;
    BIT1(ll nin) { n = nin; arr.assign(n+1,0LL); }
    void add(ll x, ll v) {
        for (ll xx = x; xx <= n; xx += (xx & -xx)) arr[xx] += v;
    }
    ll query(ll x) {
        ll ans = 0;
        for (ll xx = x; xx > 0; xx -= (xx & -xx)) ans += arr[xx];
        return ans;
    }
    ll query(ll l, ll r) { return query(r) - query(l-1);  }
};

struct BIT12D {
    ll n; ll m;
    vector<vector<ll>> arr;

    BIT12D(ll nin, ll min) {
        n = nin;
        m = min;
        arr.resize(n+1);
        FORE(i,0,n) { arr[i].assign(m+1,0LL); }
    } 

    // Updates all rectangles from x,y to n,m with value (add or xor both work)
    void add(ll x, ll y, ll v) {
        for (ll xx = x; xx <= n; xx += (xx & -xx)) {
            for (ll yy = y; yy <= m; yy += (yy & -yy)) {
                arr[xx][yy] += v;
            }
        }
        return;
    }

    ll query(ll x, ll y) {
        ll ans = 0;
        for (ll xx = x; xx > 0; xx -= (xx & -xx)) {
            for (ll yy = y; yy > 0; yy -= (yy & -yy)) {
                ans += arr[xx][yy];
            }
        }
        return ans;
    }
};

struct solver {
    ll n;
    vector<ll> a;
    vector<ll> b;
    vector<pileSum> acomb;
    vector<pileSum> bcomb;

    // Scratch for the dfs
    ll cnt1, cnt2, cnt3;
    ll sum1, sum2, sum3;
    ll n3;


    void doit(ll t) {
        read();
        acomb.reserve(1000000);
        bcomb.reserve(1000000);

        cnt1 = n; cnt2 = n; cnt3 = n;
        sum1 = 0; sum2 = 0; sum3 = 0;
        n3 = 3 * n;
        dfs(a,acomb,0);
        dfs(b,bcomb,0);

        // We can save a factor of 6 by sorting the 3 sums within each acomb entry
        for (auto &p: acomb) {
            ll x,y,z;
            if       (p.p1 <= p.p2 && p.p2 <= p.p3) { x = p.p1; y = p.p2; z = p.p3; }
            else if  (p.p1 <= p.p3 && p.p3 <= p.p2) { x = p.p1; y = p.p3; z = p.p2; }
            else if  (p.p2 <= p.p1 && p.p1 <= p.p3) { x = p.p2; y = p.p1; z = p.p3; }
            else if  (p.p2 <= p.p3 && p.p3 <= p.p1) { x = p.p2; y = p.p3; z = p.p1; }
            else if  (p.p3 <= p.p1 && p.p1 <= p.p2) { x = p.p3; y = p.p1; z = p.p2; }
            else                                    { x = p.p3; y = p.p2; z = p.p1; }
            p.p1 = x; p.p2 = y; p.p3 = z;
        }
        sort(acomb.begin(),acomb.end(),sort12);
        auto it2 = unique(acomb.begin(),acomb.end());
        acomb.resize(distance(acomb.begin(),it2));

        ll acombsize = (ll) acomb.size();
        ll bcombsize = (ll) bcomb.size();
        REP(i,acombsize) acomb[i].idx = i;
        vector<ll> wincnt(acombsize, 0LL);

        // Coordinate Compression
        vector<ll> values;
        values.reserve(2000000);
        for (auto &p : acomb) { values.push_back(p.p1); values.push_back(p.p2); values.push_back(p.p3); }
        for (auto &p : bcomb) values.push_back(p.p1);
        sort(values.begin(),values.end());
        auto it = unique(values.begin(),values.end());
        values.resize(distance(values.begin(),it));
        unordered_map<ll,ll> coord;
        REP(i,(ll) values.size()) { coord[values[i]] =  i+1; }
        ll coordmax = 1;
        while (coordmax < (ll) values.size()) coordmax *= 2;

        // Use inclusing exclusion
        sort(acomb.begin(),acomb.end(),sort12);
        sort(bcomb.begin(),bcomb.end(),sort12);
        BIT12D calc123(coordmax,coordmax);
        ll idx123 = 0;
        for (auto &p : acomb) {
            while (idx123 < bcombsize && p.p1 > bcomb[idx123].p1) { calc123.add(coord[bcomb[idx123].p2], coord[bcomb[idx123].p3], 1LL); idx123++; }
            wincnt[p.idx] += calc123.query(coord[p.p2]-1,coordmax);
            wincnt[p.idx] += calc123.query(coordmax,coord[p.p3]-1);
            wincnt[p.idx] -= 2 * calc123.query(coord[p.p2]-1,coord[p.p3]-1);
        }

        sort(acomb.begin(),acomb.end(),sort23);
        sort(bcomb.begin(),bcomb.end(),sort23);
        BIT1 calc23(coordmax);
        ll idx23 = 0;
        for (auto &p : acomb) {
            while (idx23 < bcombsize && p.p2 > bcomb[idx23].p2) { calc23.add(coord[bcomb[idx23].p3],1LL); idx23++; }
            wincnt[p.idx] += calc23.query(coord[p.p3]-1);
        }

        // Now find the answer
        ll num = *max_element(wincnt.begin(),wincnt.end());
        ll denom = bcombsize;
        double ans = (double) num / (double) denom;

        printf("Case #%lld: %.12f\n", t, ans);
    }

    void read() {
        cin >> n;
        a.resize(3*n);
        b.resize(3*n);
        REP(i,3*n) cin >> a[i];
        REP(i,3*n) cin >> b[i];
    }

    void dfs(vector<ll> &a, vector<pileSum> &acomb, ll idx) {
        if (idx == n3) { acomb.push_back({sum1,sum2,sum3, 0}); return; }
        if (cnt1 > 0) { sum1 += a[idx]; cnt1--; dfs(a, acomb, idx+1); cnt1++; sum1 -= a[idx]; }
        if (cnt2 > 0) { sum2 += a[idx]; cnt2--; dfs(a, acomb, idx+1); cnt2++; sum2 -= a[idx]; }
        if (cnt3 > 0) { sum3 += a[idx]; cnt3--; dfs(a, acomb, idx+1); cnt3++; sum3 -= a[idx]; }
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



