#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<map>
#include<set>
//#include<windows.h>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=2147483647;
const int MAX=1010;
const int mod=1e9+7;

struct Edge{//边，这里只存了终止点
    int e;
};

vector<Edge>adList[MAX];
int V,E;//V代表多少个点，E代表多少条边

int dfn[MAX],low[MAX];//dfn代表访问顺序编号，low代表儿子节点编号最小的
bool vis[MAX];
int root,cutPointCnt,rootSonCnt;

void tarjan(int now,int p,int &len){//递归代码，dot从任意[1,V]开始都可以，但要注意可能不会被都走到，len代表深度
    int i,j,k,next;
    dfn[now]=low[now]=len++;
    vis[now]=1;
    bool v=true;
    for(i=0;i<adList[now].size();i++){
        next=adList[now][i].e;
        if(vis[next]==0){//把dfn当做dfs的vis数组判断走没走过
            tarjan(next,now,len);
            low[now]=min(low[now],low[next]);
            if(now==root){//是根,把根节点，能到达的数目加一
                rootSonCnt++;//根节点的子树数量增加
            }else if(dfn[now]<=low[next]&&v){//避免重复计算用v标记
                cutPointCnt++;
                v=false;
            }
        }else if(dfn[next] < dfn[now]&&next!=p){//树是有向的，但原图是无向图，要检测是不是父节点,不能更新父节点
             //如果next访问过了，那么也至少更新当节点now的low是自己和dfn[next]最小c
            // 且在为了入栈不重复和多余，对于无向图应该只对dfn小于now的next操作，因为较大的没有意义
            low[now]=min(low[now],dfn[next]);
        }
    }
}

int getCutPoint(){
    int len,i,j;
    memset(vis,0,sizeof(vis));
    cutPointCnt=0;//割点初始化
    for(i=1;i<=V;i++){
        if(vis[i]==0){
            root=i;//初始化根节点是哪个
            len=1;//初始化访问顺序
            rootSonCnt=0;//初始化根节点的子树数量
            tarjan(root,-1,len);
            if(rootSonCnt>1)
                cutPointCnt++;
        }
    }
    return cutPointCnt;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,b,e,n;
    Edge edge;
    while(~scanf("%d",&V)&&V>0){
        for(i=1;i<=V;i++){
            adList[i].clear();
        }
        while(~scanf("%d",&b)&&b>0){
            while(getchar() != '\n'){
                scanf("%d",&e);
                edge.e=e;
                adList[b].push_back(edge);
                edge.e=b;
                adList[e].push_back(edge);
            }
        }
        //图可能是不连通的，应该多次判断知道所有点都被走过tarjan为止。这样才能找到每一块的割点，具体看题了
        printf("%d\n",getCutPoint());
    }
return 0;
}

