// 2022.09.29

#include<bits/stdc++.h>
using namespace std;
const long double one=(long double)1.0;

inline bool check(long long b,long long y,long long l){
    if(b<10)return false;
    long long to=0,mul=1;
    while(y){
        if(y%b>9)return false;
        to+=mul*(y%b);
        y/=b;
        mul*=10;
    }
    return to>=l;
}

int main(){
    freopen("age.in","r",stdin);
    freopen("age.out","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--){
        long long y,l,answer=10;
        scanf("%lld%lld",&y,&l);
        for(int i=max(10ll,l);i<=99;i++){
            int a0=i%10,a1=i/10;
            // 枚举转换后的结果,则 a1*b+a0=y
            long long b0=(y-a0)/a1;
            for(long long b=b0-3;b<=b0+3;b++)
                if(check(b,y,l))answer=max(answer,b);
        }
        for(int i=max(100ll,l);i<=999;i++){
            long double a0=i%10-y,a1=i/10%10,a2=i/100;
            // 枚举转换后的结果,则 a2*b^2+a1*b+a0=y
            long double b0=(-a1+sqrt(a1*a1-4*one*a0*a2))/(2*one*a2),
                        b1=(-a1-sqrt(a1*a1-4*one*a0*a2))/(2*one*a2);
            for(long long b=b0-10;b<=b0+10;b++)
                if(check(b,y,l))answer=max(answer,b);
            for(long long b=b1-10;b<=b1+10;b++)
                if(check(b,y,l))answer=max(answer,b);
        }
        for(int b=11;b<=1000000;b++)
            if(check(b,y,l))answer=max(answer,(long long)b);
        printf("%lld\n",answer);
    }
    return 0;
}