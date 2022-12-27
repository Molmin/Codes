// 2022.10.01

#include<bits/stdc++.h>
using namespace std;

int n,q,k,l[200001];

int block;

vector<int> id[200001];

int total[200001];
bool p[200001];

int inbigid[200001],bigcnt,inmainid[501];
int adjoin[501][501],changeinfluence[501];

int main(){
    freopen("light.in","r",stdin);
    freopen("light.out","w",stdout);
    scanf("%d%d%d",&n,&q,&k);
    block=sqrt(n);
    for(int i=1;i<=n;i++){
        scanf("%d",l+i);
        total[l[i]]++;
        id[l[i]].push_back(i);
    }
    for(int i=1;i<=k;i++)
        if(total[i]>block)
            inbigid[i]=++bigcnt,inmainid[bigcnt]=i;
    for(int i=1;i<n;i++)
        if(inbigid[l[i]]&&inbigid[l[i+1]])
            adjoin[inbigid[l[i]]][inbigid[l[i+1]]]++,
            adjoin[inbigid[l[i+1]]][inbigid[l[i]]]++;
    long long answer=0;
    while(q--){
        int x;
        scanf("%d",&x);
        p[x]=!p[x];
        if(p[x])answer+=total[x]<<1;
        else answer-=total[x]<<1;
        if(total[x]<=block){
            if(p[x])for(int i:(id[x])){
                if(l[i+1]==x)answer--;
                else answer-=p[l[i+1]]<<1;
                if(l[i-1]==x)answer--;
                else answer-=p[l[i-1]]<<1;
            }
            else for(int i:(id[x])){
                if(l[i+1]==x)answer++;
                else answer+=p[l[i+1]]<<1;
                if(l[i-1]==x)answer++;
                else answer+=p[l[i-1]]<<1;
            }
            if(p[x]){
                for(int i:(id[x])){
                    if(i<n&&inbigid[l[i+1]])
                        changeinfluence[inbigid[l[i+1]]]++;
                    if(i>1&&inbigid[l[i-1]])
                        changeinfluence[inbigid[l[i-1]]]++;
                }
            }
            else{
                for(int i:(id[x])){
                    if(i<n&&inbigid[l[i+1]])
                        changeinfluence[inbigid[l[i+1]]]--;
                    if(i>1&&inbigid[l[i-1]])
                        changeinfluence[inbigid[l[i-1]]]--;
                }
            }
        }
        else{
            if(p[x]){
                for(int i=1;i<=bigcnt;i++)
                    if(p[inmainid[i]]&&inmainid[i]!=x)
                        answer-=adjoin[inbigid[x]][i]<<1;
                answer-=adjoin[inbigid[x]][inbigid[x]];
                answer-=changeinfluence[inbigid[x]]<<1;
            }
            else{
                for(int i=1;i<=bigcnt;i++)
                    if(p[inmainid[i]]&&inmainid[i]!=x)
                        answer+=adjoin[inbigid[x]][i]<<1;
                answer+=adjoin[inbigid[x]][inbigid[x]];
                answer+=changeinfluence[inbigid[x]]<<1;
            }
        }
        printf("%lld\n",answer>>1);
    }
    return 0;
}