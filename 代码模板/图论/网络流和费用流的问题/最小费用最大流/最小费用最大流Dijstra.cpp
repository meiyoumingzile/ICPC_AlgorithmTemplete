#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#pragma GCC optimize(2)
const int inv2=500000004;
const int INF=0x3f3f3f3f;
const int MAX=1000010;
const int mod=1e9+7;

struct number{
    int i;int dis;
	bool operator < (const number &a) const {
        return dis>a.dis;//最小值优先
    }
    number(){}
    number(const int &i,const int &dis){
        this->i=i;
        this->dis=dis;
    }
};
struct Edge{
    int e,val,cost,k;
    Edge(){}
    Edge(int e,int val,int cost,int k){
        this->e=e;
        this->k=k;
        this->val=val;
        this->cost=cost;
    }
};
struct Graphic{
   int V,E,S,T;
    int size=0;
    int head[MAX];
    Edge edge[400010];
    void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
    void push(int b,int e,int val,int cost){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,cost,t);
    }
};
Graphic g;
int dist[MAX],h[MAX];//维护的数组类似于动态规划的dp数组；它的最大数量实际取决于点的数量相同,下标代表点，一般从1开始
Edge p[MAX];//记录最短路径；
ll Dijkstra_flow(ll &cost){//用Dijkstra_flow求最小费用最大流，返回最大流数值，cost引用最小费和
    int i,j,minv;
    number now,next;
    ll res[2];
    res[0]=res[1]=0;//res[0]表示最大流，res[1]表示费用
    priority_queue<number>que;
    memset(h,0,sizeof(h));
    while(1){
        memset(dist,INF,sizeof(dist));
        dist[g.S]=0;
        que.push(number(g.S,0));
        while(!que.empty()){
            now=que.top();
            que.pop();
            if(dist[now.i] < now.dis) continue;
            for(i=g.head[now.i];i!=-1;i=g.edge[i].k){
                if(g.edge[i].val>0){
                    next.i=g.edge[i].e;
                    next.dis=dist[now.i]+g.edge[i].cost+h[now.i]-h[next.i];
                    if(dist[next.i]>next.dis){//单位流量
                        p[next.i].e=now.i;
                        p[next.i].val=i;
                        dist[next.i]=next.dis;
                        que.push(next);
                    }
                }
            }
        }
        if(dist[g.T]==INF)
            break;
        for(i=g.T,minv=INF;i!=g.S;i=p[i].e){
            minv=min(minv,g.edge[p[i].val].val);
        }
        res[0]+=minv;
        res[1]+=(dist[g.T]+h[g.T])*minv;//加回来
        for(i=g.T;i!=g.S;i=p[i].e){
            const int &k=p[i].val;
            g.edge[k].val-=minv;
            g.edge[k^1].val+=minv;
        }
        for(i=1;i<g.V;++i){
            h[i]+=dist[i];
        }
    }
    cost=res[1];
    return res[0];
}
void print(Graphic &g){
    for(int i=1;i<=g.V;i++){
        for(int j=g.head[i];j!=-1;j=g.edge[j].k){
            //if(g.edge[j].val>0){
                printf("(%d %d %d)",i,g.edge[j].e,g.edge[j].val);
            //}
            //printf("(%d %d %d) ",i,g.edge[j].e,g.edge[j].val);
        }printf("\n");
    }
}
int main(int argc,char *argv[]){
	int i,j,k,b,e,val,cost;
	ll r1,r2; 
	g.clear();
    scanf("%d%d%d%d",&g.V,&g.E,&g.S,&g.T);
    for(i=0;i<g.E;i++){
        scanf("%d%d%d%d",&b,&e,&val,&cost);
        g.push(b,e,val,cost);
        g.push(e,b,0,-cost);
    }
    r1=Dijkstra_flow(r2);
    printf("%lld %lld\n",r1,r2);
return 0;
}
