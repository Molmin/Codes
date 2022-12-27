// 2022.09.29

#include<bits/stdc++.h>
using namespace std;

long long gcd(long long a,long long b){
    return b==0?a:gcd(b,a%b);
}

long long work(long long a,long long b){
    if(a==b)return 1;
    if(a==0)return 0;
    if(a<b)return work(b,a);
    return a/b+work(a%b,b);
}

int main(){
    freopen("r.in","r",stdin);
    freopen("r.out","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--){
        long long a,b;
        scanf("%lld%lld",&a,&b);
        printf("%lld\n",work(a/gcd(a,b),b/gcd(a,b)));
    }
    return 0;
}