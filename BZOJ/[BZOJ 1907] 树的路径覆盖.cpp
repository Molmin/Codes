// 2022.07.27

#include<bits/stdc++.h>
using namespace std;

namespace solve{
    int n;

    struct Edge{
        int to,nxt;
    }edge[20001];
    int head[10001],cntEdge;
    inline void addEdge(int u,int v){
        edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
    }

    int dp[10001]; // 以 i 为根的子树最少链条数
    bool p[10001]; // 取到最小值时，i 节点是否为链的一端
    void dfs(int id,int father){
        dp[id]=p[id]=0;
        int total=0;
        for(int i=head[id];i;i=edge[i].nxt){
            int to=edge[i].to;
            if(to==father)continue;
            dfs(to,id);
            dp[id]+=dp[to];
            if(p[to])total++;
        } 
        if(total>1)dp[id]--;
        else if(total==1)p[id]=true;
        else dp[id]++,p[id]=true;
    }

    void main(){
        cntEdge=0;
        memset(head,0,sizeof head);
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        dfs(1,0);
        printf("%d\n",dp[1]);
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--)
        solve::main();
    return 0;
}