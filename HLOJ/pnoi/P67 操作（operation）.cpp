// 2022.09.29

#include<bits/stdc++.h>
using namespace std;

namespace solve{
    int n,k,a[200001],b[200001];
    int id[200001],t[200001];
    void main(){
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            scanf("%d",a+i),id[a[i]]=i;
        memset(t,-1,sizeof t);
        for(int i=1;i<=k;i++)
            scanf("%d",b+i),t[id[b[i]]]=i;
        long long answer=1;
        for(int i=1;i<=k;i++){
            bool flag1=id[b[i]]>1&&t[id[b[i]]]>t[id[b[i]]-1],
                 flag2=id[b[i]]<n&&t[id[b[i]]]>t[id[b[i]]+1];
            answer=answer*(flag1+flag2)%998244353;
        }
        printf("%lld\n",answer);
    }
}

int main(){
    freopen("operation.in","r",stdin);
    freopen("operation.out","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
        solve::main();
    return 0;
}