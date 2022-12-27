// 2022.10.27

#include<bits/stdc++.h>
using namespace std;

void print(int n){
    for(int i=0;i<n;i++)
        printf("2");
}

int main(){
    freopen("run.in","r",stdin);
    freopen("run.out","w",stdout);
    long long c,s;
    scanf("%lld%lld",&c,&s);
    if(c&1||int(c/4.0)*1ll*(int)ceil(c/4.0)<s||c/2-1>s)
        return printf("Impossible\n"),0;
    if(c==4){
        if(s==1)return printf("2333"),0;
        else return printf("Impossible\n"),0;
    }
    for(int i=1;c/2-i>=i;i++){
        int a=i,b=c/2-i;
        if((long long)a*b<s)continue;
        long long cutarea=(long long)a*b-s;
        int cutline=cutarea/(b-1);
        int cutnum=cutarea%(b-1);
        if(cutnum==0){
            if(cutline==0){
                print(a);
                printf("3");
                print(b-1);
                printf("3");
                print(a-1);
                printf("3");
                print(b-1);
            }
            else{
                print(a);
                printf("3");
                print(b-1);
                printf("3");
                print(a-cutline-1);
                printf("3");
                print(b-2);
                printf("1");
                print(cutline-1);
                printf("3");
            }
        }
        else{
            if(cutline==0){
                print(a);
                printf("3");
                print(b-1);
                printf("3");
                print(a-2);
                printf("3");
                print(cutnum-1);
                printf("13");
                print(b-cutnum-1);
            }
            else{
                print(a);
                printf("3");
                print(b-1);
                printf("3");
                print(a-cutline-2);
                printf("3");
                print(cutnum-1);
                printf("13");
                print(b-cutnum-2);
                printf("1");
                print(cutline-1);
                printf("3");
            }
        }
        return 0;
    }
    printf("Impossible\n");
    return 0;
}