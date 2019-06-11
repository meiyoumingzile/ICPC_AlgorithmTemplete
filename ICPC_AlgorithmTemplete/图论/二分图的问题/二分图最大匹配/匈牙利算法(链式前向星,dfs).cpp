#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1010;
const int mod=1e9+7;

struct Edge{
    int e,val,k;
    Edge(){}
    Edge(const int &e,const int &val,const int &k){
        this->e=e;
        this->val=val;
        this->k=k;
    }
};
struct Graphic{
    int V1,V2,E,size;
    int head[2][MAX];
    Edge edge[2000010];
    Graphic(){
        clear();
    }
    inline void push(const int &b,const int &e,const int &val,int fp=0){
        int t=head[fp][b];
        head[fp][b]=size;
        edge[size++]=Edge(e,val,t);
    }
    void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
};
Graphic g;
int vis[MAX],ytox[MAX];
inline bool Hungary_dfs(int now){//找到一个最大匹配
    for(rg int i=g.head[0][now];i!=-1;i=g.edge[i].k){
        const int &next=g.edge[i].e;
        if(!vis[next]){
            vis[next]++;
            if(ytox[next]==0||Hungary_dfs(ytox[next])){
                ytox[next]=now;
                return true;
            }
        }
    }
    return false;
}
int Hungary(){
    rg int i,cnt=0;
    memset(ytox,0,sizeof(ytox));
    for(i=1;i<=g.V1;i++){
       memset(vis,0,sizeof(vis));
       cnt+=Hungary_dfs(i);
    }
    return cnt;
}
int main(){
	rg int i,b,e,E,n,m,cnt=0;
	scanf("%d%d%d",&n,&m,&E);
    for(i=0;i<E;i++){
        scanf("%d%d",&b,&e);
        if(b<=m&&e<=m){
            g.push(b,e,0,0);
        }
	}
	g.V1=n;
	g.V2=m;
	printf("%d\n",Hungary());
return 0;
}
