// 2022.08.02

#include<bits/stdc++.h>
using namespace std;
int p;

long long power(long long m,long long n=p-2){
    if(n==0)return 1;
    long long tmp=power(m,n>>1);
    tmp=tmp*tmp%p;
    if(n&1)tmp=tmp*m%p;
    return tmp;
}

bool isp[2000001];
int cnt,prime[150000];
void getprimes(int N=2000000){
    memset(isp,true,sizeof isp);
    isp[0]=isp[1]=false;
    for(int i=2;i<=N;i++)
        if(isp[i]){
            prime[++cnt]=i;
            for(int j=i<<1;j<=N;j+=i)
                isp[j]=false;
        }
}
inline int Vp(int pid,int n){
    int cnt=0;
    while(n)cnt+=n/prime[pid],n/=prime[pid];
    return cnt;
}

int main(){
    int n;
    scanf("%d%d",&n,&p);
    getprimes();
    long long answer=1;
    for(int i=1;i<=cnt&&prime[i]<(n<<1);i++)
        answer=answer*power(prime[i],Vp(i,n<<1)-Vp(i,n+1)-Vp(i,n))%p;
    printf("%lld\n",answer);
    return 0;
}