#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
const int inv2=500000004;
const int INF=2139062143;////2139062143
const int MAX=5001;
const int mod=1e9+7;
inline void scan(int &x){
    rg char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}

struct Edge{
    int e,val,k;
    Edge(){}
    Edge(const int &e,const int &val,const int &k){
        this->e=e;
        this->val=val;
        this->k=k;
    }
    bool operator < (const Edge& x)const{//优先队列即最小堆
        return x.val<val;
    }
};
struct Graphic{
    int V,E,S,T,size=0;
    int head[MAX];
    Edge edge[400010];
    void push(const int &b,const int &e,const int &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
    }
	void doupushMin(const int &b,const int &e,const int &val){//加入边如果存在更新成最小，双向加入
        rg int i;
        for(i=head[b];i!=-1&&edge[i].e!=e;i=edge[i].k);
        if(i==-1){
            push(b,e,val);
            push(e,b,val);
        }else{
            edge[i].val=min(edge[i].val,val);
            edge[i^1].val=min(edge[i^1].val,val);
        }
    }
	void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
};
Graphic g;
bool vis[MAX];
void dfs(int now){//dfs检查是不是联通图
    vis[now]=1;
    for(int i=g.head[now];i!=-1;i=g.edge[i].k){
        if(vis[g.edge[i].e]==0)
            dfs(g.edge[i].e);
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
int MST_prim(){//范围是int,如果longlong就要改变最大值INF
    rg int i,t,ans=0;
    memset(isTree,0,sizeof isTree);
    isTree[1]=1;
    priority_queue< Edge>que;
    for(i=g.head[1];i!=-1;i=g.edge[i].k){
        if(isTree[g.edge[i].e]==0)
            que.push(g.edge[i]);
    }
    t=g.V-1;
    while(t&&!que.empty()){
        Edge now=que.top();
        que.pop();
        if(isTree[now.e])
            continue;
        isTree[now.e]=1;
        ans+=now.val;
        for(i=g.head[now.e];i!=-1;i=g.edge[i].k){
            if(isTree[g.edge[i].e]==0)
                que.push(g.edge[i]);
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
            g.doupushMin(u,v,val);
        }
        if(isConnect()){
            printf("%d\n",MST_prim());
        }else{
            printf("orz\n");
        }
    }
return 0;
}
