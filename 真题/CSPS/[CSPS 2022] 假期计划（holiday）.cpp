// 2022.11.11

#include<bits/stdc++.h>
using namespace std;

int n,m,k,d[2501][2501];
long long s[2501];

struct Edge{
    int to,nxt;
}edge[20001];
int head[2501],cntEdge;
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

int c[2501];
long long dp[2501];
vector<int> to[2501];
long long dfs(int id,int color){
    if(dp[id]!=-1)return dp[id];
    dp[id]=-5e18;
    if(color==3){
        if(d[1][id]<=k)dp[id]=s[id];
    }
    else{
        for(int v:to[id])
            if(c[v]==color+1)
                dp[id]=max(dp[id],dfs(v,color+1)+s[id]);
    }
    return dp[id];
}

int main(){
    freopen("holiday.in","r",stdin);
    freopen("holiday.out","w",stdout);
    srand(time(0));
    scanf("%d%d%d",&n,&m,&k);
    for(int i=2;i<=n;i++)
        scanf("%lld",s+i);
    memset(d,0x3f,sizeof d);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        d[u][v]=0;
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        queue<pair<int,int> > Q;
        bool vis[2501]={};
        vis[i]=true;
        for(int j=head[i];j;j=edge[j].nxt)
            vis[edge[j].to]=true,Q.push({edge[j].to,0});
        while(!Q.empty()){
            int id=Q.front().first,stp=Q.front().second;
            d[i][id]=stp;
            Q.pop();
            for(int j=head[id];j;j=edge[j].nxt)
                if(!vis[edge[j].to])
                    Q.push({edge[j].to,stp+1}),
                    vis[edge[j].to]=true;
        }
    }
    long long answer=0;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(d[i][j]<=k){
                to[i].push_back(j);
                to[j].push_back(i);
            }
    while(clock()<3.5*CLOCKS_PER_SEC){
        for(int i=2;i<=n;i++)c[i]=rand()&3;
        memset(dp,0xff,sizeof dp);
        answer=max(answer,dfs(1,-1));
    }
    printf("%lld\n",answer);
    return 0;
}