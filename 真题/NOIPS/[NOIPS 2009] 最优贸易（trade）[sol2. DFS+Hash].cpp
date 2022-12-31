// 2022.12.29

#include <bits/stdc++.h>
using namespace std;

struct Edge{
    int to,nxt;
}edge[2000001];
int head[100001],cntEdge;
void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

int n,m,w[100001],answer;
const long long mod=137778806;
bool vis[mod];
int Hash(int id,int typ,int ans){
    return ((id*1377ll+typ*788ll+ans*618ll)%mod+mod)%mod;
}

void dfs(int id,int typ,int ans){
    int hashval=Hash(id,typ,ans);
    if(vis[hashval])return;
    if(typ==3&&ans<=answer)return;
    if(typ==3&&id==n){
        answer=ans;
        return;
    }
    vis[hashval]=true;
    if(typ==1){
        for(int i=head[id];i;i=edge[i].nxt){
            dfs(edge[i].to,2,w[id]);
            dfs(edge[i].to,1,0);
        }
    }
    if(typ==2){
        for(int i=head[id];i;i=edge[i].nxt){
            dfs(edge[i].to,3,w[id]-ans);
            dfs(edge[i].to,2,ans);
        }
    }
    if(typ==3){
        for(int i=head[id];i;i=edge[i].nxt)
            dfs(edge[i].to,3,ans);
    }
}

int main(){
    freopen("trade.in","r",stdin);
    freopen("trade.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",w+i);
    for(int i=1;i<=m;i++){
        int u,v,typ;
        scanf("%d%d%d",&u,&v,&typ);
        addEdge(u,v);
        if(typ==2)addEdge(v,u);
    }
    dfs(1,1,0);
    printf("%d\n",answer);
    return 0;
}