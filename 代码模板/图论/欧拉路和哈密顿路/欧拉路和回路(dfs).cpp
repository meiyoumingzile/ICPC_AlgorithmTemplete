#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;

//寻找欧拉路
struct Edge{
    int e,val,k,i;//i储存边的编号，val储存边方向的正负(以输入为准)
    Edge(){}
    Edge(const int &e,const int &val,const int &k,const int &i){
        this->e=e;
        this->val=val;
        this->k=k;
        this->i=i;
    }
};
struct Graphic{
    int V,E,S,T,size=0;
    int head[MAX];
    Edge edge[MAX*10];
    void push(const int &b,const int &e,const int &val,const int &i=0){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t,i);
    }
    void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
};
Graphic g;
int du[MAX],dotList[MAX],euList[MAX],vis[MAX];//dotList是联通块点集，euLsit是欧拉路边集
int dotListLen,euListLen;
inline void dfs(int now){//寻找联通块
    vis[now]=1;
    dotList[dotListLen++]=now;
    for(int i=g.head[now];i!=-1;i=g.edge[i].k){
        if(vis[g.edge[i].e]==0){
            dfs(g.edge[i].e);
        }
    }
}
void findEuLoad(int now){//返回要输出的起点,i代表编号
    int val;
    for(int i=g.head[now];i!=-1;i=g.edge[i].k){
        if(g.edge[i].val<10){
            val=g.edge[i].val;
            g.edge[i].val+=20;
            g.edge[i^1].val+=20;
            findEuLoad(g.edge[i].e);
            euList[euListLen++]=g.edge[i].i*(-val);
        }
    }
}
int solve(){//非联通图返回-1,否则输出是不是欧拉路
    int i,cnt=0,d;
    memset(vis,0,sizeof(vis));
    dfs(1);
    if(dotListLen<g.V){//dfs出的点集点数少于总点数，孤立点存在也可判断，说明是非连通图
        printf("不连通\n");
        return -1;
    }
    for(i=1;i<=g.V;i++){
        if(du[i]&1){
            cnt++;
            d=i;
        }
    }
    if(cnt==0){
        printf("有欧拉回路\n");
        findEuLoad(1);
        for(i=0;i<euListLen;i++){
            printf("%d ",euList[i]);
        }printf("\n");
    }else if(cnt==2){
        printf("有欧拉路\n");
        findEuLoad(d);
        for(i=0;i<euListLen;i++){
            printf("%d ",euList[i]);
        }printf("\n");
    }else{
        printf("没有欧拉回路和欧拉路");
    }
    return 1;
}
int main(){
	int i,b,e,cnt,lastDot;
	while(~scanf("%d%d",&g.V,&g.E)){
        g.clear();
        memset(du,0,sizeof(du));
        for(i=1;i<=g.E;i++){
            scanf("%d%d",&b,&e);
            g.push(b,e,1,i);
            g.push(e,b,-1,i);
            du[b]++;
            du[e]++;
        }
        solve();//寻找欧拉路
	}
return 0;
}
