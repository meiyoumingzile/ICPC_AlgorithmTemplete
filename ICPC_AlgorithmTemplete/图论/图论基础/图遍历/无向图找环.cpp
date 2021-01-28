#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;

struct Edge{
    int e,k;
    Edge(){
    }
    Edge(const int &e,const int &k){
        this->e=e;
        this->k=k;
    }
};
struct Graphic{
    int V,E,S,T,size=0;
    int head[MAX];
    Edge edge[MAX*5];
    void push(const int &b,const int &e){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,t);
    }
	void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
};
Graphic g;
int dfn[MAX];
int len;
void dfs(int now)[
    dfn=
    for(i=g.head[now];i!=-1;i=g.edge[i].k){
        int e=g.edge[i].e;
        if(dfn[e]==0){
            dfs(e);
        }
    }
]

int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m,u,v;
    g.clear();
    cin>>n>>m;
    for(i=0;i<m;i++){
        scanf("%d%d",&u,&v);
        g.push(u,v);
        g.push(v,u);
    }
    len=1;


return 0;
}

