// 2022.11.11

#include<bits/stdc++.h>
using namespace std;
const int inf=1000000001;

int n,m,q;
int a[100001],b[100001];

struct Node{
    bool zero,sm,la; // 是否有等于 / 小于 / 大于 0 的数
    int smmaxn,smminn,lamaxn,laminn;
};

inline Node merge(Node x,Node y){
    Node res;
    res={x.zero||y.zero,0,0,-inf,0,0,inf};
    if(x.sm){
        res.sm=true;
        res.smmaxn=max(res.smmaxn,x.smmaxn);
        res.smminn=min(res.smminn,x.smminn);
    }
    if(y.sm){
        res.sm=true;
        res.smmaxn=max(res.smmaxn,y.smmaxn);
        res.smminn=min(res.smminn,y.smminn);
    }
    if(x.la){
        res.la=true;
        res.lamaxn=max(res.lamaxn,x.lamaxn);
        res.laminn=min(res.laminn,x.laminn);
    }
    if(y.la){
        res.la=true;
        res.lamaxn=max(res.lamaxn,y.lamaxn);
        res.laminn=min(res.laminn,y.laminn);
    }
    return res;
}

struct Tree{
    Node t[400001];
    Node get(int id,int l,int r,int L,int R){
        if(L<=l&&R>=r)return t[id];
        if(L>r||R<l)return {0,0,0,0,0,0,0};
        int mid=l+r>>1;
        Node x=get(id<<1,l,mid,L,R),y=get((id<<1)+1,mid+1,r,L,R);
        return merge(x,y);
    }
    void init(int id,int l,int r,int *p){
        if(l==r){
            if(p[l]>0)t[id]={0,0,1,0,0,p[l],p[l]};
            if(p[l]<0)t[id]={0,1,0,p[l],p[l],0,0};
            if(p[l]==0)t[id]={1,0,0,0,0,0,0};
        }
        else{
            int mid=l+r>>1,L=id<<1,R=L+1;
            init(L,l,mid,p);
            init(R,mid+1,r,p);
            t[id]=merge(t[L],t[R]);
        }
    }
}A,B;

int main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    for(int i=1;i<=m;i++)
        scanf("%d",b+i);
    A.init(1,1,n,a);
    B.init(1,1,m,b);
    while(q--){
        int l1,r1,l2,r2;
        scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
        Node t1=A.get(1,1,n,l1,r1),
             t2=B.get(1,1,m,l2,r2);
        long long answer=-1ll*inf*inf;
        if(t1.zero){
            answer=max(answer,0ll);
        }
        if(t1.sm){
            int bmax=-inf;
            if(t2.zero)bmax=max(bmax,0);
            if(t2.sm)bmax=max(bmax,t2.smmaxn);
            if(t2.la)bmax=max(bmax,t2.lamaxn);
            if(bmax>0)answer=max(answer,(long long)bmax*t1.smmaxn);
            if(bmax<0)answer=max(answer,(long long)bmax*t1.smminn);
            if(bmax==0)answer=max(answer,0ll);
        }
        if(t1.la){
            int bmin=inf;
            if(t2.zero)bmin=min(bmin,0);
            if(t2.sm)bmin=min(bmin,t2.smminn);
            if(t2.la)bmin=min(bmin,t2.laminn);
            if(bmin>0)answer=max(answer,(long long)bmin*t1.lamaxn);
            if(bmin<0)answer=max(answer,(long long)bmin*t1.laminn);
            if(bmin==0)answer=max(answer,0ll);
        }
        printf("%lld\n",answer);
    }
    return 0;
}