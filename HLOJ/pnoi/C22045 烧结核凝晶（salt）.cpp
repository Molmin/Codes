// 2022.10.26

#include<bits/stdc++.h>
using namespace std;

int n,k;

struct Pair{
    int a,b;
    double t;
    bool operator<(Pair tmp)const{
        return t>tmp.t;
    }
}a[100001];

inline bool check(double ans){
    for(int i=1;i<=n;i++)
        a[i].t=a[i].a-a[i].b*ans;
    sort(a+1,a+1+n);
    double sum=0;
    for(int i=1;i<=k;i++)
        sum+=a[i].t;
    return sum>=0;
}

int main(){
    freopen("salt.in","r",stdin);
    freopen("salt.out","w",stdout);
    scanf("%d%d",&n,&k);
    double maxn=0;
    for(int i=1;i<=n;i++)
        scanf("%d%d",&a[i].a,&a[i].b);
    double l=0,r=1;
    while(r-l>1e-15){
        double mid=(l+r)/2;
        if(check(mid))l=mid;
        else r=mid;
    }
    printf("%.15lf\n",(l+r)/2);
    return 0;
}