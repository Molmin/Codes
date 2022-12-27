// 2022.10.21

#include<bits/stdc++.h>
using namespace std;

struct Edge{
    int to,nxt,w;
}edge[200001];
int head[100001],cntEdge;
inline void addEdge(int u,int v,int w){
    edge[++cntEdge]={v,head[u],w};
    head[u]=cntEdge;
}

int n,m;
double up[100001],down[100001];
// up/down[i]: 从 i 点出发，第一步向上/下走的期望步数
int fa[100001],son[100001];
// fa/son[i]: i 点的父亲/儿子结点个数

bool oncir[100001];
// oncir[i]: 是否在环上

void dpdown(int id,int father){
    // 求 fa/son/down[id]
    down[id]=0;
    for(int i=head[id];i;i=edge[i].nxt)
        if(edge[i].to!=father&&!oncir[edge[i].to]){
            son[id]++;
            fa[edge[i].to]++;
            dpdown(edge[i].to,id);
            down[id]+=down[edge[i].to]+edge[i].w;
        }
    if(son[id])down[id]/=son[id];
}
void dpup(int id,int father,int w){
    if(fa[father]+son[father]>1)
        up[id]=(up[father]*fa[father]+down[father]*son[father]-
            (down[id]+w))/(fa[father]+son[father]-1)+w;
    else up[id]=w;
    for(int i=head[id];i;i=edge[i].nxt)
        if(edge[i].to!=father)
            dpup(edge[i].to,id,edge[i].w);
}

namespace solve1{
    void main(){
        // 输入的是一棵普通树
        dpdown(1,0);
        for(int i=head[1];i;i=edge[i].nxt)
            dpup(edge[i].to,1,edge[i].w);
    }
}

namespace solve2{
    int tag; // 环起始位置
    bool cirend;
    void findcircle(int id,int father){
        // 找出基环树中的还并标记 oncir 以及一个起点标记 tag
        oncir[id]=true;
        for(int i=head[id];i;i=edge[i].nxt)
            if(edge[i].to!=father){
                if(oncir[edge[i].to]){
                    tag=edge[i].to; return;
                }
                findcircle(edge[i].to,id);
                if(cirend)break;
                if(tag){
                    if(tag==id)cirend=true;
                    return;
                }
            }
        oncir[id]=false;
    }
    int idoncir[21],cirid[100001],len;
    // idoncir[i]: 环上从 tag 开始顺时针第 i 个点的编号
    // cirid[i]: 编号为 i 的点在环上从 tag 开始顺时针数的编号
    // len: 环的长度
    int ldis[21],rdis[21];
    // ldis/rdis[i]: 环上从 tag 开始顺时针第 i 个点的上一条/下一条环上边的长度
    void initcircle(int id,int father){
        idoncir[++len]=id,cirid[id]=len,fa[id]=2;
        for(int i=head[id];i;i=edge[i].nxt)
            if(edge[i].to!=father&&oncir[edge[i].to]){
                if(!cirid[edge[i].to])
                    initcircle(edge[i].to,id);
                ldis[cirid[edge[i].to]]=rdis[cirid[id]]=edge[i].w;
                return;
            }
    }

    namespace cir{
        inline int pre(int id){
            if(id==1)return len;
            return id-1;
        }
        inline int nxt(int id){
            if(id==len)return 1;
            return id+1;
        }
    }

    void main(){
        findcircle(1,0);
        initcircle(tag,0);
        for(int i=1;i<=len;i++)
            dpdown(idoncir[i],0);
        for(int i=1;i<=len;i++){
            int id=idoncir[i];
            double mul=0.5; // 向顺时针下一个点走的概率占在环上走的一半
            for(int j=cir::nxt(i);j!=i;j=cir::nxt(j)){
                int v=idoncir[j];
                if(j+1==i||(j==len&&i==1)) // 顺时针下一个结点就是起点 i，特殊处理
                    up[id]+=(ldis[j]+down[v])*mul;
                else up[id]+=(down[v]*son[v]/(son[v]+1)+ldis[j])*mul;
                mul*=1.0/(son[v]+1);
            }
            mul=0.5; // 向逆时针下一个点走的概率占在环上走的一半
            for(int j=cir::pre(i);j!=i;j=cir::pre(j)){
                int v=idoncir[j];
                if(j-1==i||(j==1&&i==len)) // 逆时针下一个结点就是起点 i，特殊处理
                    up[id]+=(rdis[j]+down[v])*mul;
                else up[id]+=(down[v]*son[v]/(son[v]+1)+rdis[j])*mul;
                mul*=1.0/(son[v]+1);
            }
            for(int j=head[id];j;j=edge[j].nxt)
                if(!oncir[edge[j].to])
                    dpup(edge[j].to,id,edge[j].w);
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    if(m<n)solve1::main();
    else solve2::main();
    double answer=0;
    for(int i=1;i<=n;i++)
        answer+=(up[i]*fa[i]+down[i]*son[i])/(fa[i]+son[i]);
    printf("%.5lf\n",answer/n);
    return 0;
}