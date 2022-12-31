// 2022.12.21

#include <bits/stdc++.h>
using namespace std;
const long long mod=1e9+7;
long long power(long long a,long long n=mod-2){
    long long res=1;
    while(n){
        if(n&1)res=res*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return res;
}

struct Edge{
    int to,nxt;
};

struct Graph{
    Edge edge[2000001];
    int head[500001],cntEdge;
    void init(){
        memset(head,0,sizeof head);
        cntEdge=0;
    }
    void addEdge(int u,int v){
        edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
    }
}A,B;

int N,M,n,m,v[500001],e[500001],sume[500001];
// v/e[i]: 编号为 i 的边双中的点数 / 边数
// sume[i]: 以 i 为根的子树中的总边数（包括边双内部边）

int dfn[500001],low[500001],maxdfn,newid[500001];
bool vis[500001]; stack<int> S;
void Tarjan(int id,int father){
    maxdfn++,dfn[id]=low[id]=maxdfn;
    vis[id]=true, S.push(id);
    for(int i=A.head[id];i;i=A.edge[i].nxt){
        int to=A.edge[i].to;
        if(to==father)continue;
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
            newid[u]=n,v[n]++;
        while(u!=id);
    }
}

void dfs_calcsume(int id,int father){
    sume[id]=e[id];
    for(int i=B.head[id];i;i=B.edge[i].nxt)
        if(B.edge[i].to!=father){
            dfs_calcsume(B.edge[i].to,id);
            sume[id]+=sume[B.edge[i].to]+1;
        }
}

long long dp[500001][2],answer;
// dp[i][0/1]: 以 i 为根的子树中不建造 / 建造军营的方案数（若有军营，则所有的军营必须保持与 i 连通）

void dpontree(int id,int father){
    for(int i=B.head[id];i;i=B.edge[i].nxt)
        if(B.edge[i].to!=father){
            int to=B.edge[i].to;
            dpontree(to,id);
            dp[id][1]=dp[id][0]*dp[to][1]%mod+(dp[to][0]*2+dp[to][1])%mod*dp[id][1]%mod;
            dp[id][1]%=mod, dp[id][0]*=dp[to][0]*2%mod, dp[id][0]%=mod;
        }
    if(father==0)answer+=dp[id][1];
    else answer+=dp[id][1]*power(2,sume[1]-sume[id]-1)%mod;
    answer%=mod;
}

int main(){
    freopen("barrack.in","r",stdin);
    freopen("barrack.out","w",stdout);
    A.init(); B.init();
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        A.addEdge(u,v);
        A.addEdge(v,u);
    }
    Tarjan(1,0);
    for(int id=1;id<=N;id++)
        for(int i=A.head[id];i;i=A.edge[i].nxt)
            if(newid[A.edge[i].to]==newid[id])e[newid[id]]++;
            else B.addEdge(newid[id],newid[A.edge[i].to]);
    for(int i=1;i<=n;i++){
        e[i]>>=1, dp[i][0]=power(2,e[i]);
        dp[i][1]=power(2,v[i]+e[i])-dp[i][0];
        dp[i][1]=(dp[i][1]%mod+mod)%mod;
    }
    dfs_calcsume(1,0);
    dpontree(1,0);
    printf("%lld\n",answer);
    return 0;
}