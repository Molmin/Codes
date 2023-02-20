// 2022.07.31

#include<bits/stdc++.h>
using namespace std;

inline long double cal(int x,int y,int x_,int y_){
    return(x_-x)*(long double)y/(y-y_)+x;
    return((long double)y_*x-(long double)y*x_)/(y_-y);
}

int n;

struct Mine{
    int l,r,y;
}a[2001];
struct Interval{
    long double l,r;
    int value;
    bool operator<(Interval tmp)const{
        return l<tmp.l;
    }
}b[2001];
struct Node{
    long double x;
    int value;
    bool operator<(Node tmp)const{
        return x>tmp.x;
    }
};

int cnt;

inline long long work(int x,int y){
    cnt=0;
    for(int i=1;i<=n;i++){
        if(a[i].y==y)continue;
        long double L=cal(x,y,a[i].l,a[i].y),
                    R=cal(x,y,a[i].r,a[i].y);
        if(L>R)swap(L,R);
        b[++cnt]={L,R,a[i].r-a[i].l};
    }
    sort(b+1,b+1+cnt);

    long long sum=0,maxn=0;
    priority_queue<Node> Q;
    for(int i=1;i<=cnt;i++){
        Q.push({b[i].r,b[i].value});
        sum+=b[i].value;
        while(!Q.empty()&&Q.top().x<b[i].l)
            sum-=Q.top().value,Q.pop();
        maxn=max(sum,maxn);
    }
    return maxn;
}

int main(){
    while(~scanf("%d",&n)){
        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].y);
            if(a[i].l>a[i].r)swap(a[i].l,a[i].r);
        }
        long long ans=0;
        for(int i=1;i<=n;i++){
            ans=max(ans,work(a[i].l,a[i].y)+abs(a[i].l-a[i].r));
            ans=max(ans,work(a[i].r,a[i].y)+abs(a[i].l-a[i].r));
        }
        printf("%lld\n",ans);
    }
    return 0;
}