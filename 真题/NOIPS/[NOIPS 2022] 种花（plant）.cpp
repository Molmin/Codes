// 2022.11.26

#include <bits/stdc++.h>
using namespace std;
const long long mod=998244353;

int n,m,c,f;
bool a[1001][1001];

namespace calcC{
    int getright[1001][1001]; // 向右最多几格（不含自己）
    int getdown[1001][1001]; // 向下到 a[i][j]==false，getright 值之和（不含自己）
    void solve(){
        // calculate getright
        for(int i=1;i<=n;i++){
            getright[i][m]=0;
            for(int j=m-1;j>=1;j--){
                if(a[i][j]||a[i][j+1])getright[i][j]=0;
                else getright[i][j]=getright[i][j+1]+1;
            }
        }
        // calculate getdown
        for(int i=n;i>=1;i--){
            for(int j=1;j<=m;j++){
                if(i==n)getdown[i][j]=0;
                else if(a[i][j]||a[i+1][j])getdown[i][j]=0;
                else getdown[i][j]=getdown[i+1][j]+getright[i+1][j];
            }
        }
        // calculate answer
        long long answer=0;
        for(int i=1;i<=n-2;i++)
            for(int j=1;j<m;j++){
                if(a[i][j]||a[i+1][j]||a[i+2][j]||a[i][j+1])continue;
                answer+=1ll*getright[i][j]*getdown[i+1][j]%mod;
                answer%=mod;
            }
        printf("%lld ",answer*c);
    }
}

namespace calcF{
    int getdown[1001][1001]; // 向下最多几格（不含自己）
    int getright[1001][1001]; // 向右最多几格（不含自己）
    int getup[1001][1001]; // 向上到 a[i][j]==false，getright 值之和（不含自己）
    void solve(){
        // calculate getdown
        for(int j=1;j<=m;j++){
            getdown[n][j]=0;
            for(int i=n-1;i>=1;i--){
                if(a[i][j]||a[i+1][j])getdown[i][j]=0;
                else getdown[i][j]=getdown[i+1][j]+1;
            }
        }
        // calculate getright
        for(int i=1;i<=n;i++){
            getright[i][m]=0;
            for(int j=m-1;j>=1;j--){
                if(a[i][j]||a[i][j+1])getright[i][j]=0;
                else getright[i][j]=getright[i][j+1]+1;
            }
        }
        // calculate getup
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(i==1)getup[i][j]=0;
                else if(a[i][j]||a[i-1][j])getup[i][j]=0;
                else getup[i][j]=getup[i-1][j]+getright[i-1][j];
            }
        }
        // calculate answer
        long long answer=0;
        for(int i=2;i<n;i++)
            for(int j=1;j<m;j++){
                if(a[i][j]||a[i+1][j]||a[i-1][j]||a[i][j+1]||a[i-2][j])continue;
                answer+=1ll*getright[i][j]*getdown[i][j]%mod*getup[i-1][j]%mod;
                answer%=mod;
            }
        printf("%lld\n",answer*f);
    }
}

int main(){
    int T,id;
    scanf("%d%d",&T,&id);
    while(T--){
        scanf("%d%d%d%d",&n,&m,&c,&f);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                char ch;
                scanf(" %ch",&ch);
                a[i][j]=ch=='1';
            }
        calcC::solve();
        calcF::solve();
    }
    return 0;
}
