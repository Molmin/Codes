// 2022.12.18

#include<bits/stdc++.h>
using namespace std;

int n,m,k,a[2000001],special;
int nowin[600]; // 第 i 类图案现在在第几个栈里
bool onfront[600]; // 是否在栈的顶端
queue<int> Q;
deque<int> S[301];

struct Op{
    int op,s1,s2;
};
vector<Op> ops;

void basicop(int x){
    if(nowin[x]){
        if(S[nowin[x]].empty())exit(0);
        if(*(S[nowin[x]].rbegin())==x){
            ops.push_back({1,nowin[x],0});
            S[nowin[x]].pop_back();
        }
        else{
            ops.push_back({1,special,0});
            ops.push_back({2,nowin[x],special});
            S[nowin[x]].pop_front();
        }
        Q.push(nowin[x]);
        nowin[x]=0;
    }
    else{
        nowin[x]=Q.front(),Q.pop();
        ops.push_back({1,nowin[x],0});
        S[nowin[x]].emplace_back(x);
    }
}

int LAST=0;
int main(){
    freopen("meow.in","r",stdin);
    freopen("meow.out","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=m;i++)
            scanf("%d",a+i);
        for(int i=1;i<=n;i++)
            S[i].clear();
        ops.clear();
        while(!Q.empty())Q.pop();
        for(int i=1;i<n;i++)
            Q.push(i),Q.push(i);
        special=n; // 特殊栈
        memset(nowin,0,sizeof nowin);
        for(int i=1;i<=m;i++){
            if(nowin[a[i]]||!Q.empty()){
                basicop(a[i]);
            }
            else{
                int j=i+1;
                while(j<=m&&a[j]!=a[i]&&*(S[nowin[a[j]]].rbegin())==a[j])j++;
                if(a[i]==a[j]){
                    ops.push_back({1,special,0});
                    for(int k=i+1;k<j;k++)
                        basicop(a[k]);
                    ops.push_back({1,special,0});
                }
                else{
                    int total=0,xid=nowin[a[j]],x=*(S[xid].rbegin());
                    for(int k=i+1;k<j;k++)
                        if(a[k]==x)total++;
                    if(total&1){
                        ops.push_back({1,special,0});
                        for(int k=i+1;k<j;k++)
                            if(x!=a[k])basicop(a[k]);
                            else ops.push_back({1,xid,0}),nowin[x]=xid-nowin[x];
                        ops.push_back({1,xid,0});
                        nowin[a[j]]=0,nowin[a[i]]=special;
                        S[special].emplace_back(a[i]);
                        Q.push(special),special=xid;
                        S[special].clear();
                    }
                    else{
                        ops.push_back({1,xid,0});
                        nowin[a[i]]=xid;
                        S[xid].emplace_back(a[i]);
                        for(int k=i+1;k<j;k++)
                            if(x!=a[k])basicop(a[k]);
                            else ops.push_back({1,xid,0});
                        ops.push_back({1,special,0});
                        ops.push_back({2,xid,special});
                        S[xid].pop_front();
                        nowin[a[j]]=0;
                    }
                }
                i=j;
            }
        }
        printf("%d\n",(int)ops.size());
        for(Op op:ops)
            if(op.op==1)printf("1 %d\n",op.s1);
            else printf("2 %d %d\n",op.s1,op.s2);
    }
    return 0;
}