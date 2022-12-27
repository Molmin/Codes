// 2022.10.02

#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
long long power(long long x,long long n=mod-2){
    if(n==0)return 1ll;
    long long tmp=power(x,n>>1ll);
    tmp=tmp*tmp%mod;
    if(n&1ll)tmp=tmp*x%mod;
    return tmp;
}
long long fac[100001],invfac[100001];
void initfac(int N){
    fac[0]=1;
    for(int i=1;i<=N;i++)
        fac[i]=fac[i-1]*i%mod;
    invfac[N]=power(fac[N]);
    for(int i=N;i>=1;i--)
        invfac[i-1]=invfac[i]*i%mod;
}
long long C(int m,int n){
    if(n<0||m<0||n>m)return 0;
    return fac[m]*invfac[n]%mod*invfac[m-n]%mod;
}

struct Edge{
    int to,nxt;
}edge[200001];
int head[100001],cntEdge;
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]};
    head[u]=cntEdge;
}
int n;
void readTree(){
    memset(head,0,sizeof head);
    cntEdge=0;
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        int x; scanf("%d",&x);
        addEdge(x,i);
    }
}
bool win[100001];
bool getTreeType(bool endcanwin){
    for(int i=n;i>=1;i--)
        if(head[i]==0)win[i]=!endcanwin;
        else{
            win[i]=false;
            for(int j=head[i];j;j=edge[j].nxt)
                if(!win[edge[j].to])win[i]=true;
        }
    return !win[1];
}

int main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    int m;
    scanf("%d",&m);
    initfac(m);
    long long answer=power(2,m);
    int total[2][2]={};
    while(m--){
        readTree();
        total[getTreeType(true)][getTreeType(false)]++;
    }
    long long sum=0;
    for(int i=0;i<=total[0][1];i+=2)
        sum+=C(total[0][1],i),sum%=mod;
    answer-=power(2,total[1][0]+total[0][0])*sum%mod;
    printf("%lld\n",(answer+mod)%mod);
    return 0;
}