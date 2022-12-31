// 2022.07.27

#include<bits/stdc++.h>
using namespace std;
const long long Inf=0x3f3f3f3f3f3f;

int n;

struct Edge{
    int to,nxt;
}edge[2001];
int head[1001],cntEdge;
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

long long dp[1001][5];
/* dp[id][0/1/2/3/4]: 在以 id 为根的子树内，
   id 被自己/儿子/孙子/爷爷/父亲支配的最小支配集大小 */
inline long long Min(int id,int l,int r){
    long long minn=Inf;
    for(int i=l;i<=r;i++)
        minn=min(minn,dp[id][i]);
    return minn;
}
void dfs(int id,int father){
    dp[id][0]=1,dp[id][1]=dp[id][2]=Inf;
    long long s1=0,s2=0;
    for(int i=head[id];i;i=edge[i].nxt){
        int to=edge[i].to;
        if(to==father)continue;
        dfs(to,id);
        s1+=Min(to,0,3),s2+=Min(to,1,2);
    } 
    for(int i=head[id];i;i=edge[i].nxt){
        int to=edge[i].to;
        if(to==father)continue;
        dp[id][0]+=Min(to,0,4);
        dp[id][1]=min(dp[id][1],s1-Min(to,0,3)+dp[to][0]);
        dp[id][2]=min(dp[id][2],s2-Min(to,1,2)+dp[to][1]);
        dp[id][3]+=Min(to,0,2);
        dp[id][4]+=Min(to,0,3);
    } 
}

int main(){
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        int x;
        scanf("%d",&x);
        addEdge(i,x);
        addEdge(x,i); 
    }
    dfs(1,0);
    printf("%lld\n",Min(1,0,2));
    return 0;
}