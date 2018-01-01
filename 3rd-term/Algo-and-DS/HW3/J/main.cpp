#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <sstream>

using namespace std;

const int inf = int(1e9);

struct edge {
    int v, flow, cap, cost, next;
    int num;
} e[100000];


int n, k, ff, S, T, N;
int a[100000], an, first[100000], phi[100000], d[100000], res[100000];
int s[100000], t[100000], c[100000], from[100000], with[100000];
priority_queue < pair<int,int> , vector <pair<int,int> >, greater <pair<int,int> > > pq;

int Find(int x) {
    return lower_bound(a, a + an, x) - a;
}

void addEdge(int u, int v, int cap, int cost, int num) {
    e[ff].v = v, e[ff].cap = cap, e[ff].flow = 0, e[ff].cost = cost, e[ff].next = first[u], e[ff].num = num, first[u] = ff++;
    e[ff].v = u, e[ff].cap = 0, e[ff].flow = 0, e[ff].cost = -cost, e[ff].next = first[v], first[v] = ff++;
}

int minCostMaxFlow() {
    for (int i = 0; i < N; ++i)
        phi[i] = inf;
    phi[S] = 0;
    for (int i = 0; i < N; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int j = first[u]; j != -1; j = e[j].next) if (e[j].flow < e[j].cap) {
                    int v= e[j].v;
                    if (phi[v] > phi[u] + e[j].cost) {
                        phi[v] = phi[u] + e[j].cost;
                    }
                }
        }
    }
    int res = 0;
    for (int iter = 0; iter < k; ++iter) {
        for (int i = 0; i < N; ++i)
            d[i] = inf;
        d[S] = 0;
        pq.push(make_pair(d[S], S));
        while (!pq.empty()) {
            pair<int,int>  top = pq.top();
            pq.pop();
            int u = top.second;
            if (d[u] < top.first) continue;
            for (int i = first[u]; i != -1; i = e[i].next) if (e[i].flow < e[i].cap) {
                    int v = e[i].v;
                    if (d[v] > d[u] + phi[u] - phi[v] + e[i].cost) {
                        d[v] = d[u] + phi[u] - phi[v] + e[i].cost;
                        with[v] = i;
                        pq.push(make_pair(d[v], v));
                    }
                }
        }
        if (d[T] == inf) break;
        for (int i = 0; i < N; ++i) if (d[i] < inf)
                phi[i] += d[i];

        for (int u = T; u != S; ) {
            int i = with[u];
            int j = i ^ 1;
            ++e[i].flow;
            res += e[i].cost;
            --e[j].flow;
            u = e[j].v;
        }
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d", &s[i], &t[i], &c[i]);
        a[an++] = s[i];
        a[an++] = s[i] + t[i];
    }
    sort(a, a + an);
    an = unique(a, a + an) - a;

    S = an;
    T = S + 1;
    N = T + 1;
    memset(first, -1, sizeof(first));

    addEdge(S, 0, k, 0, -1);
    for (int i = 0; i + 1 < an; ++i)
        addEdge(i, i + 1, k, 0, -1);

    for (int i = 0; i < n; ++i) {
        int u = Find(s[i]);
        int v = Find(s[i] + t[i]);
        addEdge(u, v, 1, -c[i],  i);
    }
    addEdge(an - 1, T, k, 0, -1);

    int ans = minCostMaxFlow();

    for (int u = 0; u < N; ++u) {
        for (int i = first[u]; i != -1; i = e[i].next) if (e[i].flow == 1) {
                int nn = e[i].num;
                if (nn != -1)
                    res[nn] = 1;
            }
    }
    for (int i = 0; i < n; ++i) {
        if (i > 0) putchar(' ');
        printf("%d", res[i]);
    }
    return 0;
}