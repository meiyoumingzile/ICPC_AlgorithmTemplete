#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<stack>
#include<cmath>
#include<string>
#include<cstring>
//#include<windows.h>
using namespace std;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;

/*
//最短路小小变形，走的路长度不是权值本身，而是看和上一个边权值是否相等，不相等长度增加1,否则就不需要花费长度
在迪杰斯特拉的队列结构体额外维护一个val表示上个边的权值即可，或者开个数组表示也可以
*/

struct Edge{
    int e,val,k;
    Edge(){}
    Edge(const int e,const int val,const int k){
        this->e=e;
        this->val=val;
        this->k=k;
    }
};
struct Graphic{
    int V,E,sz;
    int head[MAX];
    Edge edge[4*MAX];
    Graphic(){
        this->clear();
    }
    void push(const int b,const int e,const int val){
        int t=head[b];
        head[b]=sz;
        edge[sz++]=Edge(e,val,t);
    }
	void clear(){
        sz=0;
        memset(head,-1,sizeof(head));
    }
};
Graphic g;
struct Node{
    int i,dis,val;
    bool operator < (const Node a) const {
        return dis>a.dis;//最小值优先
    }
};
int dist[MAX];//表示起点到编号为i的点的最短路，初始值是INF；
priority_queue<Node>que;
//bool vis[MAXDOT];//表示有没有入过队列；//0表示还没入队过
void Dijkstra(int start){//类似广搜,此算法针对无负数边的图
    int i,j,k;
    Node now,next;
    now.i=start;
    now.dis=0;
    now.val=0;
    for(i=1;i<=g.V;i++)
        dist[i]=INF;
    dist[start]=0;
    que.push(now);
    while(!que.empty()){
        now=que.top();
        que.pop();
        for(i=g.head[now.i];i!=-1;i=g.edge[i].k){//表示遍历当前点能到达的所有点
            next.i=g.edge[i].e;
            next.dis=dist[now.i]+(now.val!=g.edge[i].val);
            if(dist[next.i]>next.dis){//下一个本身的值大于求得的新值才更新
                next.val=g.edge[i].val;
                dist[next.i]=next.dis;
                que.push(next);
            }
        }
    }
}

int main(){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,T,u,v,val;
	while(~scanf("%d%d",&g.V,&g.E)){
        g.clear();
        for(i=0;i<g.E;i++){
            scanf("%d%d%d",&u,&v,&val);
            if(u!=v){

                    g.push(u,v,val);
                    g.push(v,u,val);

            }
        }
        Dijkstra(1);
        if(dist[g.V]==INF){
            dist[g.V]=-1;
        }
        printf("%d\n",dist[g.V]);
	}
return 0;
}

