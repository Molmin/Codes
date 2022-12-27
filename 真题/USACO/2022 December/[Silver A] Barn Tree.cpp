// 2022.12.25

#include<bits/stdc++.h>
using namespace std;

struct Edge{
    int to,nxt;
}edge[400001];
int head[200001],cntEdge;
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

struct Op{
    int s,t;
    long long w;
}ops[200001];
int cnt;

int n,h[200001],siz[200001];
long long sum,up[200001];

long long calcup(int id,int father){
    siz[id]=1;
    long long res=h[id];
    for(int i=head[id];i;i=edge[i].nxt)
        if(edge[i].to!=father){
            long long s=calcup(edge[i].to,id);
            up[edge[i].to]=s-sum;
            res+=up[edge[i].to];
            siz[id]+=siz[edge[i].to];
        }
    return res;
}

void getanswer(int id,int father){
    vector<pair<long long,int> > children;
    int cntchildren=0;
    for(int i=head[id];i;i=edge[i].nxt)
        if(edge[i].to!=father)
            children.push_back({up[edge[i].to],edge[i].to});
    for(auto i:children){
        if(i.first==0)
            getanswer(i.second,id);
        else if(i.first>0){
            getanswer(i.second,id);
            ops[++cnt]={i.second,id,i.first};
        }
    }
    for(auto i:children){
        if(i.first<0){
            ops[++cnt]={id,i.second,-i.first};
            getanswer(i.second,id);
        }
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",h+i),sum+=h[i];
    sum/=n;
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    calcup(1,0);
    getanswer(1,0);
    printf("%d\n",cnt);
    for(int i=1;i<=cnt;i++)
        printf("%d %d %lld\n",ops[i].s,ops[i].t,ops[i].w);
    return 0;
}