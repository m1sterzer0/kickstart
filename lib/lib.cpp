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

// Algorithm Checklist:
// Graph:
//    Dijkstra
//    Floyd Warshal
//    Prim
//    Kruskal
//    Topological Sort
//    Articulation Points
//    Bridges
//    Bipartite Matching

//  Data Structures
//    SegmentTree
//    BIT/Fenwick
//    SegmentTree2D
//    BIT2D
//    CompactSegmentTree2D
//    UnionFind
//    SparseTable

//  2SAT
//  PrimeSieve
//  FactorSieve

// DP:
//    Longest Common Subsequence
//    Longest Increasing Subsequence
//    Edit Distance
//    Minimum Partition
//    Ways to Cover a Distance
//    Longest Path in Matrix
//    Subset Sum
//    0-1 Knapsack
//    Assembly Line Scheduling

// Modular Combinatorics
const ull mod = 1000000007;
inline ull madd(ull x, ull y) { ull r = x + y; if (r >= mod) { r -= mod; } return r; }
inline ull msub(ull x, ull y) { return x >= y ? x - y : x + mod - y; }
inline ull mmul(ull x, ull y) { return x * y % mod; }
inline ull mpow(ull x, ull p) { ull r=1; while (p) { if (p & 1) r = mmul(r,x); x = mmul(x,x); p = p >> 1; } return r; } 
inline ull minv(ull x) { return mpow(x,mod-2); }

struct modularCombinatorics {
    vector<ull> fact;
    vector<ull> ifact;
    void init(ull lim) {
        fact.clear(); fact.resize(lim+1,1);
        ifact.clear(); ifact.resize(lim+1,1);
        for (ull i = 2; i <= lim; i++) {
            fact[i] = mmul(fact[i-1],i);
            ifact[i] = minv(fact[i]);
        }
    }
    ull comb(ull n, ull k) {
        if (k > n) { return 0; }
        return mmul(mmul(fact[n],ifact[k]),ifact[n-k]);
    }
};

struct edge { ll v1; ll v2; ll w; };

struct weightedGraph {
    ll minn; ll maxn;
    vector<vector<edge>> adj;

    // E log e version of dijkstra
    void dijkstra(ll start, vector<ll> &ans) {
        vector<bool> visited;
        ans.assign(maxn+1,infll);
        priority_queue<pair<ll,ll>> pq;
        visited.assign(maxn+1,false);
        pq.push({0,start});
        while (!pq.empty()) {
            ll d  = pq.top().first;
            ll nn = pq.top().second;
            if (visited[nn]) continue;
            visited[nn] = true;
            ans[nn] = d;
            for (auto e : adj[nn]) {
                if (visited[e.v2]) continue;
                pq.push({d+e.w, e.v2});
            }
        }
    }
    void bellmanFord(ll start, vector<ll> &ans) {
        vector<edge> edges;
        for (ll nn = minn; nn <= maxn; nn++) {
            for (auto e : adj[nn]) { edges.push_back(e); }
        }
        ans.assign(maxn+1,infll);
        ans[start] = 0LL;
        for (ll v = minn; v <= maxn; v++) {
            for (auto e : edges) {
                if (ans[e.v1] == infll) continue;
                ans[e.v2] = min(ans[e.v2],ans[e.v1]+e.w);
            }
        }
    }

    void bellmanFord2(ll start, vector<ll> &ans, vector<ll> &pred, bool &negCycle) {
        vector<edge> edges;
        for (ll nn = minn; nn <= maxn; nn++) {
            for (auto e : adj[nn]) { edges.push_back(e); }
        }
        ans.assign(maxn+1,infll);
        pred.assign(maxn+1,minn-1);
        ans[start] = 0LL;
        for (ll v = minn; v <= maxn; v++) {
            for (auto e : edges) {
                if (ans[e.v1] == infll) continue;
                ll d2 = ans[e.v1] + e.w;
                if (d2 < ans[e.v2]) { ans[e.v2] = d2; pred[e.v2] = e.v1; }
            }
        }
        negCycle = false;
        for (auto e : edges) {
            if (ans[e.v1] + e.w < ans[e.v2]) negCycle = true;
        }
    }

    void floydWarshall(vector<vector<ll>> &ans) {
        ans.resize(maxn+1);
        for (ll i = minn; i <= maxn; i++) {
            ans[i].assign(maxn+1,infll);
        }

        for (ll nn = minn; nn <= maxn; nn++) {
            for (auto e : adj[nn]) {
                ans[nn][e.v2] = min(ans[nn][e.v2], e.w);
            }
        }

        for (ll k = minn; k <= maxn; k++) {
            for (ll i = minn; i <= maxn; i++) {
                if (ans[i][k] == infll) continue;
                for (ll j = minn; j <= maxn; j++) {
                    if (ans[k][j] == infll) continue;
                    ans[i][j] = min(ans[i][j], ans[i][k] + ans[k][j]);
                }
            }
        }
    }
};

struct twoSat {
    ll n;
    vector<vector<ll>> adj;
    vector<vector<ll>> adjInv;
    vector<bool> visited;
    vector<ll> sscnum;
    vector<ll> s;
    ll counter;

    bool doit (ll nin, vector<pair<ll,ll>> &orterms, vector<bool> &sol) {
        // Step 1, set up the graph.
        // Coming in, positives represent true variables and negatives represent false variables
        // Internally, variables 1-n represent true variables and variables n+1-2n represent false variables
        n = nin;
        adj.clear();
        adj.resize(2*n+1);
        sscnum.assign(2*n+1,0);
        for (auto p : orterms) {
            ll first     = p.first > 0 ? p.first : n - p.first;
            ll second    = p.second > 0 ? p.second : n - p.second;
            ll notfirst  = first <= n ? first + n : first - n;
            ll notsecond = second <= n ? second + n : second - n;
            adj[notfirst].push_back(second);
            adj[notsecond].push_back(first); 
        }

        // Step 2, do kosaraju
        kosaraju();

        // Step 3, do variable assignments
        sol.assign(2*n+1,false);
        vector<vector<ll>> ssc(counter);
        FORE(i,1,n)   { if (sscnum[i] == sscnum[n+i]) return false; }
        FORE(i,1,2*n) { ssc[sscnum[i]].push_back(i); }
        REP(i,counter) {
            bool sscval = false;
            for (auto nn : ssc[i]) {
                if (sol[nn]) { sscval = true; break; } 
            }
            for (auto nn : ssc[i]) {
                sol[nn] = sscval;
                if (nn <= n) sol[nn+n] = !sscval;
                else         sol[nn-n] = !sscval;
            }
        }
        sol.resize(n+1);  //Discard the "false" variables -- don't need them
        return true;
    }

    void kosaraju() {
        visited.assign(2*n+1,false);
        s.clear();
        counter = 0;
        makeInv();
        FORE(nn,1,2*n) { if (!visited[nn]) dfs1(nn); }
        visited.assign(2*n+1,false);
        reverse(s.begin(),s.end());
        for (auto nn : s) { if (!visited[nn]) { dfs2(nn); counter++; } }
    }

    void makeInv() {
        adjInv.clear();
        adjInv.resize(2*n+1);
        FORE(nn,1,2*n) {
            for (auto nn2 : adj[nn]) { adjInv[nn2].push_back(nn); }
        }
    } 

    void dfs1(ll nn) {
        if (visited[nn]) return;
        visited[nn] = true;
        for (auto nn2 : adj[nn]) dfs1(nn2);
        s.push_back(nn);
    }

    void dfs2(ll nn) {
        if (visited[nn]) return;
        visited[nn] = true;
        for (auto nn2 : adjInv[nn]) dfs2(nn2);
        sscnum[nn] = counter;
    }
};







int main() {
    return 0;
}
