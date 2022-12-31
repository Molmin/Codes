// 2022.12.26

#include<bits/stdc++.h>
using namespace std;

int n,minturn;
bool ans;

bool isp[5000001]; int maxp[5000001];
void init(int N){
    memset(isp,true,sizeof isp);
    for(int i=2;i<=N;i++)
        if(isp[i])
            for(int j=i<<1;j<=N;j+=i)isp[j]=false;
    for(int i=5;i<N;i+=2)
        for(int j=i-4;j>=1;j-=4)
            if(isp[j]){
                maxp[i]=j; break;
            }
}

int main(){
    init(5000000);
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        minturn=5000000;
        bool mustwin=false;
        for(int i=1;i<=n;i++){
            int a;
            scanf("%d",&a);
            if(isp[a])mustwin=true;
            else if(a&1){
                int b=(a-maxp[a])/2;
                if(b<minturn)minturn=b,ans=true;
            }
            else if(a/4<minturn)minturn=a/4,ans=a%4==2;
        }
        if(ans||mustwin)printf("Farmer John\n");
        else printf("Farmer Nhoj\n");
    }
    return 0;
}