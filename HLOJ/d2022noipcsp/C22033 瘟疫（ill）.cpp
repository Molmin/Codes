// 2022.10.24

#include<bits/stdc++.h>
using namespace std;

int n,a[100001];

int main(){
    freopen("ill.in","r",stdin);
    freopen("ill.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    double answer=1;
    for(int i=2;i<=n;i++)
        answer+=a[i]*1.0/(a[1]+a[i]);
    printf("%.3lf\n",answer);
    return 0;
}