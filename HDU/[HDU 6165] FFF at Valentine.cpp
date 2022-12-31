// 2022.12.31

#include <bits/stdc++.h>
using namespace std;

struct Edge{
    int to,nxt;
};

struct Graph{
    Edge edge[6001];
    int head[1001],cntEdge;
    void init(){
        memset(head,0,sizeof head);
        cntEdge=0;
    }
    void addEdge(int u,int v){
        edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
    }
}A,B;

int N,M,n,m;

int dfn[1001],low[1001],maxdfn,newid[1001];
bool vis[1001]; stack<int> S;
void initTarjan(){
    memset(dfn,0,sizeof dfn);
    memset(low,0,sizeof low);
    memset(newid,0,sizeof newid);
    memset(vis,false,sizeof vis);
    while(!S.empty())S.pop();
    maxdfn=n=m=0;
}
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
        do
            u=S.top(),S.pop(),
            vis[u]=false,
            newid[u]=n;
        while(u!=id);
    }
}

int in[1001];

int main(){
    int T; scanf("%d",&T);
    while(T--){
        A.init(); B.init();
        scanf("%d%d",&N,&M);
        for(int i=1;i<=M;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            A.addEdge(u,v);
        }
        initTarjan();
        for(int i=1;i<=N;i++)
            if(!dfn[i])Tarjan(i,0);
        memset(in,0,sizeof in);
        for(int id=1;id<=N;id++)
            for(int i=A.head[id];i;i=A.edge[i].nxt)
                if(newid[A.edge[i].to]!=newid[id])
                    B.addEdge(newid[id],newid[A.edge[i].to]),
                    m++,in[newid[A.edge[i].to]]++;
        queue<int> Q;
        int total=0;
        bool fail=false;
        for(int i=1;i<=n;i++)
            if(in[i]==0)Q.push(i),total++;
        if(total>1)fail=true;
        while(!Q.empty()&&!fail){
            int id=Q.front(); Q.pop(),total=0;
            for(int i=B.head[id];i;i=B.edge[i].nxt)
                if(!(--in[B.edge[i].to]))Q.push(B.edge[i].to),total++;
            if(total>1)fail=true;
        }
        if(fail)printf("Light my fire!\n");
        else printf("I love you my love and our love save us!\n");
    }
    return 0;
}