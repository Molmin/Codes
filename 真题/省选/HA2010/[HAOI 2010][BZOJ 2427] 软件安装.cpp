// 2022.07.26

#include<bits/stdc++.h>
using namespace std;

int n,m,deg[101],w[101],v[101];

struct Edge{
    int from,to,nxt;
}edge[101];
int cntEdge,head[101],f[101];
inline void addEdge(int u,int v){
    edge[++cntEdge]={u,v,head[u]},head[u]=cntEdge;
}

int viscnt,dfn[101],low[101];
bool vis[101];
stack<int> S;
int newid[101];
void Tarjan(int id){
    viscnt++,dfn[id]=low[id]=viscnt;
    S.push(id),vis[id]=true;
    for(int i=head[id];i;i=edge[i].nxt){
        if(!dfn[edge[i].to]){
            Tarjan(edge[i].to);
            low[id]=min(low[id],low[edge[i].to]);
        }
        else if(vis[edge[i].to])
            low[id]=min(low[id],low[edge[i].to]);
    }
    if(dfn[id]==low[id]){
        while(!S.empty()){
            int x=S.top(); S.pop();
            newid[x]=id,vis[x]=false;
            if(x==id)break;
            w[id]+=w[x],v[id]+=v[x];
        }
    }
}

struct Edge_{
    int to,nxt;
}edge_[101];
int cntEdge_,head_[101];
inline void addEdge_(int u,int v){
    edge_[++cntEdge_]={v,head_[u]},head_[u]=cntEdge_;
}

int dp[101][501];
void dfs(int id){
    // if(sum<=0)return;
    for(int i=w[id];i<=m;i++)dp[id][i]=v[id];
    for(int i=head_[id];i;i=edge_[i].nxt){
        int v=edge_[i].to; dfs(v);
        for(int j=m-w[id];j>=0;j--)
            for(int k=0;k<=j;k++)
                dp[id][j+w[id]]=max(dp[id][j+w[id]],dp[id][j+w[id]-k]+dp[v][k]);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",w+i);
    for(int i=1;i<=n;i++)
        scanf("%d",v+i);
    for(int i=1;i<=n;i++){
        scanf("%d",f+i);
        if(f[i])addEdge(f[i],i);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i])Tarjan(i);
    for(int i=1;i<=cntEdge;i++)
        if(newid[edge[i].from]!=newid[edge[i].to])
            addEdge_(newid[edge[i].from],newid[edge[i].to]),deg[newid[edge[i].to]]++;
    for(int i=1;i<=n;i++)
        if(!deg[i])addEdge_(0,newid[i]);
    dfs(0);
    printf("%d\n",dp[0][m]);
    return 0;
}