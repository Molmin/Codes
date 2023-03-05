// 2023.02.04

#include <bits/stdc++.h>
using namespace std;

const int L=1000000000;
int k;

struct Point{
    int x,y;
};
const Point LU={0,0},RU={0,L},LD={L,0},RD={L,L};
Point getMiddle(Point A,Point B){
    return {(A.x+B.x)/2,(A.y+B.y)/2};
}
struct Triangle{
    Point A,B,C;
}ans[51];
int total;

int main(){
    srand(time(0));
    scanf("%d",&k);
    if(k<8)return printf("No\n"),0;
    printf("Yes\n");
    switch(k%3){
        case 0: {
            Point A={int(L*0.35),int(L*0.8)},
                  B={int(L*0.28),int(L*0.64)},
                  C={0,int(L*0.7)},D={int(L*0.3),L},
                  O={int(L*0.175),int(L*0.84)};
            ans[++total]={LU,LD,A};
            ans[++total]={LD,RD,A};
            ans[++total]={LU,B,C};
            ans[++total]={RD,A,D};
            ans[++total]={A,B,O};
            ans[++total]={B,C,O};
            ans[++total]={C,RU,O};
            ans[++total]={RU,D,O};
            ans[++total]={D,A,O};
            break;
        }
        case 1: {
            Point A={int(L*0.7),int(L*0.5)},
                  B={int(L*0.76),int(L*0.4)},
                  C={int(L*0.76),int(L*0.6)},
                  O={int(L*0.78),int(L*0.5)},
                  D={L,int(L*0.45)},E={L,int(L*0.55)};
            ans[++total]={LU,RU,A};
            ans[++total]={LU,LD,A};
            ans[++total]={RU,RD,A};
            ans[++total]={LD,B,D};
            ans[++total]={RD,C,E};
            ans[++total]={A,B,O};
            ans[++total]={B,D,O};
            ans[++total]={D,E,O};
            ans[++total]={E,C,O};
            ans[++total]={C,A,O};
            break;
        }
        case 2: {
            Point A={0,L/2},B={L,L/2},
                  C={int(L*0.85),int(L*0.48)},
                  D={int(L*0.85),int(L*0.52)};
            ans[++total]={LU,LD,C};
            ans[++total]={RU,RD,D};
            ans[++total]={LD,B,C};
            ans[++total]={RD,B,D};
            ans[++total]={B,C,D};
            ans[++total]={LU,A,C};
            ans[++total]={RU,A,D};
            ans[++total]={A,C,D};
            break;
        }
    }
    while(total<k){
        int id=rand()%total+1;
        Point A=ans[id].A,B=ans[id].B,C=ans[id].C,
              X=getMiddle(A,B),
              Y=getMiddle(B,C),
              Z=getMiddle(C,A);
        ans[id]     ={A,Z,X};
        ans[++total]={B,X,Y};
        ans[++total]={C,Y,Z};
        ans[++total]={X,Y,Z};
    }
    for(int i=1;i<=total;i++)
        printf("%d %d %d %d %d %d\n",
            ans[i].A.x,ans[i].A.y,ans[i].B.x,
            ans[i].B.y,ans[i].C.x,ans[i].C.y);
    return 0;
}
