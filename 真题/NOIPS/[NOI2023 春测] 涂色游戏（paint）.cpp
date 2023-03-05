// 2023.03.04（VP 考场代码）

#include<bits/stdc++.h>
using namespace std;

namespace solve{

	int n,m,q;

	// means that last operation's color or time in one line(i) or column(j)
	int iLastOpColor[100001],iLastOpTime[100001],
	    jLastOpColor[100001],jLastOpTime[100001];

	void init(){
		memset(iLastOpColor,0,sizeof iLastOpColor);
		memset(iLastOpTime,0,sizeof iLastOpTime);
		memset(jLastOpColor,0,sizeof jLastOpColor);
		memset(jLastOpTime,0,sizeof jLastOpTime);
	}

	void main(){
		scanf("%d%d%d",&n,&m,&q);
		for(int i=1;i<=q;i++){
			int op,x,c;
			scanf("%d%d%d",&op,&x,&c);
			switch(op){
				case 0:
					iLastOpColor[x]=c;
					iLastOpTime[x]=i;
					break;
				case 1:
					jLastOpColor[x]=c;
					jLastOpTime[x]=i;
					break;
			}
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(iLastOpTime[i]<jLastOpTime[j])
					printf("%d ",jLastOpColor[j]);
				else printf("%d ",iLastOpColor[i]);
				if(j==m)printf("\n");
			}
	}
}

int main(){
	freopen("paint.in","r",stdin);
	freopen("paint.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--){
		solve::init();
		solve::main();
	}
    return 0;
}
