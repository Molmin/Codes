// 2022.09.26

#include<bits/stdc++.h>
using namespace std;

int n;

long long cal(vector<int> x){
    sort(x.begin(),x.end());
    long long pre=0,sum=0;
    for(int i=0;i<n;i++){
        sum+=(long long)i*x[i]-pre;
        pre+=x[i];
    }
    return sum;
}

long long Cal(vector<int> x,vector<int> y){
    return cal(x)+cal(y);
}

signed main(){
    freopen("dist.in","r",stdin);
    freopen("dist.out","w",stdout);
    vector<int> x,y,_x,_y;
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        int a; scanf("%lld",&a);
        x.push_back(a);
    }
    for(int i=1;i<=n;i++){
        int a; scanf("%lld",&a);
        y.push_back(a);
    }
    long long tmp=Cal(x,y);
    for(int i=0;i<n;i++)
        _x.push_back(x[i]-y[i]),
        _y.push_back(x[i]+y[i]);
    printf("%lld\n",tmp*2-Cal(_x,_y));
    return 0;
}