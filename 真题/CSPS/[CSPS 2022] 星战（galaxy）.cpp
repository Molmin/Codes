// 2022.11.10

#include<bits/stdc++.h>
using namespace std;

long long randll(){
    long long a=rand();
    a<<=31, a+=rand();
    return a&((1ll<<44)-1);
}

int n,m,q;
long long w[500001],s[500001];
long long deg[500001],sumdeg,ansdeg;

int main(){
    freopen("galaxy.in","r",stdin);
    freopen("galaxy.out","w",stdout);
    srand(time(0));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        w[i]=randll(),ansdeg+=w[i];
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        s[v]+=w[u],deg[v]+=w[u];
        sumdeg+=w[u];
    }
    scanf("%d",&q);
    while(q--){
        int op,u,v;
        scanf("%d",&op);
        switch(op){
            case 1:
                scanf("%d%d",&u,&v);
                sumdeg-=w[u];
                deg[v]-=w[u];
                break;
            case 2:
                scanf("%d",&v);
                sumdeg-=deg[v];
                deg[v]=0;
                break;
            case 3:
                scanf("%d%d",&u,&v);
                sumdeg+=w[u];
                deg[v]+=w[u];
                break;
            case 4:
                scanf("%d",&v);
                sumdeg-=deg[v];
                deg[v]=s[v];
                sumdeg+=s[v];
                break;
        }
        if(sumdeg==ansdeg)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}