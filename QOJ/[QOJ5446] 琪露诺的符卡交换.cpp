// 2023.02.26

#include <bits/stdc++.h>
using namespace std;

int n,b[201][201];
vector<int> cardId[201][201];
int cardNum[201][201],matched[201];
bool vis[201];

bool newMatch(int x){
    if(vis[x])return false; vis[x]=true;
    for(int i=1;i<=n;i++)
        if(cardNum[x][i]&&(!matched[i]||newMatch(matched[i]))){
            cardNum[matched[i]][i]++,
            matched[i]=x,
            cardNum[matched[i]][i]--;
            return true;
        }
    return false;
}

int main(){
    int T; scanf("%d",&T);
    while(T--){
        memset(cardNum,0,sizeof cardNum);
        memset(matched,0,sizeof matched);
        memset(b,0,sizeof b);
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                cardId[i][j].clear();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                int card; scanf("%d",&card);
                cardNum[i][card]++;
                cardId[i][card].push_back(j);
            }
        for(int k=1;k<=n;k++){
            for(int i=1;i<=n;i++){
                memset(vis,false,sizeof vis);
                newMatch(i);
            }
            for(int i=1;i<=n;i++)
                b[matched[i]][k]=i;
            memset(matched,0,sizeof matched);
        }
        printf("%d\n",n*(n-1)/2);
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++){
                int x=b[i][j],y=b[j][i];
                printf("%d %d %d %d\n",i,cardId[i][x].back(),j,cardId[j][y].back());
                cardId[i][x].pop_back(); cardId[j][y].pop_back();
            }
    }
    return 0;
}
