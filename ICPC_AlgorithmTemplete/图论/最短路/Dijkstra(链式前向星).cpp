#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
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
    Edge edge[MAX*2];
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

struct Node{
    int i,dis;
    bool operator < (const Node a) const {
        return dis>a.dis;//最小值优先
    }
    void sett(int i,int dis){
        this->i=i;
        this->dis=dis;
    }
};
int dist[MAX];//表示起点到编号为i的点的最短路，初始值是INF；
priority_queue<Node>que;
//bool vis[MAXDOT];//表示有没有入过队列；//0表示还没入队过
int last[MAX];//表示当前点最短路径下的上一个点是哪个，用了输出最短路径
void Dijkstra(int start){//类似广搜,此算法针对无负数边的图
    int i,j,k;
    Node now,next;
    now.sett(start,0);//等于初始值
    memset(dist,127,sizeof dist);
    dist[start]=0;
    que.push(now);
    while(!que.empty()){
        now=que.top();
        que.pop();
        if(now.dis!=dist[now.i])//大优化，勿省略
            continue;
        for(i=g.head[now.i];i!=-1;i=g.edge[i].k){//表示遍历当前点能到达的所有点
            next.i=g.edge[i].e;
            next.dis=now.dis+g.edge[i].val;
            if(dist[next.i]>next.dis&&now.i!=next.i){//下一个本身的值大于求得的新值才更新
                dist[next.i]=next.dis;
                que.push(next);
            }
        }
    }
}
inline void scan(int &x){
    rg char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}

int main(){
    int i,j,k,T,u,v,val,s;
    g.clear();
    scan(g.V);scan(g.E);scan(s);
    for(i=0;i<g.E;i++){
        scan(u);scan(v);scan(val);
        g.push(u,v,val);
       // g.push(v,u,val);
    }
    Dijkstra(s);
    for(i=1;i<=g.V;i++){
        printf("%d%c",dist[i],i==g.V?'\n':' ');
    }
return 0;
}
