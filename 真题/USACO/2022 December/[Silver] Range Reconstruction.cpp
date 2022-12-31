// 2022.12.26

#include<bits/stdc++.h>
using namespace std;

int n,r[301][301],a[301],pre;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            scanf("%d",r[i]+j);
    a[1]=0,pre=0;
    for(int i=2;i<=n;i++)
        if(r[i-1][i]==0)a[i]=a[i-1];
        else{
            if(!pre)a[i]=a[i-1]+r[i-1][i];
            else{
                a[i]=a[i-1]+r[i-1][i];
                int maxn=max(a[pre],max(a[i-1],a[i])),
                    minn=min(a[pre],min(a[i-1],a[i]));
                if(maxn-minn!=r[pre][i])
                    a[i]=a[i-1]-r[i-1][i];
            }
            pre=i-1;
        }
    for(int i=1;i<=n;i++)
        printf("%d ",a[i]);
    return 0;
}