// 2022.07.27

#include<bits/stdc++.h>
using namespace std;
const int mod=10007;

int n,w[200001];

struct Edge{
    int to,nxt;
}edge[400001];
int head[200001],cntEdge;
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

int s[200001],f[200001],g[200001];
// s: 孩子权值和
// f: 孩子权值最大值
// g: 孩子权值次大值
long long sum;
int maxn;
void dfs(int id,int father){
    for(int i=head[id];i;i=edge[i].nxt){
        int to=edge[i].to;
        if(to==father)continue;
        dfs(to,id);
        s[id]+=w[to];
        if(w[to]>f[id])g[id]=f[id],f[id]=w[to];
        else if(w[to]>g[id])g[id]=w[to];
        sum+=2ll*w[id]*s[to];
        maxn=max(maxn,w[id]*f[to]);
        sum%=mod;
    }
    for(int i=head[id];i;i=edge[i].nxt){
        int to=edge[i].to;
        if(to==father)continue;
        sum+=w[to]*1ll*(s[id]-w[to]);
        sum%=mod;
    }
    maxn=max(maxn,f[id]*g[id]);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",w+i);
    dfs(1,0);
    printf("%d %lld\n",maxn,sum);
    return 0;
}