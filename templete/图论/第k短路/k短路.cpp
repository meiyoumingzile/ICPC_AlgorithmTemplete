#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2139062143;////2139062143
const int MAX=1010;
const int mod=1e9+7;
/*
例题是poj2449 求s到t最短路 V<1000  k<1000
*/
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
    int V,E,S,T,size;
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
Graphic g,ig;//ig是反向图
struct Node{
    int i;
	ll dis;
    bool operator < (const Node a) const {
        return dis>a.dis;//最小值优先
    }
    void sett(cint i,cll dis){
        this->i=i;
        this->dis=dis;
    }
};
ll dist[MAX];//表示起点到编号为i的点的最短路，初始值是INF；
priority_queue<Node>que;//a*和迪杰斯特拉公用一个堆
void Dijkstra(Graphic &g){//传入一个图 
    int i,j,k;
    Node now,next;
    now.sett(g.S,0);//等于初始值
    memset(dist,-1,sizeof dist);//-1表示无穷大
    dist[g.S]=0;
    que.push(now);
    while(!que.empty()){
        now=que.top();
        que.pop();
        if(now.dis!=dist[now.i])//大优化，勿省略
            continue;
        for(i=g.head[now.i];i!=-1;i=g.edge[i].k){//表示遍历当前点能到达的所有点
            next.i=g.edge[i].e;
            next.dis=now.dis+g.edge[i].val;
            if(dist[next.i]==-1||dist[next.i]>next.dis){//下一个本身的值大于求得的新值才更新
                dist[next.i]=next.dis;
                que.push(next);
            }
        }
    }
}
ll A_star(Graphic &g,int K){//寻找第k短路，找到返回数值，没找到返回-1
    if(dist[g.S]==-1)
        return -1;
    Node now,next;
    int tcnt=0;//终点出队次数
    now.sett(g.S,dist[g.S]);
    que.push(now);
    if(g.T==g.S)//起点终点是同一个点,起始会多走了一次，要补回来
        K++;
    while(!que.empty()){
        now=que.top();
        que.pop();
        if(now.i==g.T){
            tcnt++;
            if(tcnt==K)
                return now.dis;
        }
        for(int i=g.head[now.i];i!=-1;i=g.edge[i].k){
            next.dis=now.dis-dist[now.i]+g.edge[i].val+dist[g.edge[i].e];
            next.i=g.edge[i].e;
            que.push(next);
        }
    }
    return -1;
}
int main(){
	int i,k,n,u,v,val;
	while(~scanf("%d%d",&g.V,&g.E)){//k短路
	    g.clear();
	    ig.clear();
        for(i=0;i<g.E;i++){
            scanf("%d%d%d",&u,&v,&val);
            g.push(u,v,val);
            ig.push(v,u,val);
        }
        scanf("%d%d%d",&g.S,&g.T,&k);
        ig.S=g.T;
        Dijkstra(ig);//初始化反向最短路，作为a*的h(x);
        printf("%lld\n",A_star(g,k));
	}
return 0;
}

