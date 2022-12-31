// 2022.12.29

#include <bits/stdc++.h>
using namespace std;

struct Edge{
    int to,nxt;
};

struct Graph{
    Edge edge[2000001];
    int head[100001],cntEdge;
    void init(){
        memset(head,0,sizeof head);
        cntEdge=0;
    }
    void addEdge(int u,int v){
        edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
    }
}A,B;

int N,M,n,m;
int w[100001],w1[100001],w2[100001];

int dfn[100001],low[100001],maxdfn,newid[100001];
bool vis[100001]; stack<int> S;
void Tarjan(int id,int father){
    maxdfn++,dfn[id]=low[id]=maxdfn;
    vis[id]=true, S.push(id);
    for(int i=A.head[id];i;i=A.edge[i].nxt){
        int to=A.edge[i].to;
        if(dfn[to]==0){
            Tarjan(to,id);
            low[id]=min(low[id],low[to]);
        }
        else if(vis[to])low[id]=min(low[id],dfn[to]);
    }
    if(dfn[id]==low[id]){
        n++; int u;
        w1[n]=w2[n]=w[S.top()];
        do
            u=S.top(),S.pop(),
            vis[u]=false,
            newid[u]=n,
            w1[n]=min(w1[n],w[u]),
            w2[n]=max(w2[n],w[u]);
        while(u!=id);
    }
}

int f[100001],g[100001],in[100001];
// f[i]: 从 1 到 i 的路径上的最小花费
// g[i]: 表示从 1 开始，到 i 为止，最大收入的贸易方式

int main(){
    freopen("trade.in","r",stdin);
    freopen("trade.out","w",stdout);
    A.init(); B.init();
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;i++)
        scanf("%d",w+i);
    for(int i=1;i<=M;i++){
        int u,v,typ;
        scanf("%d%d%d",&u,&v,&typ);
        A.addEdge(u,v);
        if(typ==2)A.addEdge(v,u);
    }
    Tarjan(1,0);
    for(int id=1;id<=N;id++)
        for(int i=A.head[id];i;i=A.edge[i].nxt)
            if(newid[A.edge[i].to]!=newid[id])
                B.addEdge(newid[id],newid[A.edge[i].to]),
                m++,in[newid[A.edge[i].to]]++;
    for(int i=1;i<=n;i++)
        f[i]=w1[i],g[i]=w2[i]-w1[i];
    queue<int> Q;
    Q.push(newid[1]);
    while(!Q.empty()){
        int u=Q.front(); Q.pop();
        for(int i=B.head[u];i;i=B.edge[i].nxt){
            int v=B.edge[i].to;
            f[v]=min(f[u],f[v]);
            g[v]=max(g[v],max(g[u],w2[v]-f[u]));
            in[v]--;
            if(in[v]==0)Q.push(v);
        }
    }
    printf("%d\n",g[newid[N]]);
    return 0;
}