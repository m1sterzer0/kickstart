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
    ll n, q;
    ll x1, x2, a1, b1, c1, m1;
    ll y1, y2, a2, b2, c2, m2;
    ll z1, z2, a3, b3, c3, m3;
    vector<ll> xi;
    vector<ll> yi;
    vector<ll> zi;

    void doit(ll t) {
        read();
        solve();
        printf("Case #%lld: %lld\n", t, ans);
    }

    void read() {
        cin >> n >> q;
        cin >> x1 >> x2 >> a1 >> b1 >> c1 >> m1;
        cin >> y1 >> y2 >> a2 >> b2 >> c2 >> m2;
        cin >> z1 >> z2 >> a3 >> b3 >> c3 >> m3;
    }

    void solve() {
        // Unwrap the inputs
        xi.resize(n);
        yi.resize(n);
        zi.resize(q);
        xi[0] = x1; if (n > 1) xi[1] = x2;
        yi[0] = y1; if (n > 1) yi[1] = y2;
        zi[0] = z1; if (q > 1) zi[1] = z2;
        FOR(i,2,n) {
            xi[i] = (a1 * xi[i-1] + b1 * xi[i-2] + c1) % m1;
            yi[i] = (a2 * yi[i-1] + b2 * yi[i-2] + c2) % m2;
        }
        FOR(i,2,q) {
            zi[i] = (a3 * zi[i-1] + b3 * zi[i-2] + c3) % m3;
        }

        // store 2 min heaps, one for the beginning of the intervals and one for the end
        priority_queue<ll, vector<ll>, greater<ll>> liq;
        priority_queue<ll, vector<ll>, greater<ll>> riq;
        vector<ll> points;
        REP(i,n) {
            ll li = min(xi[i],yi[i]) + 1;
            ll ri = max(xi[i],yi[i]) + 1;
            liq.push(li);
            riq.push(ri);
            points.push_back(li-1);
            points.push_back(li);
            points.push_back(ri);
            points.push_back(ri+1);
        }

        // Iterate through all of these points
        sort(points.begin(),points.end());
        auto it = unique(points.begin(),points.end());
        points.resize(distance(points.begin(),it));

        vector<ll> cumsum;
        cumsum.reserve(points.size());
        ll slope = 0;
        ll last = 0;
        ll running = 0;
        for (auto s : points) {
            while (!liq.empty() && liq.top() == s) { liq.pop(); slope++; }
            running += slope * (s - last);
            cumsum.push_back(running);
            last = s;
            while (!riq.empty() && riq.top() == s) { riq.pop(); slope--; }
        }

        // Now do the queries
        ans = 0;
        REP(i,q) {
            ll ki = zi[i] + 1;
            // I made a mistake and wrote this for kth lowest instead of kth highest, so I need to do a conversion
            ll kth = cumsum.back() + 1 - ki;
            if (kth < 1) continue;
            ll si = doQuery(kth,cumsum,points);
            ans += (i+1) * si;
        }
    }

    ll doQuery(ll ki, vector<ll> &cumsum, vector<ll> &points) {
        ll l = 0;
        ll r = cumsum.size()-1;
        if (ki > cumsum[r]) return 0;

        // Simple Bin Search
        while (r-l > 1) {
            ll m = (l+r)/2;
            if (cumsum[m] < ki) l = m;
            else                r = m;
        }
        if (cumsum[r] == cumsum[l]) return points[l]; 
        ll slope = (cumsum[r] - cumsum[l]) / (points[r] - points[l]);
        ll adder =  (ki - cumsum[l] + (slope-1)) / slope;
        return points[l] + adder;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("B.in","r",stdin);
    ll t; cin >> t;
    FORE(i,1,t) { solver ss; ss.doit(i); }
    return 0;
}
