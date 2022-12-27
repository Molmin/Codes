// 2022.09.30

#include<bits/stdc++.h>
using namespace std;

namespace solve{
    int n,m;
    bool a[1001][1001];

    int nulltot[1002][1002];
    long long xysum[1002][1002];

    int xid[1001],yid[1001];

    void main(){
        scanf("%d%d",&n,&m);
        memset(xid,0,sizeof xid);
        memset(yid,0,sizeof yid);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                char ch;
                scanf(" %c",&ch);
                a[i][j]=ch=='G';
                if(a[i][j])xid[j]=i,yid[i]=j;
            }

        long long answer=0;
        memset(nulltot,0,sizeof nulltot);
        memset(xysum,0,sizeof xysum);
        for(int i=1;i<=n;i++)
            for(int j=m;j>=1;j--){
                nulltot[i][j]=nulltot[i][j+1]+nulltot[i-1][j]-nulltot[i-1][j+1]+1-a[i][j];
                xysum[i][j]=xysum[i][j+1]+xysum[i-1][j]-xysum[i-1][j+1];
                if(!a[i][j])xysum[i][j]+=i-j,
                    answer+=(i-j)*(long long)nulltot[i-1][j+1]-xysum[i-1][j+1];
            }

        memset(nulltot,0,sizeof nulltot);
        memset(xysum,0,sizeof xysum);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                nulltot[i][j]=nulltot[i][j-1]+nulltot[i-1][j]-nulltot[i-1][j-1]+1-a[i][j];
                xysum[i][j]=xysum[i][j-1]+xysum[i-1][j]-xysum[i-1][j-1];
                if(!a[i][j])xysum[i][j]+=i+j,
                    answer+=(i+j)*(long long)nulltot[i][j]-xysum[i][j];
            }

        for(int i=1;i<=n;i++){
            if(yid[i]==0)continue;
            int firid=yid[i],pre=yid[i];
            for(int j=i;j<=n;j++){
                if(yid[j]==0)break;
                if(pre-firid>0&&yid[j]-pre<0)break;
                if(pre-firid<0&&yid[j]-pre>0)break;
                pre=yid[j];
                if(pre-firid<=0)answer+=2ll*(m-firid)*(yid[j]-1);
                else answer+=2ll*(m-yid[j])*(firid-1);
            }
        }

        for(int i=1;i<=m;i++){
            if(xid[i]==0)continue;
            int firid=xid[i],pre=xid[i];
            for(int j=i;j<=m;j++){
                if(xid[j]==0)break;
                if(pre-firid>0&&xid[j]-pre<0)break;
                if(pre-firid<0&&xid[j]-pre>0)break;
                pre=xid[j];
                if(pre-firid<=0)answer+=2ll*(n-firid)*(xid[j]-1);
                else answer+=2ll*(n-xid[j])*(firid-1);
            }
        }

        printf("%.4lf\n",answer*2.0/nulltot[n][m]/nulltot[n][m]);
    }
}

int main(){
    freopen("chess.in","r",stdin);
    freopen("chess.out","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--)
        solve::main();
    return 0;
}