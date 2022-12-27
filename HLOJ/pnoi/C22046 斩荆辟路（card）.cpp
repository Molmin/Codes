// 2022.10.26

#include<bits/stdc++.h>
using namespace std;

const long long mod=998244353;

struct Matrix{
    int n,m;
    vector<vector<long long> > data;
    long long val(int i,int j){
        return data[i][j];
    }
    long long set(int i,int j,long long val){
        return data[i][j]=val;
    }
    void init(int a,int b){
        n=a,m=b;
        data.clear();
        vector<long long> tmp;
        for(int i=0;i<b;i++)
            tmp.push_back(0);
        for(int i=0;i<a;i++)
            data.push_back(tmp);
    }
    void print(){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++)
                printf("%lld ",val(i,j));
            printf("\n");
        }
    }
    Matrix operator*(Matrix S)const{
        if(m!=S.n)return{0,0,{}};
        Matrix res;
        res.n=n,res.m=S.m;
        for(int i=0;i<res.n;i++){
            vector<long long> tmp;
            for(int j=0;j<res.m;j++){
                long long sum=0;
                for(int k=0;k<m;k++)
                    sum+=data[i][k]*S.val(k,j)%mod;
                tmp.push_back(sum%mod);
            }
            res.data.push_back(tmp);
        }
        return res;
    }
}A,B,C;
Matrix power(Matrix X,int n){
    Matrix res={-1,-1,{}};
    while(n){
        if(n&1){
            if(res.n==-1)res=X;
            else res=res*X;
        }
        X=X*X,n>>=1;
    }
    return res;
};
long long power(long long a,long long n=mod-2){
    long long res=1;
    while(n){
        if(n&1)res=res*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return res;
}

int n,k;
long long p[101];

int main(){
    freopen("card.in","r",stdin);
    freopen("card.out","w",stdout);
    scanf("%d%d",&n,&k),p[k]=1;
    for(int i=0;i<k;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        p[i]=a*power(b)%mod;
    }
    Matrix M0; M0.init(1,k+2);
    M0.set(0,0,1);
    Matrix M; M.init(k+2,k+2);
    for(int i=0;i<=k;i++)
        M.set(i,0,p[i]),M.set(i,i+1,(1-p[i]+mod)%mod),M.set(i,k+1,p[i]);
    M.set(k+1,k+1,1);
    Matrix ans;
    ans=M0*power(M,n);
    printf("%lld\n",ans.val(0,k+1));
    return 0;
}