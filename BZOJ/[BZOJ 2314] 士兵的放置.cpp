// 2022.07.30

#include<bits/stdc++.h>
using namespace std;
const long long mod=1032992941ll;

int n;

struct Edge{
    int to,nxt;
}edge[1000001];
int head[500001],cntEdge;
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

long long f[500001][3],g[500001][3];
/* f/g[id][0/1/2]: 节点 id 被自己/儿子/父亲支配时，
   以 id 为根的子树的最小支配集大小/方案总数 */

void dp(int id,int father){
    long long minval;
    f[id][0]=1,f[id][1]=1919810,f[id][2]=0;
    g[id][0]=g[id][1]=g[id][2]=1;
    for(int i=head[id];i;i=edge[i].nxt){
        int to=edge[i].to;
        if(to==father)continue;
        dp(to,id);

        minval=min(f[to][0],min(f[to][1],f[to][2]));
        g[id][0]*=(f[to][0]==minval?g[to][0]:0)
                 +(f[to][1]==minval?g[to][1]:0)
                 +(f[to][2]==minval?g[to][2]:0);
        g[id][0]%=mod;
        f[id][0]+=minval;

        minval=min(min(f[id][1]+f[to][0],f[id][1]+f[to][1]),f[id][2]+f[to][0]);
        g[id][1]=(f[id][1]+f[to][0]==minval?g[id][1]*g[to][0]%mod:0)
                +(f[id][1]+f[to][1]==minval?g[id][1]*g[to][1]%mod:0)
                +(f[id][2]+f[to][0]==minval?g[id][2]*g[to][0]%mod:0);
        g[id][1]%=mod;
        f[id][1]=minval;

        f[id][2]+=f[to][1];
        g[id][2]*=g[to][1];
        g[id][2]%=mod;
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dp(1,0);
    printf("%lld\n%lld\n",min(f[1][0],f[1][1]),
        ((f[1][0]==min(f[1][0],f[1][1])?g[1][0]:0)
        +(f[1][1]==min(f[1][0],f[1][1])?g[1][1]:0))%mod);
    return 0;
}