// 2022.07.26

#include<bits/stdc++.h>
using namespace std;

int n;
map<pair<int,int>,int> M;

struct Edge{
    int to,nxt;
}edge[400001];
int head[200001],cntEdge;

void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

void add(int x,int y,int id){
    if(x>y)swap(x,y);
    if(M[{x,y}]){
        addEdge(id,M[{x,y}]);
        addEdge(M[{x,y}],id);
    }
    else M[{x,y}]=id;
}

int f[200001],g[200001],ans;
void dp(int id,int father){
    for(int i=head[id];i;i=edge[i].nxt)
        if(edge[i].to!=father){
            int v=edge[i].to;
            dp(v,id);
            if(f[v]+1>f[id])g[id]=f[id],f[id]=f[v]+1;
            else if(f[v]+1>g[id])g[id]=f[v]+1;
        }
    ans=max(ans,f[id]+g[id]);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n-2;i++){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,i);
        add(c,b,i);
        add(a,c,i);
    }
    dp(1,0);
    printf("%d\n",ans+1);
    return 0;
}