const int N = 100005;
const int E = 2000006;
vector<int> g[N];

int ne;
struct Edge{
    int from, to;
    ll flow, cap;
} edge[E];

int lvl[N], vis[N], pass, source = N-2, target = N-1;
int qu[N], qt, px[N];

ll run(int s, ll minE){
    if(s == target) return minE;

    ll ans = 0;

    for(; px[s] < (int)g[s].size(); px[s]++){
        int e = g[s][ px[s] ];
        auto &v = edge[e], &rev = edge[e^1];
        if(lvl[v.to] != lvl[s]+1 || v.flow >= v.cap) continue;
        ll tmp = run(v.to, min(minE, v.cap-v.flow));
        v.flow += tmp, rev.flow -= tmp;
        ans += tmp, minE -= tmp;
        if(minE == 0) break;
    }
    return ans;
}

bool bfs(){
    qt = 0;
    qu[qt++] = source;
    lvl[source] = 1;
    vis[source] = ++pass;

    for(int i = 0; i < qt; i++){
        int u = qu[i];
        px[u] = 0;
		if(u == target) return true;

        for(int e : g[u]){
            auto v = edge[e];
            if(v.flow >= v.cap || vis[v.to] == pass) continue;
            vis[v.to] = pass;
            lvl[v.to] = lvl[u] + 1;
            qu[qt++] = v.to;
        }
    }
    return false;
}

ll flow(){
    ll ans = 0;
    while(bfs()) ans += run(source, oo);
    return ans;
}

void addEdge(int u, int v, ll c = 1, ll rc = 0){
    edge[ne] = {u, v, 0, c};
    g[u].push_back(ne++);
    edge[ne] = {v, u, 0, rc};
    g[v].push_back(ne++);
}

void reset_flow(){
	for(int i = 0; i < ne; i++)
		edge[i].flow = 0;
}
