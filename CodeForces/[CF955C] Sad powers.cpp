// 2023.03.05

#include<bits/stdc++.h>
using namespace std;

long long power(long long a,long long n){
    long long res=1;
    while(n){
        if(n&1)res=res*a;
        a=a*a;
        n>>=1;
    }
    return res;
}

namespace solve{

    vector<long long> valid;

    void init(){
        valid.clear();
        for(int p=3;p<=60;p+=2)
            for(int a=1,MAX=pow(1e18,1.0/p);a<=MAX;a++){
                long long x=power(a,p),SQRT=sqrt(x);
                if(SQRT*SQRT==x)continue;
                else valid.push_back(x);
            }
        sort(valid.begin(),valid.end());
        auto temp=unique(valid.begin(),valid.end());
        valid.erase(temp,valid.end());
    }
    long long main(long long r){
        long long res=lower_bound(valid.begin(),valid.end(),r)-valid.begin();
        if(res==valid.size())res--;
        if(res<valid.size()&&valid[res]>r)res--;
        return res+(long long)sqrt(r);
    }
}

int main(){
    solve::init();
    int q;
    scanf("%d",&q);
    while(q--){
        long long l,r;
        scanf("%lld%lld",&l,&r);
        printf("%lld\n",solve::main(r)-solve::main(l-1));
    }
    return 0;
}