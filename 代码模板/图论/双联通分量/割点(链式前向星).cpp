#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=20010;
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
    int V,E,S,T,size=0;
    int head[MAX];
    Edge edge[200010];
    void push(const int &b,const int &e,const int &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
    }
	void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
};
Graphic g;
int dfn[MAX],low[MAX];//dfn代表访问顺序编号，low代表儿子节点编号最小的
bool vis[MAX],isCut[MAX];//isCut代表是不是割点
int root,rootSonCnt,cutPointCnt;//root代表根节点，rootSonCnt代表根节点子树数量，cutPointCnt代表已经找到的割点数量
void tarjan(int now,int p,int &len){//递归代码，now从任意[1,V]开始都可以，但要注意可能不会被都走到，p代表搜索树的父节点初始化是-1，len代表深度
    dfn[now]=low[now]=len++;
    vis[now]=1;
    isCut[now]=0;
    for(int i=g.head[now];i!=-1;i=g.edge[i].k){
        int e=g.edge[i].e;
        if(vis[e]==0){//把dfn当做dfs的vis数组判断走没走过
            tarjan(e,now,len);
            low[now]=min(low[now],low[e]);
            if(now==root){//是根,把根节点，能到达的数目加一
                rootSonCnt++;//根节点的子树数量增加
            }else if(dfn[now]<=low[e]&&isCut[now]==0){//避免重复计算用v标记
                cutPointCnt++;
                isCut[now]=1;//找到一个割点
            }
        }else if(dfn[e] < dfn[now]&&e!=p){//树是有向的，但原图是无向图，要检测是不是父节点,不能更新父节点
             //如果e访问过了，那么也至少更新当节点now的low是自己和dfn[e]最小c
            // 且对于无向图应该只对dfn小于now的e操作，因为较大的没有意义
            low[now]=min(low[now],dfn[e]);
        }
    }
}
int getCutPoint(){//图可能是不连通的，应该多次判断知道所有点都被走过tarjan为止。这样才能找到每一块的割点，具体看题了
    int len,i;
    memset(vis,0,sizeof(vis));
    memset(isCut,0,sizeof(isCut));
    cutPointCnt=0;//割点初始化
    for(i=1;i<=g.V;i++){
        if(vis[i]==0){
            root=i;//初始化根节点是哪个
            len=1;//初始化访问顺序
            rootSonCnt=0;//初始化根节点的子树数量
            tarjan(root,-1,len);
            if(rootSonCnt>1){//看根节点是不是割点
                isCut[root]=1;
                cutPointCnt++;
            }
        }
    }
    return cutPointCnt;
}
int main(int argc,char *argv[]){
    int i,b,e;
    while(~scanf("%d%d",&g.V,&g.E)){
        g.clear();
        for(i=0;i<g.E;i++){
            scanf("%d%d",&b,&e);
            g.push(b,e,0);
            g.push(e,b,0);
        }
        printf("%d\n",getCutPoint());//数量
        for(i=1;i<=g.V;i++){
            if(isCut[i]){
                printf("%d ",i);
            }
        }
    }
return 0;
}
/*
8 8
1 2
2 3
3 4
4 5
3 5
2 4
6 7
7 8
*/
