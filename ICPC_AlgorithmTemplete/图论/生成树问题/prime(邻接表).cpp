#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2139062143;////2139062143
const int MAX=5001;
const int mod=1e9+7;


struct Edge{
    int u,v,val;
    Edge(){}
    Edge(const int &u,const int &v,const int &val){
        this->u=u;
        this->v=v;
        this->val=val;
    }
    bool operator < (const Edge& x)const{//优先队列即最小堆
        return x.val<val;
    }
};
struct Graphic{
    int V,E,S,T=0;
    vector<Edge> adList[MAX];
	void clear(){
        for(int i=0;i<=V;i++){
            adList[i].clear();
        }
    }
};
Graphic g;
bool vis[MAX];
void dfs(int now){//dfs检查是不是联通图
    vis[now]=1;
    for(int i=0;i<g.adList[now].size();i++){
        if(vis[g.adList[now][i].v]==0)
            dfs(g.adList[now][i].v);
    }
}
bool isConnect(){//检查是不是联通图
    memset(vis,0,sizeof vis);
    dfs(1);
    for(int i=1;i<=g.V;i++){
        if(vis[i]==0){
            return 0;
        }
    }
    return 1;
}
bool isTree[MAX];//当前点是否在树里，true表示在
vector<Edge>edgeList;
int MST_prim(){//前提是连通图，如果longlong就要改变最大值INF
    int i,t,ans=0;
    memset(isTree,0,sizeof isTree);
    isTree[1]=1;
    priority_queue< Edge>que;
    for(i=0;i<g.adList[1].size();i++){
        if(isTree[g.adList[1][i].v]==0)
            que.push(g.adList[1][i]);
    }
    t=g.V-1;
    while(t&&!que.empty()){
        Edge now=que.top();
        que.pop();
        if(isTree[now.v])
            continue;
        isTree[now.v]=1;
        edgeList.push_back(now);
        ans+=now.val;
        for(i=0;i<g.adList[now.v].size();i++){
            if(isTree[g.adList[now.v][i].v]==0)
                que.push(g.adList[now.v][i]);
        }
        t--;
    }
    return ans;
}
int main(int argc,char *argv[]){
    int i,j,k,u,v,val;
    priority_queue<Edge>que;
    while(~scanf("%d%d",&g.V,&g.E)){
        g.clear();
        for(i=0;i<g.E;i++){//要判断重复边，自环不用考虑
            scanf("%d%d%d",&u,&v,&val);
            g.adList[u].push_back(Edge(u,v,val));
            g.adList[v].push_back(Edge(v,u,val));
        }
        if(isConnect()){
            printf("%d\n",MST_prim());
            for(auto a:edgeList){
                printf("%d-%d %d\n",a.u,a.v,a.val);
            }
        }else{
            printf("erro\n");
        }
    }
return 0;
}
/*
5 6
1 2 1
1 3 2
1 4 10
1 5 1
2 4 7
3 5 1
*/
