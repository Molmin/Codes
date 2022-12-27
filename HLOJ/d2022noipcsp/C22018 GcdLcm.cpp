// 2022.10.25

#include<bits/stdc++.h>
using namespace std;

const long long mod=1e9+9;

long long power(long long a,long long n=mod-2){
    if(n==0)return 1;
    long long tmp=power(a,n>>1);
    tmp=tmp*tmp%mod;
    if(n&1)tmp=tmp*a%mod;
    return tmp;
}

long long n,d,m;

long long worker(int x,long long n){
    long long sum=0;
    sum+=power(x+1,n);
    sum-=2*power(x,n);
    sum+=power(x-1,n);
    sum%=mod;
    sum+=mod;
    sum%=mod;
    return sum;
}

int main(){
    freopen("gcdlcm.in","r",stdin);
    freopen("gcdlcm.out","w",stdout);
    scanf("%lld%lld%lld",&n,&d,&m);
    if(m%d)return printf("0\n"),0;
    m/=d;
    long long answer=1;
    for(int i=2;i<=sqrt(m);i++){
        int total=0;
        while(m%i==0)total++,m/=i;
        if(total){
            answer*=worker(total,n);
            answer%=mod;
        }
    }
    if(m>1){
        answer*=worker(1,n);
        answer%=mod;
    }
    printf("%lld\n",answer);
    return 0;
}