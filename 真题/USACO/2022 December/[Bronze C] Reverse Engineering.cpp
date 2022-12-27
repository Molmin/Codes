// 2022.12.24

#include<bits/stdc++.h>
using namespace std;

int n,m;
bool a[101][1001],res[101],deled[101],checked[101];

int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                char ch; scanf(" %c",&ch);
                a[i][j]=ch=='1';
            }
            cin>>res[i];
        }
        memset(deled,0,sizeof deled);
        memset(checked,0,sizeof checked);
        bool solved=false;
        int deltotal=0;
        for(int i=1;i<=n;i++){
            int K=0,delres=0,delval=0;
            for(int k=1;k<=n;k++){
                if(checked[k])continue;
                bool all0is0=true,all0is1=true,all1is0=true,all1is1=true;
                for(int j=1;j<=m;j++){
                    if(deled[j])continue;
                    all0is0&=a[j][k]!=0||res[j]==0;
                    all0is1&=a[j][k]!=0||res[j]==1;
                    all1is0&=a[j][k]!=1||res[j]==0;
                    all1is1&=a[j][k]!=1||res[j]==1;
                }
                if(all0is0&&!K)K=k,delval=0,delres=0;
                if(all0is1&&!K)K=k,delval=0,delres=1;
                if(all1is0&&!K)K=k,delval=1,delres=0;
                if(all1is1&&!K)K=k,delval=1,delres=1;
            }
            if(!K)break;
            checked[K]=true;
            for(int j=1;j<=m;j++)
                if(!deled[j]&&a[j][K]==delval&&res[j]==delres)deled[j]=true,deltotal++;
            if(deltotal==m){
                solved=true;
                break;
            }
            if(i==n){
                set<int>results;
                for(int j=1;j<=m;j++)
                    if(!deled[j])results.insert(res[j]);
                if(results.size()==1)solved=true;
            }
        }
        if(solved)printf("OK\n");
        else printf("LIE\n");
    }
    return 0;
}