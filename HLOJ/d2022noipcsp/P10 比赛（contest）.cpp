// 2022.10.02

#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
long long gcd(long long x,long long y){
    if(y==0)return x;
    return gcd(y,x%y);
}
long long power(long long x,long long n=mod-2){
    if(n==0)return 1ll;
    long long tmp=power(x,n>>1ll);
    tmp=tmp*tmp%mod;
    if(n&1ll)tmp=tmp*x%mod;
    return tmp;
}

long long dp[1000001],p[1000001],q[1000001];
// dp[k] 表示 从 n 个人中选出 k 个人颁奖的概率
long long fac[1000001],invfac[1000001];

int main(){
    freopen("contest.in","r",stdin);
    freopen("contest.out","w",stdout);
    int n; long long a,b;
    scanf("%d%lld%lld",&n,&a,&b);
    long long GCD=gcd(a,b);
    a/=GCD,b/=GCD;
    if((a<<1)!=b){
        p[0]=q[0]=dp[0]=1;
        p[1]=a*power(b)%mod;
        q[1]=1-p[1],q[1]+=mod,q[1]%=mod;
        for(int i=2;i<=n;i++)
            p[i]=p[i-1]*p[1]%mod,
            q[i]=q[i-1]*q[1]%mod;
        for(int i=1;i<n;i++)
            dp[i]=dp[i-1]*(p[n-i+1]-q[n-i+1]+mod)%mod
                *power(p[i]-q[i]+mod)%mod;
    }
    else{
        fac[0]=1;
        for(int i=1;i<=n;i++)
            fac[i]=fac[i-1]*i%mod;
        invfac[n]=power(fac[n]);
        for(int i=n;i>=1;i--)
            invfac[i-1]=invfac[i]*i%mod;
        for(int k=1;k<n;k++){
            dp[k]=fac[n]*invfac[k]%mod*invfac[n-k]%mod;
            dp[k]=dp[k]*power(power(2,k*(n-k)))%mod;
        }
    }
    long long answer=0,f=1;
    for(int i=1;i<n;i++,f=(f*f+2)%mod)
        answer+=dp[i]*f%mod,answer%=mod;
    printf("%lld\n",answer);
    return 0;
}